// Code von Falk-Jonatan Strube (mail@fj-strube.de)
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL0Compiler {
    /// <summary>
    /// Abstrakter Eintrag in der Namensliste enthält:
    /// - ID der Prozedur, in der der Eintrag existiert.
    /// - Bezeichnung des Eintrags.
    /// </summary>
    abstract class NamelistEntry {
        public int MemberProcedureID { protected set; get; }
        public String Name { protected set; get; }
    }

    /// <summary>
    /// Variable in der Namenliste. Enthält deren Verschiebung.
    /// </summary>
    class NamelistVariable : NamelistEntry {
        public int Displacement { private set; get; }

        /// <summary>
        /// Weist dem Variableneintrag alle benötigten Werte zu.
        /// </summary>
        /// <param name="memberProcedureID">ID der Prozedur, in der der Variableneintrag existiert</param>
        /// <param name="name">Bezeichnung der Variable</param>
        /// <param name="displacement">Verschiebung der Variable</param>
        public NamelistVariable(int memberProcedureID, String name, int displacement) {
            MemberProcedureID = memberProcedureID;
            Name = name;
            Displacement = displacement;
        }
    }

    /// <summary>
    /// Konstante in der Namenliste. Enthält deren Wert und Index.
    /// </summary>
    class NamelistConstant : NamelistEntry {
        public int Value { private set; get; }
        public int Index { private set; get; }

        /// <summary>
        /// Weist dem Konstaneneintrag alle benötigten Werte zu.
        /// </summary>
        /// <param name="memberProcedureID">ID der Prozedur, in der der Konstanteneintrag existiert</param>
        /// <param name="name">Bezeichnung der Konstanten</param>
        /// <param name="value">Wert der Konstanten</param>
        /// <param name="index">Index der Konstanten</param>
        public NamelistConstant(int memberProcedureID, String name, int value, int index) {
            MemberProcedureID = memberProcedureID;
            Name = name;
            Value = value;
            Index = index;
        }
    }

    /// <summary>
    /// Prozedur in der Namensliste. Enthält die ID der Prozedur, die Elternprozedur, eine eigene Namenliste und die größe des Variablenspeichers.
    /// </summary>
    class NamelistProcedure : NamelistEntry {
        // ID der Prozedur. Nicht zu verwechseln mit der memberProcedureID, die angibt, in welcher Prozedur diese Prozedur existiert.
        public int ProcedureID { private set; get; }
        public NamelistProcedure ParentProcedure { private set; get; }
        public List<NamelistEntry> namelist;
        public int variablesMemorySize;

        /// <summary>
        /// Weist dem Prozedureintrag alle benötigten Werte zu.
        /// </summary>
        /// <param name="memberProcedureID">ID der Prozedur, in der der Prozedureinträg existiert</param>
        /// <param name="name">Bezeichnung der Prozedur</param>
        /// <param name="procedureID">ID der Prozedur</param>
        /// <param name="parentProcedure">Elternprozedur</param>
        public NamelistProcedure(int memberProcedureID, String name, int procedureID, NamelistProcedure parentProcedure) {
            Init(memberProcedureID, name, procedureID, parentProcedure);
        }

        /// <summary>
        /// Konstruktor für die main-Prozedur setzt die benötigten Werte fest.
        /// </summary>
        public NamelistProcedure() {
            Init(-1, "***main***", 0, null);
        }

        /// <summary>
        /// Weise dem Prozess die Werte zu.
        /// </summary>
        /// <param name="memberProcedureID">ID der Prozedur, in der der Prozedureinträg existiert</param>
        /// <param name="name">Bezeichnung der Prozedur</param>
        /// <param name="procedureID">ID der Prozedur</param>
        /// <param name="parentProcedure">Elternprozedur</param>
        private void Init(int memberProcedureID, String name, int procedureID, NamelistProcedure parentProcedure) {
            MemberProcedureID = memberProcedureID;
            Name = name;
            ProcedureID = procedureID;
            ParentProcedure = parentProcedure;
            this.namelist = new List<NamelistEntry>();
            this.variablesMemorySize = 0;
        }

        /// <summary>
        /// Überprüft, ob die Prozedur einen Eintrag in seiner Namenliste mit der entsprechenden Bezeichnung hat.
        /// </summary>
        /// <param name="name">Zu überprüfende Bezeichnung</param>
        /// <returns></returns>
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
