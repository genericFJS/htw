using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    abstract class Person { // abstract: Person kann nicht erzeugt werden, sie muss in neuer Klasse durch Vererbung genutzt werden
        public String PreName { get; set; }
        public String SurName { get; set; }
        public DateTime birthday;
        public DateTime Birthday {
            get {
                return birthday;
            }
            set {
                DateTime correctValue = value;
                while (correctValue.Year < 1900) {
                    Console.WriteLine("Geburtstag vor 1900, bitte erneut eingeben:");
                    correctValue = DateTime.Parse(Console.ReadLine());
                }
                birthday = correctValue;
            }
        }
        public Person() { }

        public Person (string preName, string surName, DateTime birthday) {
            this.PreName = preName;
            this.SurName = surName;
            this.Birthday = birthday;
        }

        public virtual void printPerson() {
            Console.WriteLine("Person " + PreName + " " + SurName + ", Alter: " + Math.Floor((DateTime.Today - Birthday).TotalDays / 365));
        }
    }
}
