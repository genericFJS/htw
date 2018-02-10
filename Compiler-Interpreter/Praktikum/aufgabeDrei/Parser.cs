using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {
    class Parser {
        private delegate bool ActionDelegate();

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
            public EdgeType type;
            // Mögliche Kanten-Werte:
            private string symbol;
            private MorphemCode morphemCode;
            private Edge[] graph;
            // Folgeaktion:
            public ActionDelegate action;
            // Nächste/alterantive Kante
            public int nextEdge;
            public int alternativeEdge;

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
                        return symbol.ToUpper();
                    case EdgeType.morphem:
                        return morphemCode;
                    case EdgeType.graph:
                        return graph;
                }
                return null;
            }
        }

        // Definition der Bögen:
        private Edge[] programmGraph = new Edge[2];
        private Edge[] blockGraph = new Edge[22];
        private Edge[] statementGraph = new Edge[23];
        private Edge[] expressionGraph = new Edge[10];
        private Edge[] termGraph = new Edge[7];
        private Edge[] factorGraph = new Edge[5];
        private Edge[] conditionGraph = new Edge[10];

        // Definiton Morphem:
        Morphem currentMorphem;
        Lexer lexer;

        public Parser(string filePath) {
            // Initialisierung der Bögen:
            // Alternative Bögen -1: es existiert keine Alternative (oder ist letzte Alternative)
            // Nächster Bögen -1: es existiert kein nächster Bogen => Ende vom Graph
            programmGraph[0] = new Edge(EdgeType.graph, blockGraph, null, 1, -1);
            programmGraph[1] = new Edge(EdgeType.symbol, ".", new ActionDelegate(ProgrammEnd), -1, -1);

            blockGraph[0] = new Edge(EdgeType.symbol, "const", null, 1, 7); // Bögen const
            blockGraph[1] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckConstIdentifier), 2, -1);
            blockGraph[2] = new Edge(EdgeType.symbol, "=", null, 3, -1);
            blockGraph[3] = new Edge(EdgeType.morphem, MorphemCode.number, new ActionDelegate(BlockCheckConstValue), 4, -1);
            blockGraph[4] = new Edge(EdgeType.symbol, ",", null, 1, 5);
            blockGraph[5] = new Edge(EdgeType.symbol, ";", null, 6, -1);
            blockGraph[6] = new Edge(EdgeType.blank, null, null, 8, -1);
            blockGraph[7] = new Edge(EdgeType.blank, null, null, 8, -1);
            blockGraph[8] = new Edge(EdgeType.symbol, "var", null, 9, 13); // Bögen var
            blockGraph[9] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckVarIdentifier), 10, -1);
            blockGraph[10] = new Edge(EdgeType.symbol, ",", null, 9, 11);
            blockGraph[11] = new Edge(EdgeType.symbol, ";", null, 12, -1);
            blockGraph[12] = new Edge(EdgeType.blank, null, null, 14, -1);
            blockGraph[13] = new Edge(EdgeType.blank, null, null, 14, -1);
            blockGraph[14] = new Edge(EdgeType.symbol, "procedure", null, 15, 20); // Bögen procedure
            blockGraph[15] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckProcedureIdentifer), 16, -1);
            blockGraph[16] = new Edge(EdgeType.symbol, ";", null, 17, -1);
            blockGraph[17] = new Edge(EdgeType.graph, blockGraph, null, 18, -1);
            blockGraph[18] = new Edge(EdgeType.symbol, ";", new ActionDelegate(BlockEndProcedure), 19, -1);
            blockGraph[19] = new Edge(EdgeType.blank, null, null, 14, 20);
            blockGraph[20] = new Edge(EdgeType.blank, null, new ActionDelegate(BlockEnterStatement), 21, -1); // Zum statement
            blockGraph[21] = new Edge(EdgeType.graph, statementGraph, null, -1, -1);

            statementGraph[0] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementCheckVarIdentifier), 1, 3); // Bögen var
            statementGraph[1] = new Edge(EdgeType.symbol, ":=", null, 2, -1);
            statementGraph[2] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(StatementCheckVarValue), -1, -1);
            statementGraph[3] = new Edge(EdgeType.symbol, "if", null, 4, 7); // Bögen if
            statementGraph[4] = new Edge(EdgeType.graph, conditionGraph, new ActionDelegate(StatementIfCondition), 5, -1);
            statementGraph[5] = new Edge(EdgeType.symbol, "then", null, 6, -1);
            statementGraph[6] = new Edge(EdgeType.graph, statementGraph, new ActionDelegate(StatementIfStatement), -1, -1);
            statementGraph[7] = new Edge(EdgeType.symbol, "while", new ActionDelegate(StatementWhile), 8, 11); // Bögen while
            statementGraph[8] = new Edge(EdgeType.graph, conditionGraph, new ActionDelegate(StatementWhileCondition), 9, -1);
            statementGraph[9] = new Edge(EdgeType.symbol, "do", null, 10, -1);
            statementGraph[10] = new Edge(EdgeType.graph, statementGraph, new ActionDelegate(StatementWhileStatement), -1, -1);
            statementGraph[11] = new Edge(EdgeType.symbol, "begin", null, 12, 15); // Bögen codeblock
            statementGraph[12] = new Edge(EdgeType.graph, statementGraph, null, 13, 14);
            statementGraph[13] = new Edge(EdgeType.symbol, ";", null, 12, 14);
            statementGraph[14] = new Edge(EdgeType.symbol, "end", null, -1, -1);
            statementGraph[15] = new Edge(EdgeType.symbol, "call", null, 16, 17); // Bögen call
            statementGraph[16] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementProcedureCall), -1, -1);
            statementGraph[17] = new Edge(EdgeType.symbol, "?", null, 18, 19);  // Bögen input
            statementGraph[18] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementInput), -1, -1);
            statementGraph[19] = new Edge(EdgeType.symbol, "!", null, 22, 21);  // Bögen output
            statementGraph[20] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(StatementOutputExpression), -1, -1);
            statementGraph[21] = new Edge(EdgeType.blank, null, null, -1, -1);
            statementGraph[22] = new Edge(EdgeType.morphem, MorphemCode.strings, new ActionDelegate(StatementOutputString), -1, 20); // Erweiterung output String

            expressionGraph[0] = new Edge(EdgeType.symbol, "-", null, 1, 2);    // Bögen negative term
            expressionGraph[1] = new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionNegative), 4, -1);
            expressionGraph[2] = new Edge(EdgeType.blank, null, null, 3, -1);   // Bögen normal term
            expressionGraph[3] = new Edge(EdgeType.graph, termGraph, null, 4, -1);
            expressionGraph[4] = new Edge(EdgeType.blank, null, null, 5, -1);
            expressionGraph[5] = new Edge(EdgeType.symbol, "+", null, 6, 7);   // Bögen addition
            expressionGraph[6] = new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionAddition), 4, -1);
            expressionGraph[7] = new Edge(EdgeType.symbol, "-", null, 8, 9);   // Bögen subtraction
            expressionGraph[8] = new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionSubtraction), 4, -1);
            expressionGraph[9] = new Edge(EdgeType.blank, null, null, -1, -1);

            termGraph[0] = new Edge(EdgeType.graph, factorGraph, null, 1, -1);
            termGraph[1] = new Edge(EdgeType.blank, null, null, 2, -1);
            termGraph[2] = new Edge(EdgeType.symbol, "*", null, 3, 4);   // Bögen multiplication
            termGraph[3] = new Edge(EdgeType.graph, factorGraph, new ActionDelegate(TermMultiplication), 1, -1);
            termGraph[4] = new Edge(EdgeType.symbol, "/", null, 5, 6);    // Bögen division
            termGraph[5] = new Edge(EdgeType.graph, factorGraph, new ActionDelegate(TermDivision), 1, -1);
            termGraph[6] = new Edge(EdgeType.blank, null, null, -1, -1);

            factorGraph[0] = new Edge(EdgeType.morphem, MorphemCode.number, new ActionDelegate(FactorCheckNumber), -1, 1);  // Bogen numeral
            factorGraph[1] = new Edge(EdgeType.symbol, "(", null, 2, 4);    // Bögen braced
            factorGraph[2] = new Edge(EdgeType.graph, expressionGraph, null, 3, -1);
            factorGraph[3] = new Edge(EdgeType.symbol, ")", null, -1, -1);
            factorGraph[4] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(FactorCheckIdentifier), -1, -1);  // Bogen identifier

            conditionGraph[0] = new Edge(EdgeType.symbol, "odd", null, 1, 2);  // Bögen odd
            conditionGraph[1] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(ConditionOdd), -1, -1);
            conditionGraph[2] = new Edge(EdgeType.graph, expressionGraph, null, 3, -1);    // Bögen comparsion
            conditionGraph[3] = new Edge(EdgeType.symbol, "=", new ActionDelegate(ConditionSaveEq), 9, 4);
            conditionGraph[4] = new Edge(EdgeType.symbol, "#", new ActionDelegate(ConditionSaveNo), 9, 5);
            conditionGraph[5] = new Edge(EdgeType.symbol, "<", new ActionDelegate(ConditionSaveLt), 9, 6);
            conditionGraph[6] = new Edge(EdgeType.symbol, "<=", new ActionDelegate(ConditionSaveLeq), 9, 7);
            conditionGraph[7] = new Edge(EdgeType.symbol, ">", new ActionDelegate(ConditionSaveGt), 9, 8);
            conditionGraph[8] = new Edge(EdgeType.symbol, ">=", new ActionDelegate(ConditionSaveGeq), 9, -1);
            conditionGraph[9] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(ConditionApplyOperand), -1, -1);

            currentMorphem = new Morphem();
            currentMorphem.Init();
            lexer = new Lexer(filePath);
        }

        public bool Parse() {
            if (Parse(programmGraph)) {
                return true;
            } else {
                return false;
            }
        }

        private bool Parse(Edge[] currentGraph) {
            int currentEdgeNumber = 0;
            bool success = false;
            Edge currentEdge;
            if (currentMorphem.code == MorphemCode.empty)
                currentMorphem = lexer.NextMorphem();
            while (true) {
                currentEdge = currentGraph[currentEdgeNumber];
                //Console.WriteLine("\tType von currentEdge(" + currentEdgeNumber + ") aus currentGraph: " + currentEdge.type);
                switch (currentEdge.type) {
                    case EdgeType.blank:
                        success = true;
                        break;
                    case EdgeType.symbol:
                        //Console.WriteLine(currentMorphem.getValue() + " vs(symbol) " + currentEdge.getValue());
                        success = (currentMorphem.code == MorphemCode.symbol && currentMorphem.getValue().ToUpper() == currentEdge.getValue().ToUpper());
                        break;
                    case EdgeType.morphem:
                        //Console.WriteLine(currentMorphem.code + " vs(morphem) " + currentEdge.getValue());
                        success = (currentMorphem.code == currentEdge.getValue());
                        break;
                    case EdgeType.graph:
                        success = Parse(currentEdge.getValue());
                        break;
                }
                if (!success) {
                    // Bei nicht passendem Bogen Alternativbogen ausprobieren (falls vorhanden).
                    if (currentEdge.alternativeEdge != -1)
                        currentEdgeNumber = currentEdge.alternativeEdge;
                    else {
                        Console.WriteLine("Fehler in Zeile " + currentMorphem.position[1] + ", Spalte " + currentMorphem.position[0] + " (Habe " + currentEdge.getValue() + " erwartet)");
                        return false;
                    }
                } else {
                    // Codegenerierungsfunktion aufrufen, falls vorhanden. Bei Fehlschlag parsen beenden.
                    if (currentEdge.action != null) {
                        if (!((ActionDelegate)currentEdge.action)())
                            return false;
                    }
                    // Gegebenenfalls Symbol/Morphem akzeptieren und nächstes holen.
                    if (currentEdge.type == EdgeType.symbol || currentEdge.type == EdgeType.morphem) {
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.Write(currentMorphem.getValue());
                        Console.ResetColor();
                        Console.Write(" konsumiert");
                        currentMorphem = lexer.NextMorphem();
                        if (currentMorphem.getValue() != null) {
                            Console.Write(" (Nächstes: ");
                            Console.ForegroundColor = ConsoleColor.DarkYellow;
                            Console.Write(currentMorphem.getValue());
                            Console.ResetColor();
                            Console.WriteLine(").");
                        } else { 
                        Console.WriteLine(". Kein weiteres Zeichen mehr zu lesen.");
                    }
                    }
                    // Wenn der letzte Bogen akzeptiert wurde, beenden.
                    if (currentEdge.nextEdge == -1)
                        return true;
                    // Nächste Kante untersuchen
                    currentEdgeNumber = currentEdge.nextEdge;
                }
            }
        }

        // ============================================================
        // Bogenfunktionen
        // ============================================================

        // Bogenfunktionen Programm:
        // ------------------------------------------------------------
        private bool ProgrammEnd() {
            Console.WriteLine("ProgrammEnd");
            return true;
        }

        // Bogenfunktionen Block:
        // ------------------------------------------------------------
        private bool BlockCheckConstIdentifier() {
            Console.WriteLine("BlockCheckConstIdentifier");
            return true;
        }

        private bool BlockCheckConstValue() {
            Console.WriteLine("BlockCheckConstValue");
            return true;
        }

        private bool BlockCheckVarIdentifier() {
            Console.WriteLine("BlockCheckVarIdentifier");
            return true;
        }

        private bool BlockCheckProcedureIdentifer() {
            Console.WriteLine("BlockCheckProcedureIdentifer");
            return true;
        }

        private bool BlockEndProcedure() {
            Console.WriteLine("BlockEndProcedure");
            return true;
        }

        private bool BlockEnterStatement() {
            Console.WriteLine("BlockEnterStatement");
            return true;
        }

        // Bogenfunktionen Statement:
        // ------------------------------------------------------------
        private bool StatementCheckVarIdentifier() {
            Console.WriteLine("StatementCheckVarIdentifier");
            return true;
        }

        private bool StatementCheckVarValue() {
            Console.WriteLine("StatementCheckVarValue");
            return true;
        }

        private bool StatementIfCondition() {
            Console.WriteLine("StatementIfCondition");
            return true;
        }

        private bool StatementIfStatement() {
            Console.WriteLine("StatementIfStatement");
            return true;
        }

        private bool StatementWhile() {
            Console.WriteLine("StatementWhile");
            return true;
        }

        private bool StatementWhileCondition() {
            Console.WriteLine("StatementWhileCondition");
            return true;
        }

        private bool StatementWhileStatement() {
            Console.WriteLine("StatementWhileStatement");
            return true;
        }

        private bool StatementProcedureCall() {
            Console.WriteLine("StatementProcedureCall");
            return true;
        }

        private bool StatementInput() {
            Console.WriteLine("StatementInput");
            return true;
        }

        private bool StatementOutputExpression() {
            Console.WriteLine("StatementOutputExpression");
            return true;
        }

        private bool StatementOutputString() {
            Console.WriteLine("StatementOutputString");
            return true;
        }

        // Bogenfunktionen Expression:
        // ------------------------------------------------------------
        private bool ExpressionNegative() {
            Console.WriteLine("ExpressionNegative");
            return true;
        }

        private bool ExpressionAddition() {
            Console.WriteLine("ExpressionAddition");
            return true;
        }

        private bool ExpressionSubtraction() {
            Console.WriteLine("ExpressionSubtraction");
            return true;
        }

        // Bogenfunktionen Term:
        // ------------------------------------------------------------
        private bool TermMultiplication() {
            Console.WriteLine("TermMultiplication");
            return true;
        }

        private bool TermDivision() {
            Console.WriteLine("TermDivision");
            return true;
        }

        // Bogenfunktionen Factor:
        // ------------------------------------------------------------
        private bool FactorCheckNumber() {
            Console.WriteLine("FactorCheckNumber");
            return true;
        }

        private bool FactorCheckIdentifier() {
            Console.WriteLine("FactorCheckIdentifier");
            return true;
        }

        // Bogenfunktionen Condition:
        // ------------------------------------------------------------
        private bool ConditionOdd() {
            Console.WriteLine("ConditionOdd");
            return true;
        }

        private bool ConditionSaveEq() {
            Console.WriteLine("ConditionSaveEq");
            return true;
        }

        private bool ConditionSaveNo() {
            Console.WriteLine("ConditionSaveNo");
            return true;
        }

        private bool ConditionSaveLt() {
            Console.WriteLine("ConditionSaveLt");
            return true;
        }

        private bool ConditionSaveLeq() {
            Console.WriteLine("ConditionSaveLeq");
            return true;
        }

        private bool ConditionSaveGt() {
            Console.WriteLine("ConditionSaveGt");
            return true;
        }

        private bool ConditionSaveGeq() {
            Console.WriteLine("ConditionSaveGeq");
            return true;
        }

        private bool ConditionApplyOperand() {
            Console.WriteLine("ConditionApplyOperand");
            return true;
        }


    }
}
