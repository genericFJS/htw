using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    class UniWien : Student {
        static int newStudentNumber = 1;
        public UniWien(string preName, string surName, DateTime birthday, createID createID) : base(preName, surName, birthday, createID) {
        }
    }
}
