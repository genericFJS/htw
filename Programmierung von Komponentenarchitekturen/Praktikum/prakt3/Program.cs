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
            while (String.Equals(Bomb.defuseBomb(password), Bomb.defuseBomb(0L))) {
                password++;
            }
            Console.WriteLine("Entschärfe mit (durch while-Schleife gefunden): "+password);
            password = 0;
            for (; String.Equals(Bomb.defuseBomb(password), Bomb.defuseBomb(0L)); password++) { }
            Console.WriteLine("Entschärfe mit (mit for-Schleife gefunden): " + password);
        }
    }
}
