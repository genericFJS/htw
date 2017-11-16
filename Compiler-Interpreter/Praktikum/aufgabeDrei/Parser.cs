using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
	class Parser {

		/// <summary>
		/// Art der Kante.
		/// </summary>
		private enum EdgeType {
			blank,		// Leer
			symbol,		// Symbol
			morphem,	// Morphem
			graph,		// Graph
			end			// Ende
		}

		private struct Edge {
			EdgeType type;

		}

	}
}
