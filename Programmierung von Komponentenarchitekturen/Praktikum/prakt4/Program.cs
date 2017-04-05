using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt4 {
    class Program {
        static void Main(string[] args) {
            Person ich = new Person("Falk-Jonatan", "Strube", DateTime.Parse("1800-01-02"));
            ich.printPerson();
        }
    }

    class Person {
        public String PreName { get; private set; }
        public String SurName { get; private set; }
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
        public Person(String preName, String surName, DateTime birthday) {
            Console.WriteLine("Erstelle Person "+preName+" "+surName+" (geboren: "+birthday.ToShortDateString()+")");
            PreName = preName;
            SurName = surName;
            Birthday = birthday;
        }

        public void printPerson() {
            Console.WriteLine("Person " + PreName + " " + SurName + ", Alter: " + Math.Floor((DateTime.Today - Birthday).TotalDays / 365));
        }
    }
}
