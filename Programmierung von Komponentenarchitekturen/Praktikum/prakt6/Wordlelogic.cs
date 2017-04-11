using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt6 {
    class CountedElement<T> : IComparable {
        public T Elem { get; private set; }
        public int Count { get; set; }

        public CountedElement(T firstelem) {
            Elem = firstelem;
            Count = 1;
        }

        public override string ToString() {
            return Count + " - " + Elem;
        }

        public int CompareTo(object otherCountedElement) {
            int ret = 0;
            if (this.Count < ((CountedElement<T>)otherCountedElement).Count)
                ret = 1;
            else if (this.Count > ((CountedElement<T>)otherCountedElement).Count)
                ret = -1;
            return ret;
        }
    }

    class CountedList<T> : List<CountedElement<T>> {
        public override string ToString() {
            string ret = "";
            foreach (var elem in this) {
                ret += elem.ToString() + "\n";
            }
            return ret;
        }

        public void addCountedElement(T elem) {
            foreach (CountedElement<T> searchelem in this) {
                if (searchelem.Elem.Equals(elem)) {
                    // Console.WriteLine("Element "+elem+" bereits in Liste, Zähler wird erhöht.");
                    searchelem.Count++;
                    return;
                }
            }
            this.Add(new CountedElement<T>(elem));
        }
    }

    class Wordlelogic {
        static void Main(string[] args) {
            CountedList<string> wordle = new CountedList<string>();
            wordle.addCountedElement("wordle");
            wordle.addCountedElement("wordle");
            wordle.addCountedElement("wordle");
            wordle.addCountedElement("wordle");
            wordle.addCountedElement("wordle");
            wordle.addCountedElement("wordle");
            wordle.addCountedElement("word");
            wordle.addCountedElement("word");
            wordle.addCountedElement("word");
            wordle.addCountedElement("word");
            wordle.addCountedElement("generic");
            wordle.addCountedElement("generic");
            while (true) {
                string[] entries = Console.ReadLine().Split(' ');
                foreach (var entry in entries) {
                    if (entry.Length > 3)
                        wordle.addCountedElement(entry);
                }
                wordle.Sort();
                Console.WriteLine(wordle.ToString());
            }
        }
    }
}
