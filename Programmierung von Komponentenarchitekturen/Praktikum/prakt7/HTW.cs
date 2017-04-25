using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    class HTW : Student {
        static int newStudentNumber = 11110;
        public HTW(string preName, string surName, DateTime birthday, CreateID createID) : base(preName, surName, birthday, createID) {
        }
        
        public HTW(string preName, string surName, DateTime birthday) : this(preName, surName, birthday, HTW.CreateCustomID) {
        }

        public static String CreateCustomID() {
            String theID = newStudentNumber.ToString();
            newStudentNumber++;
            return theID;
        }
    }
}
