// Code von Falk-Jonatan Strube (mail@fj-strube.de)
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL0Compiler {
    /// <summary>
    /// Das Morphem ist das Ergebnis der lexikalischen Analyse. Es ist ein "Wort".
    /// Zugunsten der Fehlersuche wird die Position mit gespeichert - im Fehlerfall kann sie ausgegeben werden.
    /// </summary>
    struct Morphem {
        // Gibt an, welche Art von Morhpem vorliegt.
        public MorphemCode Code { get; private set; }
        // Die Position des Morphems im Quelltext [Zeile, Spalte].
        public int[] position;
        // Wert des Morphems.
        public dynamic Value { get; private set; }
        // Beim setzen eines Morphemwerts wird der Code automatisch angepasst.
        public string Symbol {
            get { return Value; }
            set { Value = value; Code = MorphemCode.symbol; }
        }
        public string Identifier {
            get { return Value; }
            set { Value = value; Code = MorphemCode.identifier; }
        }
        public int Number {
            get { return Value; }
            set { Value = value; Code = MorphemCode.number; }
        }
        public string Strings {
            get { return Value; }
            set { Value = value; Code = MorphemCode.strings; }
        }
        // Initialisierung des Morphems.
        public Morphem(bool init) {
            Code = MorphemCode.empty;
            Value = null;
            position = new int[] { 1, 1 };
        }
        // Zurücksetzen des Morphems (beim Lesen des nächsten Morphems).
        public void Reset() {
            Code = MorphemCode.empty;
        }
    }

    /// <summary>
    /// Art des Morphems.
    /// </summary>
    enum MorphemCode {
        empty,
        symbol,
        number,
        identifier,
        strings,
        invalid
    }
}
