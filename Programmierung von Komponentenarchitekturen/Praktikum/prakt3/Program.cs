using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BombLibrary;


namespace prakt3 {
    class Program {
        static void Main(string[] args) {
            // Console.WriteLine(Bomb.defuseBomb(0L));
            long password = 0;  // wahrscheinlich nur positive Zahlen
            Console.WriteLine("Suche nach Code zum Entschärfen (while-Schleife):");
            while (String.Equals(Bomb.defuseBomb(password), Bomb.defuseBomb(0L))) {
                password++;
            }
            Console.WriteLine("Entschärfe mit: "+password);
            password = 0;
            Console.WriteLine("Suche nach Code zum Entschärfen (for-Schleife):");
            for (; String.Equals(Bomb.defuseBomb(password), Bomb.defuseBomb(0L)); password++) { }
            Console.WriteLine("Entschärfe mit: " + password);
        }
    }
}
