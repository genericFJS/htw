using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    abstract class HSMitglied : Person {
        public string Uid { get; }

        public delegate String createID();

        public HSMitglied(string preName, string surName, DateTime birthday, createID createID) : base(preName, surName, birthday) {
            Uid = createID();
        }
    }
}
