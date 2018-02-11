using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
    class Lexer {
        // Stream der zu lexenden Datei:
        private StreamReader fileReader;
        // Aktueller Zustand (relevant für nächste Aktion):
        private int currentState;
        // Aktueller Character als Zahl:
        private int currentCharCode;
        // Aktueller Morphemwert (wird bei längeren Morphemen stets erweitert):
        private string tempMorphemString;
        // Das erarbeitete Morhpem (zur Rückgabe):
        private Morphem lexedMorphem;
        // Delegate für die Nächste Aktion im der categoryNextActionTable:
        private delegate void ActionDelegate();

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
        /// 8: Anführungszeichen
        /// </summary>
        private readonly byte[] charCategoryTable = {
            7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,	//   0+
			7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,	//  16+
		/*	   !  "  #  $  %  &  '  (  )  *  +  ,  -  .  /	*/
			7, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	//  32+
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
        /// </summary>
        private readonly object[,,] categoryNextActionTable;

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

        /// <summary>
        /// Startet den Lexer, indem die Datei zum Lesen vorbereitet wird, das erste mal liest und ein Morphem initialisiert wird.
        /// </summary>
        /// <param name="filePath">Datei, die vom Lexer verarbeitet werden soll. Datei muss mit .pl0 enden (Eingabe nicht).</param>
        public Lexer(string filePath) {
            fileReader = new StreamReader(@filePath);
            // Aktionen als kurze Variablen zur besseren Übersicht in der Tabelle:
            ActionDelegate F = new ActionDelegate(FinishMorphem);
            ActionDelegate R = new ActionDelegate(ReadNext);
            ActionDelegate QR = new ActionDelegate(FinishReadNext);
            ActionDelegate CR = new ActionDelegate(WriteCharReadNext);
            ActionDelegate WR = new ActionDelegate(WriteReadNext);
            ActionDelegate WRQ = new ActionDelegate(WriteReadNextFinish);
            // Belegung der Tabelle.
            // Zustände:
            // Z0: Grundzustand
            // Z1: Buchstabe
            // Z2: Ziffer
            // Z3: Doppelpunkt
            // Z4: Kleiner
            // Z5: Größer
            // Z6: Doppelpunkt-Gleich
            // Z7: Kleiner-Gleich
            // Z8: Größer-Gleich
            // Z9: Anführungszeichen
            categoryNextActionTable = new object[,,]{
				/* Zust		So			 Bu			   Zi			  :			    <			  >		        =			  Sonst         "      */
				/* Z0 */{ { -1, WRQ},   {  1, CR},    {  2, WR},    {  3, WR},    {  4, WR},    {  5, WR},    { -1, WRQ},   {  0, R},     {  9, R}  },
				/* Z1 */{ { -1, F},     {  1, CR},    {  1, WR},    { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F}  },
				/* Z2 */{ { -1, F},     { -1, F},     {  2, WR},    { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F}  },
				/* Z3 */{ { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     {  6, WR},    { -1, F},     { -1, F}  },
				/* Z4 */{ { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     {  7, WR},    { -1, F},     { -1, F}  },
				/* Z5 */{ { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     {  8, WR},    { -1, F},     { -1, F}  },
				/* Z6 */{ { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F}  },
				/* Z7 */{ { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F}  },
				/* Z8 */{ { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F},     { -1, F}  },
				/* Z9 */{ {  9, WR},    {  9, WR},    {  9, WR},    {  9, WR},    {  9, WR},    {  9, WR},    {  9, WR},    {  9, WR},    { -1, QR} }
            };
            // Morphem initialisieren:
            lexedMorphem = new Morphem();
            lexedMorphem.Init();
            ReadNext();
        }

        /// <summary>
        /// Gibt das nächste Morhpem aus.
        /// </summary>
        /// <returns>Das nächste Morphem.</returns>
        public Morphem NextMorphem() {
            // Starte immer im Zustand Z0 und setze Morphem und temporären String zurück:
            currentState = 0;
            lexedMorphem.Reset();
            tempMorphemString = "";
            int currentCategory;
            // Während aktueller Zustand noch ein gültiger Zustand ist:
            while (currentState > -1) {
                // Aufhören, wenn ungültiges (nicht-ASCII) Zeichen oder EOF
                if (charCategoryTable.Length < currentCharCode || currentCharCode < 0) {
                    break;
                }
                currentCategory = charCategoryTable[currentCharCode];
                // Aktion abhängig vom dem entsprechenden Tabelleneintrag:
                ((ActionDelegate)categoryNextActionTable[currentState, currentCategory, 1])();
                // Nächsten Zustand setzen (abhängig vom aktuellen Zustand und Zeichen):
                currentState = (int)categoryNextActionTable[currentState, currentCategory, 0];
            }
            return lexedMorphem;
        }

        /// <summary>
        /// Das nächste Zeichen lesen.
        /// </summary>
        private void ReadNext() {
            // 10='\n': newline
            if (currentCharCode == 10) {
                // nächste Zeile (Zeile erhöhen, Spalte zurücksetzen)
                lexedMorphem.position[0] = 1;
                lexedMorphem.position[1]++;
            } else {
                lexedMorphem.position[0]++;
            }
            currentCharCode = fileReader.Read();
        }

        /// <summary>
        /// Buchstaben als Großbuchstaben im Morphem speichern, dann nächstes lesen.
        /// </summary>
        private void WriteCharReadNext() {
            tempMorphemString += ((char)currentCharCode).ToString().ToUpper();
            ReadNext();
        }

        /// <summary>
        /// Zeichen im Morphem speichern, dann nächstes lesen.
        /// </summary>
        private void WriteReadNext() {
            tempMorphemString += ((char)currentCharCode).ToString();
            ReadNext();
        }

        /// <summary>
        /// Zeichen in Morphem speichern, nächstes lesen und abschließen.
        /// </summary>
        private void WriteReadNextFinish() {
            WriteReadNext();
            FinishMorphem();
        }

        /// <summary>
        /// Nächstes abschließen und nächstes Morphem überspringen.
        /// </summary>
        private void FinishReadNext() {
            FinishMorphem();
            ReadNext();
        }

        /// <summary>
        /// Morphem abschließen: Je nach aktuellen Status und Schlüsselwort-Klassifizierung als Symbol, Nummer oder Identifikator speichern.
        /// </summary>
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
                case 9: // String
                    lexedMorphem.Strings = tempMorphemString;
                    break;
                case 2: // Zahl
                    lexedMorphem.Number = int.Parse(tempMorphemString);
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

        /// <summary>
        /// Prüft, ob übergebene Zeichenkette ein Schlüsselwort ist.
        /// </summary>
        /// <param name="morphemString">Zeichenkette, die zu überprüfen ist.</param>
        /// <returns>true: wenn Zeichenkette Schlüsselwort ist. false: sonst.</returns>
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
    }
}
