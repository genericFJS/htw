using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
    /// <summary>
    /// Abstrakter Eintrag in der Namensliste enthält den Typ (
    /// </summary>
    abstract class NamelistEntry {
        // ID der Prozedur, in der Eintrag existiert.
        public int MemberProcedureID { protected set; get; }
        public String Name { protected set; get; }
    }

    class NamelistVariable : NamelistEntry {
        public int Displacement { private set; get; }

        public NamelistVariable(int memberProcedureID, String name, int displacement) {
            MemberProcedureID = memberProcedureID;
            Name = name;
            Displacement = displacement;
        }
    }

    class NamelistConstant : NamelistEntry {
        public int Value { private set; get; }
        public int Index { private set; get; }

        public NamelistConstant(int memberProcedureID, String name, int value, int index) {
            MemberProcedureID = memberProcedureID;
            Name = name;
            Value = value;
            Index = index;
        }
    }

    class NamelistProcedure : NamelistEntry {
        // ID der Prozedur. Nicht zu verwechseln mit der memberProcedureID, die angibt, in welcher Prozedur diese Prozedur existiert.
        public int ProcedureID { private set; get; }
        public NamelistProcedure ParentProcedure { private set; get; }
        public List<NamelistEntry> namelist;
        public int nextVariableAdress;

        /// <summary>
        /// Allgemeiner Konstruktor für neue Prozedureinträge.
        /// </summary>
        /// <param name="memberProcedureID"></param>
        /// <param name="name"></param>
        /// <param name="procedureID"></param>
        /// <param name="parentProcedure"></param>
        public NamelistProcedure(int memberProcedureID, String name, int procedureID, NamelistProcedure parentProcedure) {
            Init(memberProcedureID, name, procedureID, parentProcedure);
        }

        /// <summary>
        /// Konstruktor für die main-Prozedur.
        /// </summary>
        public NamelistProcedure() {
            Init(-1, "***main***", 0, null);
        }

        private void Init(int memberProcedureID, String name, int procedureID, NamelistProcedure parentProcedure) {
            MemberProcedureID = memberProcedureID;
            Name = name;
            ProcedureID = procedureID;
            ParentProcedure = parentProcedure;
            this.namelist = new List<NamelistEntry>();
            this.nextVariableAdress = 0;
        }

        public bool HasEntry(String name) {
            foreach (var entry in namelist) {
                if (entry.Name == name) {
                    return true;
                }
            }
            return false;
        }
    }
}
