using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    class Mitarbeiter : HSMitglied {
        public Mitarbeiter(string preName, string surName, DateTime birthday) : base(preName, surName, birthday, Mitarbeiter.CreateCustomID) {
        }

        public static String CreateCustomID() {
            return "";
        }

        public override void printPerson() {
            Console.WriteLine(PreName + " " + SurName + " " + Birthday.ToString("dd.MM.yyyy") + " (Mitarbeiter)");
        }
    }
}
