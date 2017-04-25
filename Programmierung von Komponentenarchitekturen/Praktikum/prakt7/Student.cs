using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    abstract class Student : HSMitglied {
        public Student(string preName, string surName, DateTime birthday, CreateID createID) : base(preName, surName, birthday, createID) {
        }

        public override void printPerson() {
            Console.WriteLine(PreName + " " + SurName + " " + Birthday.ToString("dd.MM.yyyy") + " (" + Uid + ")");
        }
    }
}
