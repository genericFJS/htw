using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Praktikum1 {
    class Program {
        static void Main(string[] args) {
            Console.WriteLine("Hello World");
            // Aufgabe 1
            var a = 2L;
            var b = 1.23456f;
            var c = 0302;
            var d = 100UL;
            var e = .1e-5;
            var f = 0x10;
            var g = 0xFL;
            Console.WriteLine("a: " + a + " (" + a.GetType() + ")");
            Console.WriteLine("b: " + b + " (" + b.GetType() + ")");
            Console.WriteLine("c: " + c + " (" + c.GetType() + ")");
            Console.WriteLine("d: " + d + " (" + d.GetType() + ")");
            Console.WriteLine("e: " + e + " (" + e.GetType() + ")");
            Console.WriteLine("f: " + f + " (" + f.GetType() + ")");
            Console.WriteLine("g: " + g + " (" + g.GetType() + ")");

            // Aufgabe 2
            int n, i; // nicht doppelt int
            double sideLength;  // kein Leerzeichen in Variablenname
            double slow_down = .1e-4;   // Zahlen nicht in Anführungszeichen
            double[] min = new double[5]; // Klammer bei Deklaration falsch, Initialisierung des Arrays nicht min Array-Name sondern mit neuem Datentyp-Objekt
            double voidV = 1.23;    // Variablenname darf kein Keyword sein

            // Aufgabe 3
            // n=15, n+=25
            //  n1=40
            // n%9
            //  n2=4
            // n=5, n++
            //  n3=5 (erst Ausgabe, dann zusammenrechnen)
            // n*n, ++n (vor Ausgabe zusammenrechnen)
            //  n4=37
            n = 15;
            n += 25;
            Console.WriteLine("{0}", n);
            n %= 9;
            Console.WriteLine("{0}", n);
            n = 5;
            Console.WriteLine("{0}", n++);
            n *= n;
            Console.WriteLine("{0}", ++n);

            // Aufgabe 4
            // (1): (a)
            // (2): (b) (ruft wieder (a))
            // (3): (e) (ruft wieder (a))
            // (4): (c) // wegen using math1
            // (5): (d)

            // Aufgabe 5
            // a: Deklaration der Variable w (darf noch nicht existieren) vom Typ widget
            // b: Deklaration der Funktion w mit Ausgabe widget (die null ist… widget ist also Referenztyp)
            // c: Abkürzung für einen getter (geht auch für setter) für die Variable w bei der Deklaration
            // d: Cast des Typs widget auf die Variable w
            // e: Deklaration und Initialisierung der Variable w vom Typ widget mit Wert x
            // f: implizie Delkaration der Variable w mit Wert x
        }
    }
}