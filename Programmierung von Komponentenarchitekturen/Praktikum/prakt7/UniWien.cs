using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    class UniWien : Student {
        static int newStudentNumber = 0;
        
        public UniWien(string preName, string surName, DateTime birthday, int immaYear) : base(preName, surName, birthday, UniWien.CreateCustomID) {

        }

        public static String CreateCustomID() {
            String theID = "99"+"0"+ newStudentNumber.ToString().PadLeft(4, '0'); // immaYear wird weg gelassen :D
            newStudentNumber++;
            return theID;
        }
    }
}
