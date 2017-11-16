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
		double numberValue;
		// Beim setzen eines Morphemwerts wird der Code automatisch angepasst:
		public string Symbol {
			get { return stringValue; }
			set { stringValue = value; code = MorphemCode.symbol; }
		}
		public string Identifier {
			get { return stringValue; }
			set { stringValue = value; code = MorphemCode.identifier; }
		}
		public double Number {
			get { return numberValue; }
			set { numberValue = value; code = MorphemCode.number; }
		}
		// Rückgabe des Morphemwerts abhängig vom Code:
		public dynamic getValue() {
			switch (code) {
				case MorphemCode.empty:
					return null;
				case MorphemCode.identifier:
				case MorphemCode.symbol:
					return stringValue;
				case MorphemCode.number:
					return numberValue;
				default:
					return "none";
			}
		}
		// Initialisierung des Morphems (bei einem neuen Lexer):
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
	}
}
