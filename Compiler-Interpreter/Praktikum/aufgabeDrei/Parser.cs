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
        private Morphem currentMorphem = new Morphem();
        private Lexer lexer;

        // Code-Generator
        private CodeGenerator codeGenerator;

        // Definition Namensliste:
        private NamelistProcedure currentProcedure = new NamelistProcedure();
        // Zwischenspeicher Konstanten/Variablen/Prozedur-Name
        private String currentName;
        // Zwischenspeicher Condition
        private CommandCode currentCondition;
        // Prozedurzähler
        private int numberOfProcedures = 1;
        // Constantenliste
        private List<NamelistConstant> constantList = new List<NamelistConstant>();
        // Labelliste
        private List<NamelistLabel> labelList = new List<NamelistLabel>();

        // Größe eines Wertes in der Virtuellen Maschine (4 Byte)
        private static readonly int VALUE_SIZE = 4;

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
            conditionGraph[3] = new Edge(EdgeType.symbol, "=", new ActionDelegate(ConditionSaveEQ), 9, 4);
            conditionGraph[4] = new Edge(EdgeType.symbol, "#", new ActionDelegate(ConditionSaveNE), 9, 5);
            conditionGraph[5] = new Edge(EdgeType.symbol, "<", new ActionDelegate(ConditionSaveLT), 9, 6);
            conditionGraph[6] = new Edge(EdgeType.symbol, "<=", new ActionDelegate(ConditionSaveLE), 9, 7);
            conditionGraph[7] = new Edge(EdgeType.symbol, ">", new ActionDelegate(ConditionSaveGT), 9, 8);
            conditionGraph[8] = new Edge(EdgeType.symbol, ">=", new ActionDelegate(ConditionSaveGE), 9, -1);
            conditionGraph[9] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(ConditionApplyOperand), -1, -1);

            currentMorphem.Init();
            lexer = new Lexer(filePath);

            codeGenerator = new CodeGenerator(filePath);
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
                switch (currentEdge.type) {
                    case EdgeType.blank:
                        success = true;
                        break;
                    case EdgeType.symbol:
                        success = (currentMorphem.code == MorphemCode.symbol && currentMorphem.GetValue().ToUpper() == currentEdge.getValue().ToUpper());
                        break;
                    case EdgeType.morphem:
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
                        PrintError("Fehler in Zeile ", currentMorphem.position[1], " (Spalte " + currentMorphem.position[0] + "). Habe " + currentEdge.getValue() + " erwartet");
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
                        PrintProgressA("", currentMorphem.GetValue(), " konsumiert");
                        currentMorphem = lexer.NextMorphem();
                        if (currentMorphem.GetValue() != null) {
                            PrintProgressB(" (Nächstes: ", currentMorphem.GetValue(), ").");
                        } else {
                            PrintProgressB("", "", ". Kein weiteres Zeichen mehr zu lesen.");
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
            PrintCodeGen("\tProgrammEnd");
            // Mainprozedur beenden.
            BlockEndProcedure();
            // Konstantenblock schreiben.
            codeGenerator.GenerateConstantBlock(constantList);
            // Fertig kompilierten Code schreiben.
            codeGenerator.WriteCodeToFile();
            return true;
        }

        // Bogenfunktionen Block:
        // ------------------------------------------------------------
        private bool BlockCheckConstIdentifier() {
            String name = currentMorphem.GetValue();
            PrintCodeGen("\tBlockCheckConstIdentifier " + name);
            if (currentProcedure.HasEntry(name)) {
                PrintError("Der Bezeichner ", name, " existiert bereits in diesem Kontext.");
                return false;
            }
            currentName = name;
            return true;
        }

        private bool BlockCheckConstValue() {
            PrintCodeGen("\tBlockCheckConstValue " + currentMorphem.GetValue());
            int value = currentMorphem.GetValue();
            // Index des Konstantenwerts herausfinden.
            int index = FindConstantValuePosition(value);
            // Bei neuem Wert, neuen Eintrag in Konstantenliste anlegen.
            if (index < 0) {
                // Index berechnet sich aus der Größe der Konstantenliste und der Größe einer Konstante.
                index = constantList.Count() * VALUE_SIZE;
                // Konstantenliste um neuen Eintrag ergänzen.
                constantList.Add(new NamelistConstant(currentProcedure.ProcedureID, currentName, value, index));
            }
            // Konstante in Namensliste der aktuellen Prozedur einfügen.
            currentProcedure.namelist.Add(new NamelistConstant(currentProcedure.ProcedureID, currentName, value, index));
            return true;
        }

        private bool BlockCheckVarIdentifier() {
            String name = currentMorphem.GetValue();
            PrintCodeGen("\tBlockCheckVarIdentifier " + name);
            if (currentProcedure.HasEntry(name)) {
                PrintError("Der Bezeichner ", name, " existiert bereits in diesem Kontext.");
                return false;
            }
            // Variable in Namenliste der aktuellen Prozedur einfügen
            currentProcedure.namelist.Add(new NamelistVariable(currentProcedure.ProcedureID, name, currentProcedure.nextVariableAdress));
            // Relativadresse für nächsten Eintrag erhöhen.
            currentProcedure.nextVariableAdress += VALUE_SIZE;
            return true;
        }

        private bool BlockCheckProcedureIdentifer() {
            String name = currentMorphem.GetValue();
            PrintCodeGen("\tBlockCheckProcedureIdentifer " + name);
            if (currentProcedure.HasEntry(name)) {
                PrintError("Der Bezeichner ", name, " existiert bereits in diesem Kontext.");
                return false;
            }
            // Prozedur in Namenliste der aktuellen Prozedur einfügen.
            currentProcedure.namelist.Add(new NamelistProcedure(currentProcedure.ProcedureID, name, numberOfProcedures, currentProcedure));
            // Prozedurzähler erhöhen.
            numberOfProcedures++;
            // Neue Prozedur ist jetzt aktuelle Prozedur.
            currentProcedure = (NamelistProcedure)currentProcedure.namelist.Last<NamelistEntry>();
            return true;
        }

        private bool BlockEnterStatement() {
            PrintCodeGen("\tBlockEnterStatement " + currentProcedure.Name);
            // Generiere entryProc mit zunächst unbekannter Länge, der Prozedur-ID und die Größe des Variablenbereichs.
            codeGenerator.GenerateCode(CommandCode.entryProc, 0, currentProcedure.ProcedureID, currentProcedure.nextVariableAdress);
            return true;
        }

        private bool BlockEndProcedure() {
            PrintCodeGen("\tBlockEndProcedure " + currentProcedure.Name);
            // Generiere retProc.
            codeGenerator.GenerateCode(CommandCode.retProc);
            // Aktualisiere die Prozedurlänge
            codeGenerator.UpdateProcedureLength();
            // Namenliste der Prozedur löschen
            currentProcedure.namelist.Clear();
            // Elternprozedur ist nun aktuelle Prozedur
            currentProcedure = currentProcedure.ParentProcedure;
            return true;
        }

        // Bogenfunktionen Statement:
        // ------------------------------------------------------------
        private bool StatementCheckVarIdentifier() {
            PrintCodeGen("\tStatementCheckVarIdentifier");
            return true;
        }

        private bool StatementCheckVarValue() {
            PrintCodeGen("\tStatementCheckVarValue");
            return true;
        }

        private bool StatementIfCondition() {
            PrintCodeGen("\tStatementIfCondition");
            return true;
        }

        private bool StatementIfStatement() {
            PrintCodeGen("\tStatementIfStatement");
            return true;
        }

        private bool StatementWhile() {
            PrintCodeGen("\tStatementWhile");
            return true;
        }

        private bool StatementWhileCondition() {
            PrintCodeGen("\tStatementWhileCondition");
            return true;
        }

        private bool StatementWhileStatement() {
            PrintCodeGen("\tStatementWhileStatement");
            return true;
        }

        private bool StatementProcedureCall() {
            PrintCodeGen("\tStatementProcedureCall");
            return true;
        }

        private bool StatementInput() {
            PrintCodeGen("\tStatementInput");
            return true;
        }

        private bool StatementOutputExpression() {
            PrintCodeGen("\tStatementOutputExpression");
            return true;
        }

        private bool StatementOutputString() {
            PrintCodeGen("\tStatementOutputString");
            return true;
        }

        // Bogenfunktionen Expression:
        // ------------------------------------------------------------
        private bool ExpressionNegative() {
            PrintCodeGen("\tExpressionNegative");
            // Generiere vzMinus, um negativen Term anzukündigen.
            codeGenerator.GenerateCode(CommandCode.vzMinus);
            return true;
        }

        private bool ExpressionAddition() {
            PrintCodeGen("\tExpressionAddition");
            // Generiere opAdd, um weiter Terme zu addieren.
            codeGenerator.GenerateCode(CommandCode.opAdd);
            return true;
        }

        private bool ExpressionSubtraction() {
            PrintCodeGen("\tExpressionSubtraction");
            // Generiere opSub, um weiter Terme zu subtrahieren.
            codeGenerator.GenerateCode(CommandCode.opSub);
            return true;
        }

        // Bogenfunktionen Term:
        // ------------------------------------------------------------
        private bool TermMultiplication() {
            PrintCodeGen("\tTermMultiplication");
            // Generiere opMul, um weiter Faktoren zu multiplizieren.
            codeGenerator.GenerateCode(CommandCode.opSub);
            return true;
        }

        private bool TermDivision() {
            PrintCodeGen("\tTermDivision");
            // Generiere opDiv, um weiter Faktoren zu dividieren.
            codeGenerator.GenerateCode(CommandCode.opDiv);
            return true;
        }

        // Bogenfunktionen Factor:
        // ------------------------------------------------------------
        private bool FactorCheckNumber() {
            PrintCodeGen("\tFactorCheckNumber " + currentMorphem.GetValue());
            // Konstante suchen und ggf. anlegen.

            // Codegenerierung puConst(ConstIndex) mit dem Index der Konstante.

            return true;
        }

        private bool FactorCheckIdentifier() {
            PrintCodeGen("\tFactorCheckIdentifier " + currentMorphem.GetValue());
            // Identifier global suchen.

            // Überprüfen, ob Identifier eine Variable/Konstante

            // Codegenerierung abhängig vom Fundort:
            return true;
        }

        // Bogenfunktionen Condition:
        // ------------------------------------------------------------
        private bool ConditionOdd() {
            PrintCodeGen("\tConditionOdd");
            // Generiere odd, um einfachen Ungerade-Vergleich durchzuführen.
            codeGenerator.GenerateCode(CommandCode.odd);
            return true;
        }

        private bool ConditionSaveEQ() {
            PrintCodeGen("\tConditionSaveEQ");
            // Speichere Vergleichsoperator
            currentCondition = CommandCode.cmpEQ;
            return true;
        }

        private bool ConditionSaveNE() {
            PrintCodeGen("\tConditionSaveNE");
            // Speichere Vergleichsoperator
            currentCondition = CommandCode.cmpNE;
            return true;
        }

        private bool ConditionSaveLT() {
            PrintCodeGen("\tConditionSaveLT");
            // Speichere Vergleichsoperator
            currentCondition = CommandCode.cmpLT;
            return true;
        }

        private bool ConditionSaveLE() {
            PrintCodeGen("\tConditionSaveLE");
            // Speichere Vergleichsoperator
            currentCondition = CommandCode.cmpLE;
            return true;
        }

        private bool ConditionSaveGT() {
            PrintCodeGen("\tConditionSaveGT");
            // Speichere Vergleichsoperator
            currentCondition = CommandCode.cmpGT;
            return true;
        }

        private bool ConditionSaveGE() {
            PrintCodeGen("\tConditionSaveGE");
            // Speichere Vergleichsoperator
            currentCondition = CommandCode.cmpGE;
            return true;
        }

        private bool ConditionApplyOperand() {
            PrintCodeGen("\tConditionApplyOperand");
            // Generiere gespeicherten Operand, um Vergleich auszuwerten.
            codeGenerator.GenerateCode(currentCondition);
            return true;
        }

        // ============================================================
        // Codegenerierung Hilfsfunktionen
        // ============================================================
        /// <summary>
        /// Findet die Position der Konstanten in der Konstantenliste, falls vorhanden.
        /// Ist Null, wenn Wert noch nicht existiert.
        /// </summary>
        /// <returns></returns>
        int FindConstantValuePosition(int value) {
            foreach (var entry in constantList) {
                if (entry.Value == value)
                    return entry.Index;
            }
            return -1;
        }

        // ============================================================
        // Ausgabe Hilfsfunktionen
        // ============================================================
        public static void PrintProgressA(String a, dynamic b, String c) {
            Console.Write(a);
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write(b);
            Console.ResetColor();
            Console.Write(c);
        }

        public static void PrintProgressB(String a, dynamic b, String c) {
            Console.Write(a);
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.Write(b);
            Console.ResetColor();
            Console.WriteLine(c);
        }

        public static void PrintError(String a, dynamic b, String c) {
            Console.Write(a);
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Write(b);
            Console.ResetColor();
            Console.WriteLine(c);
        }

        public static void PrintCodeGen(String a) {
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine(a);
            Console.ResetColor();
        }

    }
}
