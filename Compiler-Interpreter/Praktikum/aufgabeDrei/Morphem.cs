using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
	struct Morphem {
		// Gibt an, welche Art von Morhpem vorliegt:
		public MorphemCode code { get; private set; }
		// Die Position des Morphems im Quelltext [Zeile, Spalte]:
		public int[] position;
		// Der Wert, wenn Morphem eine Zeichenkette ist (Symbol/Identifier):
		string stringValue;
		// Der Wert, wenn Morphem eine Zahl ist:
		int numberValue;
		// Beim setzen eines Morphemwerts wird der Code automatisch angepasst:
		public string Symbol {
			get { return stringValue; }
			set { stringValue = value; code = MorphemCode.symbol; }
		}
		public string Identifier {
			get { return stringValue; }
			set { stringValue = value; code = MorphemCode.identifier; }
        }
        public int Number {
            get { return numberValue; }
            set { numberValue = value; code = MorphemCode.number; }
        }
        public string Strings {
            get { return stringValue; }
            set { stringValue = value; code = MorphemCode.strings; }
        }
        // Rückgabe des Morphemwerts abhängig vom Code:
        public dynamic GetValue() {
			switch (code) {
				case MorphemCode.empty:
					return null;
				case MorphemCode.identifier:
				case MorphemCode.symbol:
                case MorphemCode.strings:
					return stringValue;
                case MorphemCode.number:
                    return numberValue;
                default:
					return "none";
			}
		}
		// Initialisierung des Morphems:
		public void Init() {
			Reset();
			position = new int[] { 1, 1 };
		}
		// Zurücksetzen des Morphems (beim Lesen des nächsten Morphems):
		public void Reset() {
			code = MorphemCode.empty;
		}
	}

	enum MorphemCode {
		empty,
		symbol,
		number,
		identifier,
        strings,
		invalid
	}
}
