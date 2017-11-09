using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeEins {

	struct Morphem {
		public MorphemCode code { get; private set; }
		char operand;
		public char Operand { get { return operand; } set { operand = value; code = MorphemCode.operand; } }
		double number;
		public double Number { get { return number; } set { number = value; code = MorphemCode.number; } }
		string identifier;
		public string Identifier { get { return identifier; } set { identifier = value; code = MorphemCode.identifier; } }
		public void SetEmpty() {
			code = MorphemCode.empty;
		}
	}

	enum MorphemCode {
		empty,
		operand,
		number,
		identifier
	}

	class Lexer {
		public string InputString { get; set; }
		public int Position { get; private set; }
		public char CurrentChar { get { return InputString[Position]; } }
		public Morphem CurrentMorphem;
		private enum ActionCode : byte {
			q=0,  // quit:				beenden
			r=1,  // read:				lesen
			cr=2, // char, read:			Großbuchstaben schreiben, lesen
			wr=3, // write, read:			schreiben, lesen
			wrq=4 // write, read, quit:	schreiben, lesen, beenden
		}
		private static byte[] charClassTable = {
		/*		0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F	*/
		/* 0*/	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,	//   0+
		/*10*/	7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,	//  16+
		/*		   !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /	*/
		/*20*/	7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//  32+
		/*		Zahlen                        :  ;  <  =  >  ?	*/
		/*30*/	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 5, 4, 6, 0,	//  48+
		/*		@  Großbuchstaben								*/
		/*40*/	0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	//  64+
		/*		                                 [  \  ]  ^  _	*/
		/*50*/	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0,	//  80+
		/*		`  Kleinbuchstaben								*/
		/*60*/	0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,	//  96+
		/*		                                 {  |  }  ~		*/
		/*70*/	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0	// 112+
		// 
		};
		/**Jedes Array enthält eine Klasse.
		 * Jedes Klassenarray 
		 * 
		 */
		private static byte[,,] classNextActionTable = {
		/* Zust		So		Zi		Bu		:		=		<		>		Sonst	*/
		/* 0 */{    {0, (byte)ActionCode.wrq} },
		/* 1 */{ },
		/* 2 */{ },
		/* 3 */{ },
		/* 4 */{ },
		/* 5 */{ },
		/* 6 */{ },
		/* 7 */{ },
		/* 8 */{ }
		};


		public Lexer(string inputString) {
			InputString = inputString;
			Position = 0;
		}


		double StringToDouble() {
			string numberString = "";

			while (NextMorphemExists() && Char.IsDigit(CurrentChar)) {
				numberString += CurrentChar.ToString();
				Position += 1;
			}
			if (NextMorphemExists() && CurrentChar == '.') {
				do {
					numberString += CurrentChar.ToString();
					Position += 1;
				} while (NextMorphemExists() && Char.IsDigit(CurrentChar));
			}
			//Console.WriteLine("Parse {0} next: '{1}'", numberString, CurrentChar);
			return double.Parse(numberString);
		}

		void SkipWhitespaces() {
			while (NextMorphemExists() && (CurrentChar == '\t' || CurrentChar == ' '))
				Position += 1;
		}

		bool NextMorphemExists() {
			if (InputString.Length > Position)
				return true;
			else
				return false;
		}

		public void NextMorphem() {
			if (!NextMorphemExists()) {
				CurrentMorphem.SetEmpty();
			} else {
				SkipWhitespaces();
				if (Char.IsDigit(CurrentChar)) {
					CurrentMorphem.Number = StringToDouble();
				} else {
					switch (CurrentChar) {
						case '+':
						case '-':
						case '*':
						case '/':
						case '(':
						case ')':
							CurrentMorphem.Operand = CurrentChar;
							Position += 1;
							break;
						default:
							Console.WriteLine("Falsche Eingabe: '{0}'!\n Abbruch.\n", CurrentChar);
							Environment.Exit(1);
							break;
					}
				}
			}
		}
	}

	class Evaluator {

		Lexer lexer;

		public Evaluator(string inputString) {
			lexer = new Lexer(inputString);
		}

		public double Evaluate() {
			lexer.NextMorphem();    // erstes Morphem
			return Expression();
		}

		double Expression() {
			double result = Term();
			while (lexer.CurrentMorphem.code == MorphemCode.operand && (lexer.CurrentMorphem.Operand == '+' || lexer.CurrentMorphem.Operand == '-')) {
				if (lexer.CurrentMorphem.Operand == '+') {
					lexer.NextMorphem();    // konsumiere gelesenen Operanden
					result += Term();
				} else if (lexer.CurrentMorphem.Operand == '-') {
					lexer.NextMorphem();    // konsumiere gelesenen Operanden
					result -= Term();
				}
			}
			return result;
		}

		double Term() {
			double result = Factor();
			while (lexer.CurrentMorphem.code == MorphemCode.operand && (lexer.CurrentMorphem.Operand == '*' || lexer.CurrentMorphem.Operand == '/')) {
				if (lexer.CurrentMorphem.Operand == '*') {
					lexer.NextMorphem();    // konsumiere gelesenen Operanden
					result *= Factor();
				} else if (lexer.CurrentMorphem.Operand == '/') {
					lexer.NextMorphem();    // konsumiere gelesenen Operanden
					result /= Factor();
				}
			}
			return result;
		}

		double Factor() {
			double result;
			if (lexer.CurrentMorphem.code == MorphemCode.operand) {
				if (lexer.CurrentMorphem.Operand == '(') {
					lexer.NextMorphem();    // konsumiere gelesene Klammer auf
					result = Expression();
					if (lexer.CurrentMorphem.code != MorphemCode.operand || lexer.CurrentMorphem.Operand != ')') {
						Console.WriteLine("Habe ) erwartet, aber {0} gefunden.\n", lexer.CurrentChar);
						Environment.Exit(1);
					}
					lexer.NextMorphem();    // konsumiere gelesene Klammer zu
				} else {
					Console.WriteLine("Habe ( erwartet, aber {0} gefunden.\n", lexer.CurrentChar);
					result = 1;
					Environment.Exit(1);
				}

			} else {
				if (lexer.CurrentMorphem.code == MorphemCode.number) {
					result = lexer.CurrentMorphem.Number;
					lexer.NextMorphem();    // konsumiere gelesene Zahl
				} else {
					Console.WriteLine("Habe eine Zahl erwartet, aber {0} gefunden.\n", lexer.CurrentChar);
					result = 1;
					Environment.Exit(1);
				}
			}
			return result;
		}
	}

	class MainClass {
		static void Main(string[] args) {
			while (true) {
				Console.Write("Rechnung: ");
				string input = Console.ReadLine();
				Evaluator evaluator = new Evaluator(input);
				double result = evaluator.Evaluate();
				Console.WriteLine("Ergebnis: " + result);
				Console.WriteLine("========================");
			}
		}
	}
}
