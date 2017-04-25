using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    class Inheritance {
        static void Main(string[] args) {
            Person[] persons = new Person[6];
            persons[0] = new HTW("Karl", "Kurz", DateTime.Parse("01.02.1988"));
            persons[1] = new HTW("Karl", "Kürzer", DateTime.Parse("01.02.1989"));
            persons[2] = new UniWien("Luzie", "Lang", DateTime.Parse("2.1.1977"), 2016);
            persons[3] = new UniWien("Luzie", "Länger", DateTime.Parse("2.1.1978"), 2015);
            persons[4] = new Mitarbeiter("Bert", "Breit", DateTime.Parse("2.1.1968"));
            persons[5] = new Mitarbeiter("Berrt", "Breiter", DateTime.Parse("2.1.1969"));
            
            foreach(var person in persons) {
                person.printPerson();
            }
        }
    }
}
