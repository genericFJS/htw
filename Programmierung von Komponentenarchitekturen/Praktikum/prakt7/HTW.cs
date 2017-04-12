using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    class HTW : Student {
        static int newStudentNumber = 11110;
        public HTW(string preName, string surName, DateTime birthday, createID createID) : base(preName, surName, birthday, createID) {
        }
    }
}
