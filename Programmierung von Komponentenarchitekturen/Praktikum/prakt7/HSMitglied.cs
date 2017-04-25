using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace prakt7 {
    public delegate String CreateID();

    abstract class HSMitglied : Person {
        public string Uid { get; }

        public HSMitglied(string preName, string surName, DateTime birthday, CreateID createID) : base(preName, surName, birthday) {
            Uid = createID();
        }
    }
}
