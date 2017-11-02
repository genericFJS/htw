using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeEins {
    class Program {

        struct Unlexed {
            public MorphemCode currentMorphem;
            private double currentDouble;
            private char currentChar;
            public double CurrentDouble {
                get; private set;
            }
            public char CurrentChar {
                get; private set;
            }
            public List<char> remainingChars;

            public void RemoveLeadingWhitespace() {
                while (remainingChars.Any() && (remainingChars.ElementAt(0) == ' ' || remainingChars.ElementAt(0) == '\t'))
                    remainingChars.RemoveAt(0);
            }
            public void ParseDouble() {

            }
        }

        enum MorphemCode {
            mEmpty,
            mOperand,
            mDouble
        }

        static Unlexed unlexed;

        //        void lex(char* pX) {
        //            static char* px;
        //            /* Initialisierung (wird nur beim ersten Aufruf (mit Eingabezeile) aufgerufen): */
        //            if (pX != NULL) {
        //                m.mc = mempty;
        //                px = pX;
        //            }
        //            /* lexikalische Analyse (sonst) */
        //            // wenn EOL: leer
        //            if (*px == '\0') {
        //                m.mc = mempty;
        //            } else {
        //                // überspringe Leerzeichen/Tabulatoren
        //                for (; *px == ' ' || *px == '\t'; px++) ;
        //                // Wenn nächstes Zeichen Zahl (oder Float-Seperator) ist: 
        //                if (isdigit(*px) || *px == '.') {
        //                    m.dval = strtod(px, &px);   // Setze dval auf zu Zahl konvertierten Char (verschiebt Pointer nach Zahl)
        //                    m.mc = mdbl;
        //                } else
        //                    switch (*px) {
        //                        case '+':
        //                        case '-':
        //                        case '*':
        //                        case '/':
        //                        case '(':
        //                        case ')':
        //                            m.cval = *px++; // Setze cval auf den entsprechenden Char (und setze Pointer weiter)
        //                            m.mc = mop;
        //                            break;
        //                        default:
        //                            printf("wrong ...: %c\n­ canceling  ­­\n", *px);
        //                            exit(1);
        //                    }
        //            }
        //        }

        static void initLexer(List<char> charList) {
            unlexed.currentMorphem = MorphemCode.mEmpty;
            unlexed.remainingChars = charList;
        }

        public static List<char> Lex() {
            if (!unlexed.remainingChars.Any()) {
                unlexed.currentMorphem = MorphemCode.mEmpty;
            } else {
                // führende Leerzeichen/Tabs entfernen:
                unlexed.RemoveLeadingWhitespace();
                if (System.Char.IsDigit(unlexed.remainingChars[0])) {
                    unlexed.ParseDouble();
                } else {
                    switch (unlexed.remainingChars[0]) {
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '(':
                        case ')':
                            morphem.charValue = charList[0];
                            charList.RemoveAt(0);
                            morphem.mCode = MorphemCode.mOperand;
                            break;
                        default:
                            Console.WriteLine("Falsche Eingabe '{0}'!\n Abbruch.\n", charList[0]);
                            Environment.Exit(1);
                            break;
                    }
                }
            }
            return charList;
        }

        //        double fac() {
        //            double tmp;
        //            if (m.mc == mop) {  // wenn Operand, dann Klammer berücksichtigen:
        //                if (m.cval == '(') {
        //                    lex(NULL);
        //                    tmp = expr();
        //                    if (m.mc != mop || m.cval != ')')
        //                        exit(1);
        //                    lex(NULL);
        //                } else
        //                    exit(1);
        //            } else
        //                if (m.mc == mdbl) {
        //                tmp = m.dval;
        //                lex(NULL);
        //            } else
        //                exit(1);
        //            return tmp;
        //        }
        public static double fac() {
            if (morphem.mCode == MorphemCode.mOperand) {
                if (morphem.charValue == '(') {

                }
            }
            return 0;
        }

        //        double term(void) {
        //            double tmp = fac(); // Faktor berechnen
        //            if (m.mc == mop && m.cval == '*') { // wenn aktuelle Stelle Operand * ist:
        //                lex(NULL);
        //                tmp *= term();  // Multipliziere mit Term
        //            }
        //            return tmp;
        //        }

        public static double Expression(Unlexed unlexed) {

            return 0;
        }
        //        double expr(void) {
        //            double tmp = term();    // Term berechnen
        //            if (m.mc == mop && m.cval == '+') { // wenn aktuelle Stelle Operand + ist:
        //                lex(NULL);
        //                tmp += expr();  // Addiere Expression
        //            }
        //            return tmp;
        //        }


        //        int main(int argc, char* argv[]) {
        //            char* pBuf = argv[1];
        //            printf("%s\n", pBuf);
        //            lex(pBuf);
        //            printf("%lf\n", expr());
        //            return 0;
        //        }
        static void Main(string[] args) {
            Console.WriteLine("Gib eine Rechnung ein:");
            String inputString = Console.ReadLine();
            List<char> inputCharList = new List<char>();
            inputCharList.AddRange(inputString);
            InitLex(inputCharList);
            double result = 0;
            //lex( inputExpression );
            Console.WriteLine("Eingabe:  " + inputString);
            Console.WriteLine("Ergebnis: " + result);
            // Tests:
            Console.WriteLine("========================");
            inputCharList = Lex(inputCharList);
            inputCharList.ForEach(delegate (char theChar) {
                Console.Write(theChar);
            });
            Console.Write("\n");
        }
    }
}
