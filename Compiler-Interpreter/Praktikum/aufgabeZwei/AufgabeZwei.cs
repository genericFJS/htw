using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeEins {

	struct Morphem {
		public MorphemCode code { get; private set; }
		public int[] position;
		string stringValue;
		public string Symbol {
			get { return stringValue; }
			set { stringValue = value; code = MorphemCode.symbol; }
		}
		double numberValue;
		public double Number {
			get { return numberValue; }
			set { numberValue = value; code = MorphemCode.number; }
		}
		public string Identifier {
			get { return stringValue; }
			set { stringValue = value; code = MorphemCode.identifier; }
		}
		public dynamic getValue() {
			switch (code) {
				case MorphemCode.empty:
					return null;
				case MorphemCode.identifier:
				case MorphemCode.symbol:
					return stringValue;
				case MorphemCode.number:
					return numberValue;
				default:
					return "none";
			}
		}
		public void Init() {
			Reset();
			position = new int[] { 1, 1 };
		}
		public void Reset() {
			code = MorphemCode.empty;
		}
	}

	enum MorphemCode {
		empty,
		symbol,
		number,
		identifier,
	}

	enum ExitCode : int {
		Success = 0,
		NoFile = 1
	}

	class Lexer {
		private StreamReader reader;
		private int currentState;
		private int currentCharCode;
		private string tempMorphemString;
		private Morphem lexedMorphem;

		// Aktionen für Kategorien:
		private enum Actions {
			FinishMorphem,      // finish:				beenden
			ReadNext,           // read:				lesen
			WriteCharReadNext,  // char, read:			Großbuchstaben schreiben, lesen
			WriteReadNext,      // write, read:			schreiben, lesen
			WriteReadNextFinish // write, read, quit:	schreiben, lesen, beenden
		}
		// Aktionen als kurze Variablen zur besseren Übersicht in der Tabelle:
		private const int F = (int)Actions.FinishMorphem;
		private const int R = (int)Actions.ReadNext;
		private const int CR = (int)Actions.WriteCharReadNext;
		private const int WR = (int)Actions.WriteReadNext;
		private const int WRQ = (int)Actions.WriteReadNextFinish;

		/// <summary>
		/// Gibt an, welches Zeichen welcher Kategorie entspricht. 
		/// Die Kategorie entscheidet über die Abarbeitung des nächsten Zeichens.
		/// Kategorien:
		/// 0: Sonderzeichen
		/// 1: Buchstaben
		/// 2: Ziffern
		/// 3: Doppelpunkt
		/// 4: Kleiner
		/// 5: Größer
		/// 6: Gleich
		/// 7: Steuersymbol
		/// </summary>
		private readonly byte[] charCategoryTable = {
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,	//   0+
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,	//  16+
		/*	   !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /	*/
			7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//  32+
		/*	Zahlen                        :  ;  <  =  >  ?	*/
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 0, 4, 6, 5, 0,	//  48+
		/*	@  Großbuchstaben								*/
			0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//  64+
		/*	                                 [  \  ]  ^  _	*/
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,	//  80+
		/*	`  Kleinbuchstaben								*/
			0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,	//  96+
		/*		                                 {  |  }  ~	*/
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0	// 112+
		// 
		};
		/// <summary>
		/// Abhängig von dem aktuellen Zustand und der Kategorie des gelesenen Zeichens 
		/// sollen unterschiedliche Aktionen ausgeführt werden.
		/// Die äußersten Arrays entsprichen den möglichen Zuständen. 
		/// Die darin geschachtelten Arrays enthalten die möglichen Kategorien des gelesenen Zeichens.
		/// Dieses innere Array enthält den Folgezustand und die auszuführende Aktion.
		/// Zustände:
		/// Z0: Grundzustand
		/// Z1: Buchstabe
		/// Z2: Ziffer
		/// Z3: Doppelpunkt
		/// Z4: Kleiner
		/// Z5: Größer
		/// Z6: Doppelpunkt-Gleich
		/// Z7: Kleiner-Gleich
		/// Z8: Größer-Gleich
		/// </summary>
		private readonly int[,,] categoryNextActionTable = {
		/* Zust		So			Bu			Zi			:			<			>			=			Sonst	*/
		/* Z0 */{   {9, WRQ},   {1, CR},    {2, WR},    {3, WR},    {4, WR},    {5, WR},    {9, WRQ},   {0, R}  },
		/* Z1 */{   {9, F},     {1, CR},    {1, WR},    {9, F},     {9, F},     {9, F},     {9, F},     {9, F}  },
		/* Z2 */{   {9, F},     {9, F},     {2, WR},    {9, F},     {9, F},     {9, F},     {9, F},     {9, F}  },
		/* Z3 */{   {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {6, WR},    {9, F}  },
		/* Z4 */{   {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {7, WR},    {9, F}  },
		/* Z5 */{   {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {8, WR},    {9, F}  },
		/* Z6 */{   {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F}  },
		/* Z7 */{   {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F}  },
		/* Z8 */{   {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F},     {9, F}  }
		};

		/// <summary>
		/// Tabelle der möglichen Schlüsselwörtern abhängig von:
		/// - Anfangsbuchstabe (äußeres Array)
		/// - Länge (inneres Array)
		/// Wenn Eintrag null ist, liegt kein Schlüsselwort vor.
		/// Ansonsten muss die zu prüfende Zeichenkette mit Eintrag verglichen werden:
		/// Bei Gleichheit liegt entsprechendes Schlüsselwort vor.
		/// </summary>
		private readonly string[,] keywordTable = {
		/* Len:	2      3      4       5        6     7     8       9   	*/
		/* A */ {null, null,  null,   null,    null, null, null,   null       },
		/* B */ {null, null,  null,   "BEGIN", null, null, null,   null       },
		/* C */ {null, null,  "CALL", "CONST", null, null, null,   null       },
		/* D */ {"DO", null,  null,   null,    null, null, null,   null       },
		/* E */ {null, "END", null,   null,    null, null, null,   null       },
		/* F */ {null, null,  null,   null,    null, null, null,   null       }, // ELSE?
		/* G */ {null, null,  null,   null,    null, null, null,   null       }, // GET?
		/* H */ {null, null,  null,   null,    null, null, null,   null       },
		/* I */ {"IF", null,  null,   null,    null, null, null,   null       },
		/* J */ {null, null,  null,   null,    null, null, null,   null       },
		/* K */ {null, null,  null,   null,    null, null, null,   null       },
		/* L */ {null, null,  null,   null,    null, null, null,   null       },
		/* M */ {null, null,  null,   null,    null, null, null,   null       },
		/* N */ {null, null,  null,   null,    null, null, null,   null       },
		/* O */ {null, "ODD", null,   null,    null, null, null,   null       },
		/* P */ {null, null,  null,   null,    null, null, null,   "PROCEDURE"}, // PUT?
		/* Q */ {null, null,  null,   null,    null, null, null,   null       },
		/* R */ {null, null,  null,   null,    null, null, null,   null       },
		/* S */ {null, null,  null,   null,    null, null, null,   null       },
		/* T */ {null, null,  "THEN", null,    null, null, null,   null       },
		/* U */ {null, null,  null,   null,    null, null, null,   null       },
		/* V */ {null, "VAR", null,   null,    null, null, null,   null       },
		/* W */ {null, null,  null,   "WHILE", null, null, null,   null       },
		/* X */ {null, null,  null,   null,    null, null, null,   null       },
		/* Y */ {null, null,  null,   null,    null, null, null,   null       },
		/* Z */ {null, null,  null,   null,    null, null, null,   null       }
		};

		public Lexer(string filePath) {
			if (!filePath.EndsWith(".pl0"))
				filePath += ".pl0";
			if (!File.Exists(filePath)) {
				Console.WriteLine("File not found: '{0}'", filePath);
				Environment.Exit((int)ExitCode.NoFile);
			} else {
				reader = new StreamReader(@filePath);
			}
			lexedMorphem = new Morphem();
			lexedMorphem.Init();
			ReadNext();
		}

		public Morphem NextMorphem() {
			currentState = 0;
			lexedMorphem.Reset();
			tempMorphemString = "";
			int currentCategory;
			// Während aktueller Zustand noch ein gültiger abzuarbeitender Zustand ist:
			while (currentState < categoryNextActionTable.GetLength(0)) {
				// Aufhören, wenn ungültiges (nicht-ASCII) Zeichen oder EOF
				if (charCategoryTable.Length < currentCharCode || currentCharCode < 0) {
					break;
				}
				currentCategory = charCategoryTable[currentCharCode];
				//Console.WriteLine("CharCode: {1}[{0}]; Current State: {2}; Current Category: {3}", currentCharCode, (char)currentCharCode, currentState, currentCategory);
				switch ((Actions)categoryNextActionTable[currentState, currentCategory, 1]) {
					case Actions.ReadNext:
						ReadNext();
						break;
					case Actions.WriteReadNext:
						WriteReadNext();
						break;
					case Actions.WriteCharReadNext:
						WriteCharReadNext();
						break;
					case Actions.WriteReadNextFinish:
						WriteReadNextFinish();
						break;
					case Actions.FinishMorphem:
						FinishMorphem();
						break;
				}
				// Nächsten Zustand setzen (abhängig vom aktuellen Zustand und Zeichen):
				currentState = categoryNextActionTable[currentState, currentCategory, 0];
				//Console.WriteLine("Read so far: {0} - next state: {1}", tempMorphemString, currentState);
			}
			return lexedMorphem;
		}

		private void ReadNext() {
			//Console.Write("{0}|", currentCharCode);
			// 10: newline
			if (currentCharCode == 10) {
				// nächste Zeile (Zeile erhöhen, Spalte zurücksetzen)
				lexedMorphem.position[0] = 1;
				lexedMorphem.position[1]++;
			} else {
				lexedMorphem.position[0]++;
			}
			currentCharCode = reader.Read();
		}

		private void WriteCharReadNext() {
			//Console.WriteLine("Writing char: {0}", (char)currentCharCode);
			tempMorphemString += ((char)currentCharCode).ToString().ToUpper();
			ReadNext();
		}

		private void WriteReadNext() {
			tempMorphemString += ((char)currentCharCode).ToString();
			ReadNext();
		}

		private void WriteReadNextFinish() {
			WriteReadNext();
			FinishMorphem();
		}

		private void FinishMorphem() {
			switch (currentState) {
				case 3: // :
				case 4: // <
				case 5: // >
				case 6: // :=
				case 7: // <=
				case 8: // >=
				case 0: // Sonderzeichen
					lexedMorphem.Symbol = tempMorphemString;
					break;
				case 2: // Zahl
					lexedMorphem.Number = double.Parse(tempMorphemString);
					break;
				case 1: // Buchstabe
					if (IsKeyword(tempMorphemString)) {
						lexedMorphem.Symbol = tempMorphemString;
					} else {
						lexedMorphem.Identifier = tempMorphemString;
					}
					break;
				default:
					Console.WriteLine("Unknown morphem: {0}", tempMorphemString);
					break;
			}
		}

		private bool IsKeyword(string morphemString) {
			int morphemLength = morphemString.Length;
			// Länger als längstes Keyword?
			if (morphemLength < 2 || morphemLength > keywordTable.GetLength(1) + 1)
				return false;
			// Eintrag aus Keyword-Tabelle
			string potentialKeyword = keywordTable[(int)morphemString[0] - 65, morphemLength - 2];
			if (potentialKeyword != null && potentialKeyword.Equals(morphemString))
				return true;
			return false;
		}

		// ====================================================================
		//							Performance Tests
		// ====================================================================

		private readonly List<string> keywordList = new List<string> {
			"DO", "IF", "END", "ODD", "VAR", "CALL", "THEN", "BEGIN", "CONST", "WHILE", "PROCEDURE"
		};

		private bool IsKeywordAlt(string morphemString) {
			if (keywordList.Contains(morphemString))
				return true;
			else
				return false;
		}

		// Vergleich zeigt, dass das Array in jedem Fall schneller ist. Vor allem aber, wenn Elemente in der Liste sind, die nicht passen.
		public void CompareKeywordSearch() {
			int times = 1000000;
			double normalizer = 1000000;
			double t1, t2;
			List<string> testElements = keywordList;
			int counter = 0;
			Stopwatch sw = new Stopwatch();

			sw.Start();
			while (counter < times) {
				foreach (string element in testElements) {
					IsKeyword(element);
					counter++;
				}
			}
			sw.Stop();
			t1 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			sw.Reset();
			counter = 0;
			sw.Start();
			while (counter < times) {
				foreach (string element in testElements) {
					IsKeywordAlt(element);
					counter++;
				}
			}
			sw.Stop();
			t2 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			Console.WriteLine("(Average time in ns for 1000000 searches)");
			Console.WriteLine("Option                              Time KeywordTable  Time KeywordList  Table Speedup");
			Console.WriteLine("Search only matching:               {0,-12:0.00}       {1,-12:0.00}      {2,3:0.}%", t1, t2, t2 / t1 * 100);

			testElements.Add("HALLO");
			testElements.Add("HALLO");
			testElements.Add("HALLO");
			testElements.Add("HALLO");
			testElements.Add("HALLO");
			sw.Reset();
			counter = 0;
			sw.Start();
			while (counter < times) {
				foreach (string element in testElements) {
					IsKeyword(element);
					counter++;
				}
			}
			sw.Stop();
			t1 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			sw.Reset();
			counter = 0;
			sw.Start();
			while (counter < times) {
				foreach (string element in testElements) {
					IsKeywordAlt(element);
					counter++;
				}
			}
			sw.Stop();
			t2 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			Console.WriteLine("Search other, too (shorter):        {0,-12:0.00}       {1,-12:0.00}      {2,3:0.}%", t1, t2, t2 / t1 * 100);

			testElements.Add("PROZEDURAL");
			testElements.Add("PROZEDURAL");
			testElements.Add("PROZEDURAL");
			testElements.Add("PROZEDURAL");
			testElements.Add("PROZEDURAL");
			testElements.Add("PROZEDURAL");
			sw.Reset();
			counter = 0;
			sw.Start();
			while (counter < times) {
				foreach (string element in testElements) {
					IsKeyword(element);
					counter++;
				}
			}
			sw.Stop();
			t1 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			sw.Reset();
			counter = 0;
			sw.Start();
			while (counter < times) {
				foreach (string element in testElements) {
					IsKeywordAlt(element);
					counter++;
				}
			}
			sw.Stop();
			t2 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			Console.WriteLine("Search other, too (shorter+longer): {0,-12:0.00}       {1,-12:0.00}      {2,3:0.}%", t1, t2, t2 / t1 * 100);
		}

		private void TestCode() {
			for (int i = 1; i < 1000; i++)
				;
		}

		private void TestFuncA() {
			TestCode();
		}

		private void TestFuncB() {
			TestCode();
		}

		private void TestFuncC() {
			TestCode();
		}

		private void TestFuncD() {
			TestCode();
		}

		private enum TestActions {
			TestFuncA = 0,
			TestFuncB,
			TestFuncC,
			TestFuncD
		}

		// Vergleicht das Aufrufen einer Funktion abhängig von einem enum-Bezeichner: Entweder über Reflection oder über Switch. Switch ist schneller.
		public void CompareInvokeSwitch() {
			int[] test = { 0, 1, 2, 3 };

			int times = 100000;
			double normalizer = 1000000;
			double t1, t2;
			int counter = 0;
			Stopwatch sw = new Stopwatch();

			sw.Start();
			while (counter < times) {
				foreach (int element in test) {
					string actionFunctionName = ((TestActions)test[1]).ToString();
					this.GetType().GetMethod(actionFunctionName, BindingFlags.NonPublic | BindingFlags.Instance).Invoke(this, null);
					counter++;
				}
			}
			sw.Stop();
			t1 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			sw.Reset();
			counter = 0;
			sw.Start();
			while (counter < times) {
				foreach (int element in test) {
					switch (element) {
						case 0:
							TestFuncA();
							break;
						case 1:
							TestFuncB();
							break;
						case 2:
							TestFuncC();
							break;
						case 3:
							TestFuncD();
							break;
					}
					counter++;
				}
			}
			sw.Stop();
			t2 = sw.Elapsed.TotalMilliseconds * normalizer / counter;
			Console.WriteLine("(Average time in ns for 1000000 calls)");
			Console.WriteLine("Option                Time Reflection  Time Switch Case  Reflection Speedup");
			double speedUp;
			if (t2 > t1)
				speedUp = t2 / t1 * 100;
			else
				speedUp = -t1 / t2 * 100;
			Console.WriteLine("Search only matching: {0,-12:0.00}     {1,-12:0.00}      {2,4:0.}%", t1, t2, speedUp);
		}
	}

	class Evaluator {

		Lexer lexer;
		int currentLine;

		public Evaluator(string filePath) {
			lexer = new Lexer(filePath);
			currentLine = 0;
		}



		public void Evaluate() {
			Morphem morphem;
			do {
				morphem = lexer.NextMorphem();
				//Console.WriteLine("erstes: {0} ({1})", morphem.getValue(), morphem.code);
				if (currentLine < morphem.position[1]) {
					currentLine = morphem.position[1];
					Console.Write("\n{0,2}: ", currentLine);
				}
				switch (morphem.code) {
					case MorphemCode.number:
						Console.ForegroundColor = ConsoleColor.Blue;
						Console.Write("{0} ", morphem.getValue());
						Console.ResetColor();
						break;
					case MorphemCode.identifier:
						Console.ForegroundColor = ConsoleColor.Cyan;
						Console.Write("{0} ", morphem.getValue());
						Console.ResetColor();
						break;
					case MorphemCode.symbol:
						Console.ForegroundColor = ConsoleColor.Green;
						Console.Write("{0} ", morphem.getValue());
						Console.ResetColor();
						break;
					default:
						Console.ForegroundColor = ConsoleColor.Red;
						Console.Write("\nFinished\n");
						Console.ResetColor();
						break;
				}
			} while (morphem.code != MorphemCode.empty);
		}

		public void CompareLexerPerformance() {
			lexer.CompareKeywordSearch();
			Console.Write("========================\n");
			lexer.CompareInvokeSwitch();
		}
	}

	class MainClass {
		static void Main(string[] args) {
			while (true) {
				Console.Write("Dateiname: ");
				string input = Console.ReadLine();
				Evaluator evaluator = new Evaluator(input);
				evaluator.Evaluate();
				Console.WriteLine("========================");
				evaluator.CompareLexerPerformance();
				Console.WriteLine("========================");
			}
		}
	}
}
