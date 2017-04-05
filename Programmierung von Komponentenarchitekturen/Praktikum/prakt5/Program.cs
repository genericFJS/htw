using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt5 {
    class Program {
        static void Main(string[] args) {
            Bruch b1 = new Bruch(1, 2);
            Bruch b2 = new Bruch(1, 3);
            Console.WriteLine("{0} < {1} = {2}", b1, b2, b1 < b2);
            Console.WriteLine("{0} > {1} = {2}", b1, b2, b1 > b2);
        }
    }

    class Bruch : IComparable {
        public int Zaehler { get; private set; }
        public int Nenner { get; private set; }
        public Bruch(int z, int n) {
            Zaehler = z;
            Nenner = n;
        }



        public override string ToString() {
            return "" + Zaehler + "/" + Nenner;
        }

        public static Boolean operator <(Bruch b1, Bruch b2) {
            return b1.CompareTo(b2) < 0;
        }
        public static Boolean operator >(Bruch b1, Bruch b2) {
            return b1.CompareTo(b2) > 0;
        }

        public int CompareTo(object obj) {
            Bruch objBruch = (Bruch)obj;
            double objVal = (double)objBruch.Zaehler / objBruch.Nenner;
            double myVal = (double)Zaehler / Nenner;
            if (objVal == myVal) {
                return 0;
            } else {
                if (objVal < myVal) {
                    return 1;
                } else {
                    return -1;
                }
            }
        }
    }
}
