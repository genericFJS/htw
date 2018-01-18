using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
    class Parser {
        private delegate void ActionDelegate();

        /// <summary>
        /// Art der Kante.
        /// </summary>
        private enum EdgeType {
            blank,      // Leer
            symbol,     // Symbol
            morphem,    // Morphem
            graph       // Graph
        }

        /// <summary>
        /// Stellt eine Kante dar. 
        /// </summary>
        private struct Edge {
            EdgeType type;
            // Mögliche Kanten-Werte:
            private string symbol;
            private MorphemCode morphemCode;
            private Edge[] graph;
            // Folgeaktion:
            ActionDelegate action;
            // Nächste/alterantive Kante
            int nextEdge;
            int alternativeEdge;

            /// <summary>
            /// Erstellt neue Kante.
            /// </summary>
            /// <param name="newType"> Typ der Kante </param>
            /// <param name="newValue"> Wert der Kante (Symbol/Morphemcode/Graph)</param>
            /// <param name="newAction"> Aktion der Kante</param>
            /// <param name="newNextEdge"> Nächste Kante </param>
            /// <param name="newAlternativeEdge"> Kantenalternativen </param>
            public Edge(EdgeType newType, dynamic newValue, ActionDelegate newAction, int newNextEdge, int newAlternativeEdge) {
                type = newType;
                symbol = null;
                morphemCode = MorphemCode.invalid;
                graph = null;
                switch (newType) {
                    case EdgeType.symbol:
                        symbol = (string)newValue;
                        break;
                    case EdgeType.morphem:
                        morphemCode = (MorphemCode)newValue;
                        break;
                    case EdgeType.graph:
                        graph = (Edge[])newValue;
                        break;
                }
                action = newAction;
                nextEdge = newNextEdge;
                alternativeEdge = newAlternativeEdge;
            }

            /// <summary>
            /// Gibt den Wert der Kante wieder.
            /// </summary>
            /// <returns> Wert der Kante abhängig vom Typ (Symbol/Morphemcode/Graph). </returns>
            public dynamic getValue() {
                switch (type) {
                    case EdgeType.symbol:
                        return symbol;
                    case EdgeType.morphem:
                        return morphemCode;
                    case EdgeType.graph:
                        return graph;
                }
                return null;
            }
        }

        // Definition der Bögen:
        private Edge[] programmGraph;
        private Edge[] blockGraph;
        private Edge[] statementGraph;
        private Edge[] expressionGraph;
        private Edge[] termGraph;
        private Edge[] factorGraph;
        private Edge[] conditionGraph;

        private Morphem currentMorphem;

        public Parser() {
            // Initialisierung der Bögen:
            // Alternative Bögen -1: es existiert keine Alternative (oder ist letzte Alternative)
            // Nächster Bögen -1: es existiert kein nächster Bogen => Ende vom Graph
            programmGraph = new Edge[2] {
				/* 0 */ new Edge(EdgeType.graph,  blockGraph, null,                             1, -1),
				/* 1 */ new Edge(EdgeType.symbol, ".",        new ActionDelegate(ProgrammEnd), -1, -1)
                };

            blockGraph = new Edge[22] {
				/*  0 */ new Edge(EdgeType.symbol, "const", null, 1, 7), // Bögen const
				/*  1 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckConstIdentifier), 2, -1),
				/*  2 */ new Edge(EdgeType.symbol, "=", null, 3, -1),
				/*  3 */ new Edge(EdgeType.morphem, MorphemCode.number, new ActionDelegate(BlockCheckConstValue), 4, -1),
				/*  4 */ new Edge(EdgeType.symbol, ",", null, 1, 5),
				/*  5 */ new Edge(EdgeType.symbol, ";", null, 6, -1),
				/*  6 */ new Edge(EdgeType.blank, null, null, 8, -1),
				/*  7 */ new Edge(EdgeType.blank, null, null, 8, -1),
				/*  8 */ new Edge(EdgeType.symbol, "var", null, 9, 13), // Bögen var
				/*  9 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckVarIdentifier),10, -1),
				/* 10 */ new Edge(EdgeType.symbol, ",", null, 9, 11),
				/* 11 */ new Edge(EdgeType.symbol, ";", null, 12, -1),
				/* 12 */ new Edge(EdgeType.blank, null, null, 14, -1),
				/* 13 */ new Edge(EdgeType.blank, null, null, 14, -1),
				/* 14 */ new Edge(EdgeType.symbol, "procedure", null,  15, -1), // Bögen procedure
				/* 15 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckProcedureIdentifer), 16, -1),
				/* 16 */ new Edge(EdgeType.symbol, ";", null, 17, -1),
				/* 17 */ new Edge(EdgeType.graph, blockGraph, null, 18, -1),
				/* 18 */ new Edge(EdgeType.symbol, ";", new ActionDelegate(BlockEndProcedure), 19, -1),
				/* 19 */ new Edge(EdgeType.blank, null, null, 20, -1),
				/* 20 */ new Edge(EdgeType.blank, null, new ActionDelegate(BlockEnterStatement), 21, -1), // Zum statement
				/* 21 */ new Edge(EdgeType.graph, statementGraph, null, -1, -1)
                };
            statementGraph = new Edge[22] {
				/*  0 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementCheckVarIdentifier), 1, 3), // Bögen var
				/*  1 */ new Edge(EdgeType.symbol, ":=", null, 2, -1),
				/*  2 */ new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(StatementCheckVarValue), -1, -1),
				/*  3 */ new Edge(EdgeType.symbol, "if", null, 4, 7), // Bögen if
				/*  4 */ new Edge(EdgeType.graph, conditionGraph, new ActionDelegate(StatementIfCondition), 5, -1),
				/*  5 */ new Edge(EdgeType.symbol, "then" , null, 6, -1),
				/*  6 */ new Edge(EdgeType.graph, statementGraph, new ActionDelegate(StatementIfStatement), -1, -1),
				/*  7 */ new Edge(EdgeType.symbol, "while", new ActionDelegate(StatementWhile), 8, 11), // Bögen while
				/*  8 */ new Edge(EdgeType.graph, conditionGraph, new ActionDelegate(StatementWhileCondition), 9, -1),
				/*  9 */ new Edge(EdgeType.symbol, "do", null, 10, -1),
				/* 10 */ new Edge(EdgeType.graph, statementGraph, new ActionDelegate(StatementWhileStatement), -1, -1),
				/* 11 */ new Edge(EdgeType.symbol, "begin", null, 12, 15), // Bögen codeblock
				/* 12 */ new Edge(EdgeType.graph, statementGraph, null, 14, 13),
				/* 13 */ new Edge(EdgeType.symbol, ";", null, 12, -1),
				/* 14 */ new Edge(EdgeType.symbol, "end", null, -1, -1),
				/* 15 */ new Edge(EdgeType.symbol, "call", null, 16, 17), // Bögen call
				/* 16 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementProcedureCall), -1, -1),
				/* 17 */ new Edge(EdgeType.symbol, "?", null, 18, 19),  // Bögen input
				/* 18 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementInput), -1, -1),
				/* 19 */ new Edge(EdgeType.symbol, "!", null, 20, 21),  // Bögen output
				/* 20 */ new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(StatementOutput), -1, -1),
				/* 21 */ new Edge(EdgeType.blank, null, null, -1, -1)
            };
            expressionGraph = new Edge[10] {
				/*  0 */ new Edge(EdgeType.symbol, "-", null, 1, 2),    // Bögen negative term
				/*  1 */ new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionNegative), 4, -1),
				/*  2 */ new Edge(EdgeType.blank, null, null, 3, -1),   // Bögen normal term
				/*  3 */ new Edge(EdgeType.graph, termGraph, null, 4, -1),
				/*  4 */ new Edge(EdgeType.blank, null, null, 5, -1),
				/*  5 */ new Edge(EdgeType.symbol, "+", null, 6, 7),   // Bögen addition
				/*  6 */ new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionAddition), 4, -1),
				/*  7 */ new Edge(EdgeType.symbol, "-", null, 8, 9),   // Bögen subtraction
				/*  8 */ new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionSubtraction), 4, -1),
				/*  9 */ new Edge(EdgeType.blank, null, null, -1, -1)
            };
            termGraph = new Edge[7] {
				/*  0 */ new Edge(EdgeType.graph, factorGraph, null, 1, -1),
				/*  1 */ new Edge(EdgeType.blank, null, null, 2, -1),
				/*  2 */ new Edge(EdgeType.symbol, "*", null, 3, 4),    // Bögen multiplication
				/*  3 */ new Edge(EdgeType.graph, factorGraph, new ActionDelegate(TermMultiplication), 1, -1),
				/*  4 */ new Edge(EdgeType.symbol, "/", null, 5, 6),    // Bögen division
				/*  5 */ new Edge(EdgeType.graph, factorGraph, new ActionDelegate(TermDivision), 1, -1),
				/*  6 */ new Edge(EdgeType.blank, null, null, -1, -1)
            };
            factorGraph = new Edge[5] {
				/*  0 */ new Edge(EdgeType.morphem, MorphemCode.number, new ActionDelegate(FactorCheckNumber), -1, 1),  // Bogen numeral
				/*  1 */ new Edge(EdgeType.symbol, "(", null, 2, 4),    // Bögen braced
				/*  2 */ new Edge(EdgeType.graph, expressionGraph, null, 3, -1),
				/*  3 */ new Edge(EdgeType.symbol, ")", null, -1, -1),
				/*  4 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(FactorCheckIdentifier), -1, -1)  // Bogen identifier
            };
            conditionGraph = new Edge[10] {
				/*  0 */ new Edge(EdgeType.symbol, "odd", null, 1, 2),  // Bögen odd
				/*  1 */ new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(ConditionOdd), -1, -1),
				/*  2 */ new Edge(EdgeType.graph, expressionGraph, null, 3, -1),    // Bögen comparsion
				/*  3 */ new Edge(EdgeType.symbol, "=", new ActionDelegate(ConditionSaveEq), 9, 4),
				/*  4 */ new Edge(EdgeType.symbol, "#", new ActionDelegate(ConditionSaveNo), 9, 5),
				/*  5 */ new Edge(EdgeType.symbol, "<", new ActionDelegate(ConditionSaveLt), 9, 6),
				/*  6 */ new Edge(EdgeType.symbol, "<=", new ActionDelegate(ConditionSaveLeq), 9, 7),
				/*  7 */ new Edge(EdgeType.symbol, ">", new ActionDelegate(ConditionSaveGt), 9, 8),
				/*  8 */ new Edge(EdgeType.symbol, ">=", new ActionDelegate(ConditionSaveGeq), 9, -1),
				/*  9 */ new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(ConditionApplyOperand), -1, -1)
            };
        }

        public int Parse() {
            int success = 0;

            return success;
        }

        // ============================================================
        // Bogenfunktionen
        // ============================================================

        // Bogenfunktionen Programm:
        // ------------------------------------------------------------
        private void ProgrammEnd() {

        }

        // Bogenfunktionen Block:
        // ------------------------------------------------------------
        private void BlockCheckConstIdentifier() {

        }

        private void BlockCheckConstValue() {

        }

        private void BlockCheckVarIdentifier() {

        }

        private void BlockCheckProcedureIdentifer() {

        }

        private void BlockEndProcedure() {

        }

        private void BlockEnterStatement() {

        }

        // Bogenfunktionen Statement:
        // ------------------------------------------------------------
        private void StatementCheckVarIdentifier() {

        }

        private void StatementCheckVarValue() {

        }

        private void StatementIfCondition() {

        }

        private void StatementIfStatement() {

        }

        private void StatementWhile() {

        }

        private void StatementWhileCondition() {

        }

        private void StatementWhileStatement() {

        }

        private void StatementProcedureCall() {

        }

        private void StatementInput() {

        }

        private void StatementOutput() {

        }

        // Bogenfunktionen Expression:
        // ------------------------------------------------------------
        private void ExpressionNegative() {

        }

        private void ExpressionAddition() {

        }

        private void ExpressionSubtraction() {

        }

        // Bogenfunktionen Term:
        // ------------------------------------------------------------
        private void TermMultiplication() {

        }

        private void TermDivision() {

        }

        // Bogenfunktionen Factor:
        // ------------------------------------------------------------
        private void FactorCheckNumber() {

        }

        private void FactorCheckIdentifier() {

        }

        // Bogenfunktionen Condition:
        // ------------------------------------------------------------
        private void ConditionOdd() {

        }

        private void ConditionSaveEq() {

        }

        private void ConditionSaveNo() {

        }

        private void ConditionSaveLt() {

        }

        private void ConditionSaveLeq() {

        }

        private void ConditionSaveGt() {

        }

        private void ConditionSaveGeq() {

        }

        private void ConditionApplyOperand() {

        }


    }
}
