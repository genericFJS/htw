using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeEins {
    class Program {
        //        typedef struct morph {
        //            int mc;     // morphem-code (siehe unten)
        //            double dval;    // Zahl (wenn Zahl)
        //            char cval;  // Zeichen (wenn Operand)
        //        }
        //        MORPHEM;
        public struct Morphem {
            public MorphemCode mCode;
            public double doubleValue;
            public char charValue;
        }
        //enum mcodes {
        //            mempty, // leer
        //            mop,    // Operant
        //            mdbl    // Zahl (ggf. "." für Gleitkomma)
        //        };
        public enum MorphemCode {
            mEmpty,
            mOperand,
            mDouble
        }
        //        static MORPHEM m;
        static Morphem morphem;
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
        //                    m.dval = strtod(px, &px);   // Setze dval auf zu Zahl konvertierten Char (setzt auch Pointer weiter)
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
        public static void InitLex() {
            morphem.mCode = MorphemCode.mEmpty;
        }

        public static List<char> Lex(List<char> charList) {
            if (!charList.Any()) {  // leer?
                morphem.mCode = MorphemCode.mEmpty;
            } else {
                while (charList.ElementAt(0) == ' ' || charList.ElementAt(0) == '\t')
                    charList.RemoveAt(0);
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

        //        double term(void) {
        //            double tmp = fac(); // Faktor berechnen
        //            if (m.mc == mop && m.cval == '*') { // wenn aktuelle Stelle Operand * ist:
        //                lex(NULL);
        //                tmp *= term();  // Multipliziere mit Term
        //            }
        //            return tmp;
        //        }

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
            InitLex();
            double result = 0;
            //lex( inputExpression );
            Console.WriteLine("Eingabe:  " + inputString);
            Console.WriteLine("Ergebnis: " + result);
            // Tests:
            Console.WriteLine("========================");
            inputCharList = Lex(inputCharList);
            inputCharList.ForEach(delegate (char theChar)
            {
                Console.Write(theChar);
            });
            Console.Write("\n");
        }
    }
}
