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
