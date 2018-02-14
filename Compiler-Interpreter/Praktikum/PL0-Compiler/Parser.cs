// Code von Falk-Jonatan Strube (mail@fj-strube.de)
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL0Compiler {
    /// <summary>
    /// Der Parser parst den Code. Dazu wird eine lexikalische Analyse durchgeführt und die korrekte Grammatik erkannt.
    /// Dieser Parser leitet weiterhin Aktionen an den Codegenerator weiter, damit der passende Code dazu generiert werden kann.
    /// </summary>
    class Parser {
        // Delegate für die (potentielle) Aktion einer Kante.
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
        /// Stellt eine Kante in einem Graphen dar. 
        /// </summary>
        private struct Edge {
            public EdgeType Type { private set; get; }
            // Mögliche Kanten-Werte.
            public dynamic Value { private set; get; }
            // Folgeaktion.
            public ActionDelegate Action { private set; get; }
            // Nächste/alterantive Kante.
            public int NextEdge { private set; get; }
            public int AlternativeEdge { private set; get; }

            /// <summary>
            /// Erstellt neue Kante.
            /// </summary>
            /// <param name="newType">Typ der Kante</param>
            /// <param name="newValue">Wert der Kante (Symbol/Morphemcode/Graph)</param>
            /// <param name="newAction">Aktion der Kante</param>
            /// <param name="newNextEdge">Folgekante</param>
            /// <param name="newAlternativeEdge">Kantenalternative</param>
            public Edge(EdgeType newType, dynamic newValue, ActionDelegate newAction, int newNextEdge, int newAlternativeEdge) {
                Type = newType;
                Value = newValue;
                Action = newAction;
                NextEdge = newNextEdge;
                AlternativeEdge = newAlternativeEdge;
            }
        }

        // Größe der Graphen.
        private const int PROGRAMMGRAPH_SIZE = 2;
        private const int BLOCKGRAPH_SIZE = 22;
        private const int STATEMENTGRAPH_SIZE = 23;
        private const int EXPRESSIONGRAPH_SIZE = 10;
        private const int TERMGRAPH_SIZE = 7;
        private const int FACTORGRAPH_SIZE = 5;
        private const int CONDITIONGRAPH_SIZE = 10;
        // Definition der Graphen.
        private Edge[] programmGraph = new Edge[PROGRAMMGRAPH_SIZE];
        private Edge[] blockGraph = new Edge[BLOCKGRAPH_SIZE];
        private Edge[] statementGraph = new Edge[STATEMENTGRAPH_SIZE];
        private Edge[] expressionGraph = new Edge[EXPRESSIONGRAPH_SIZE];
        private Edge[] termGraph = new Edge[TERMGRAPH_SIZE];
        private Edge[] factorGraph = new Edge[FACTORGRAPH_SIZE];
        private Edge[] conditionGraph = new Edge[CONDITIONGRAPH_SIZE];

        // Definiton Morphem und Lexer.
        private Morphem currentMorphem = new Morphem(true);
        private Lexer lexer;

        // Code-Generator.
        private CodeGenerator codeGenerator;

        // Definition Namensliste.
        private NamelistProcedure currentProcedure = new NamelistProcedure();
        // Zwischenspeicher Konstanten/Variablen/Prozedur-Name.
        private String currentName;
        // Zwischenspeicher Condition.
        private CommandCode currentCondition;
        // Prozedurzähler.
        private int numberOfProcedures = 1;
        // Konstantenliste.
        private List<NamelistConstant> constantList = new List<NamelistConstant>();

        // Größe eines Wertes in der Virtuellen Maschine (4 Byte).
        private static readonly int VALUE_SIZE = 4;

        /// <summary>
        /// Initialisiere den Parser mit der zu kompilierenden Datei. 
        /// Graphen werden dazu mit den Kanten belegt. 
        /// Der Lexer und CodeGenerator werden mit der Datei erstellt.
        /// </summary>
        /// <param name="filePath">Zu kompilierende Datei</param>
        public Parser(string filePath) {
            // Initialisierung der Kanten entsprechend der (analog) angefertigten Nummerierungen der Graphen: 
            // { Typ, Wert, Aktion, Folgekante, Alternativkante }
            // Alternativkante -1: es existiert keine Alternative (oder ist letzte Alternative)
            // Folgekante      -1: es existiert kein nächste Kante => Ende vom Graph
            Edge[] programmGraphTemp = new Edge[PROGRAMMGRAPH_SIZE] {
                /* 0 */ new Edge(EdgeType.graph,  blockGraph, null,                             1, -1),
                /* 1 */ new Edge(EdgeType.symbol, ".",        new ActionDelegate(ProgrammEnd), -1, -1)
            };

            Edge[] blockGraphTemp = new Edge[BLOCKGRAPH_SIZE] {
                /*  0 */ new Edge(EdgeType.symbol,  "CONST",                null,                                              1,  7), // Kanten const
                /*  1 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckConstIdentifier),     2, -1),
                /*  2 */ new Edge(EdgeType.symbol,  "=",                    null,                                              3, -1),
                /*  3 */ new Edge(EdgeType.morphem, MorphemCode.number,     new ActionDelegate(BlockCheckConstValue),          4, -1),
                /*  4 */ new Edge(EdgeType.symbol,  ",",                    null,                                              1,  5),
                /*  5 */ new Edge(EdgeType.symbol,  ";",                    null,                                              6, -1),
                /*  6 */ new Edge(EdgeType.blank,   null,                   null,                                              8, -1),
                /*  7 */ new Edge(EdgeType.blank,   null,                   null,                                              8, -1),
                /*  8 */ new Edge(EdgeType.symbol,  "VAR",                  null,                                              9, 13), // Kanten var
                /*  9 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckVarIdentifier),      10, -1),
                /* 10 */ new Edge(EdgeType.symbol,  ",",                    null,                                              9, 11),
                /* 11 */ new Edge(EdgeType.symbol,  ";",                    null,                                             12, -1),
                /* 12 */ new Edge(EdgeType.blank,   null,                   null,                                             14, -1),
                /* 13 */ new Edge(EdgeType.blank,   null,                   null,                                             14, -1),
                /* 14 */ new Edge(EdgeType.symbol,  "PROCEDURE",            null,                                             15, 20), // Kanten procedure
                /* 15 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckProcedureIdentifer), 16, -1),
                /* 16 */ new Edge(EdgeType.symbol,  ";",                    null,                                             17, -1),
                /* 17 */ new Edge(EdgeType.graph,   blockGraph,             null,                                             18, -1),
                /* 18 */ new Edge(EdgeType.symbol,  ";",                    new ActionDelegate(BlockEndProcedure),            19, -1),
                /* 19 */ new Edge(EdgeType.blank,   null,                   null,                                             14, 20),
                /* 20 */ new Edge(EdgeType.blank,   null,                   new ActionDelegate(BlockEnterStatement),          21, -1), // Zum statement
                /* 21 */ new Edge(EdgeType.graph,   statementGraph,         null,                                             -1, -1)
            };

            Edge[] statementGraphTemp = new Edge[STATEMENTGRAPH_SIZE] {
                /*  0 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementCheckVarIdentifier),  1,  3), // Kanten var
                /*  1 */ new Edge(EdgeType.symbol,  ":=",                   null,                                             2, -1),
                /*  2 */ new Edge(EdgeType.graph,   expressionGraph,        new ActionDelegate(StatementStoreVarValue),      -1, -1),
                /*  3 */ new Edge(EdgeType.symbol,  "IF",                   null,                                             4,  7), // Kanten if
                /*  4 */ new Edge(EdgeType.graph,   conditionGraph,         new ActionDelegate(StatementIfCondition),         5, -1),
                /*  5 */ new Edge(EdgeType.symbol,  "THEN",                 null,                                             6, -1),
                /*  6 */ new Edge(EdgeType.graph,   statementGraph,         new ActionDelegate(StatementIfStatement),        -1, -1),
                /*  7 */ new Edge(EdgeType.symbol,  "WHILE",                new ActionDelegate(StatementWhile),               8, 11), // Kanten while
                /*  8 */ new Edge(EdgeType.graph,   conditionGraph,         new ActionDelegate(StatementWhileCondition),      9, -1),
                /*  9 */ new Edge(EdgeType.symbol,  "DO",                   null,                                            10, -1),
                /* 10 */ new Edge(EdgeType.graph,   statementGraph,         new ActionDelegate(StatementWhileStatement),     -1, -1),
                /* 11 */ new Edge(EdgeType.symbol,  "BEGIN",                null,                                            12, 15), // Kanten codeblock
                /* 12 */ new Edge(EdgeType.graph,   statementGraph,         null,                                            13, 14),
                /* 13 */ new Edge(EdgeType.symbol,  ";",                    null,                                            12, 14),
                /* 14 */ new Edge(EdgeType.symbol,  "END",                  null,                                            -1, -1),
                /* 15 */ new Edge(EdgeType.symbol,  "CALL",                 null,                                            16, 17), // Kanten call
                /* 16 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementProcedureCall),      -1, -1),
                /* 17 */ new Edge(EdgeType.symbol,  "?",                    null,                                            18, 19), // Kanten input
                /* 18 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementInput),              -1, -1),
                /* 19 */ new Edge(EdgeType.symbol,  "!",                    null,                                            22, 21), // Kanten output
                /* 20 */ new Edge(EdgeType.graph,   expressionGraph,        new ActionDelegate(StatementOutputExpression),   -1, -1),
                /* 21 */ new Edge(EdgeType.blank,   null,                   null,                                            -1, -1),
                /* 22 */ new Edge(EdgeType.morphem, MorphemCode.strings,    new ActionDelegate(StatementOutputString),       -1, 20)  // Erweiterung String output
            };

            Edge[] expressionGraphTemp = new Edge[EXPRESSIONGRAPH_SIZE] {
                /* 0 */ new Edge(EdgeType.symbol, "-",       null,                                      1,  2), // Kanten negative term
                /* 1 */ new Edge(EdgeType.graph,  termGraph, new ActionDelegate(ExpressionNegative),    4, -1),
                /* 2 */ new Edge(EdgeType.blank,  null,      null,                                      3, -1), // Kanten normal term
                /* 3 */ new Edge(EdgeType.graph,  termGraph, null,                                      4, -1),
                /* 4 */ new Edge(EdgeType.blank,  null,      null,                                      5, -1),
                /* 5 */ new Edge(EdgeType.symbol, "+",       null,                                      6,  7), // Kanten addition
                /* 6 */ new Edge(EdgeType.graph,  termGraph, new ActionDelegate(ExpressionAddition),    4, -1),
                /* 7 */ new Edge(EdgeType.symbol, "-",       null,                                      8,  9), // Kanten subtraction
                /* 8 */ new Edge(EdgeType.graph,  termGraph, new ActionDelegate(ExpressionSubtraction), 4, -1),
                /* 9 */ new Edge(EdgeType.blank,  null,      null,                                     -1, -1)
            };

            Edge[] termGraphTemp = new Edge[TERMGRAPH_SIZE] {
                /* 0 */ new Edge(EdgeType.graph,  factorGraph, null,                                    1, -1),
                /* 1 */ new Edge(EdgeType.blank,  null,        null,                                    2, -1),
                /* 2 */ new Edge(EdgeType.symbol, "*",         null,                                    3,  4), // Kanten multiplication
                /* 3 */ new Edge(EdgeType.graph,  factorGraph, new ActionDelegate(TermMultiplication),  1, -1),
                /* 4 */ new Edge(EdgeType.symbol, "/",         null,                                    5,  6), // Kanten division
                /* 5 */ new Edge(EdgeType.graph,  factorGraph, new ActionDelegate(TermDivision),        1, -1),
                /* 6 */ new Edge(EdgeType.blank,  null,        null,                                   -1, -1)
            };


            Edge[] factorGraphTemp = new Edge[FACTORGRAPH_SIZE] {
                /* 0 */ new Edge(EdgeType.morphem, MorphemCode.number,     new ActionDelegate(FactorCheckNumber),     -1,  1), // Kante numeral
                /* 1 */ new Edge(EdgeType.symbol,  "(",                    null,                                       2,  4), // Kanten braced
                /* 2 */ new Edge(EdgeType.graph,   expressionGraph,        null,                                       3, -1),
                /* 3 */ new Edge(EdgeType.symbol,  ")",                    null,                                      -1, -1),
                /* 4 */ new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(FactorCheckIdentifier), -1, -1)  // Kante identifier
            };

            Edge[] conditionGraphTemp = new Edge[CONDITIONGRAPH_SIZE] {
                /* 0 */ new Edge(EdgeType.symbol, "ODD",           null,                                       1,  2), // Kanten odd
                /* 1 */ new Edge(EdgeType.graph,  expressionGraph, new ActionDelegate(ConditionOdd),          -1, -1),
                /* 2 */ new Edge(EdgeType.graph,  expressionGraph, null,                                       3, -1), // Kanten comparsion
                /* 3 */ new Edge(EdgeType.symbol, "=",             new ActionDelegate(ConditionSaveEQ),        9,  4),
                /* 4 */ new Edge(EdgeType.symbol, "#",             new ActionDelegate(ConditionSaveNE),        9,  5),
                /* 5 */ new Edge(EdgeType.symbol, "<",             new ActionDelegate(ConditionSaveLT),        9,  6),
                /* 6 */ new Edge(EdgeType.symbol, "<=",            new ActionDelegate(ConditionSaveLE),        9,  7),
                /* 7 */ new Edge(EdgeType.symbol, ">",             new ActionDelegate(ConditionSaveGT),        9,  8),
                /* 8 */ new Edge(EdgeType.symbol, ">=",            new ActionDelegate(ConditionSaveGE),        9, -1),
                /* 9 */ new Edge(EdgeType.graph,  expressionGraph, new ActionDelegate(ConditionApplyOperand), -1, -1)
            };

            /* 
             * Da die Kanten der Graphen in Parse() angesteuert werden, müssen sie zuvor global initialisiert werden (new Edge[...]).
             * Somit können sie nicht einfach mit einem neun Graphen überschrieben werden, da bereits auf die Einträge der initialen Graphen verwiesen wird.
             * Damit müssen entweder (wie hier auskommentiert) den Einträgen die tatsächliche Kanten zugewiesen (wird vom Autoformater zerschossen) oder wie 
             * oberhalb temporärere Graphen erstellt werden, dessen Einträge dann in die globalen Graphen eingetragen werden (damit kann man Leerzeichen 
             * einfügen, ohne dass sie vom Autoformater entfernt werden - das ist tabellarisch gut übersichtlich).
            programmGraph[0] = new Edge(EdgeType.graph, blockGraph, null, 1, -1);
            programmGraph[1] = new Edge(EdgeType.symbol, ".", new ActionDelegate(ProgrammEnd), -1, -1);

            blockGraph[0] = new Edge(EdgeType.symbol, "CONST", null, 1, 7); // Kanten const
            blockGraph[1] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckConstIdentifier), 2, -1);
            blockGraph[2] = new Edge(EdgeType.symbol, "=", null, 3, -1);
            blockGraph[3] = new Edge(EdgeType.morphem, MorphemCode.number, new ActionDelegate(BlockCheckConstValue), 4, -1);
            blockGraph[4] = new Edge(EdgeType.symbol, ",", null, 1, 5);
            blockGraph[5] = new Edge(EdgeType.symbol, ";", null, 6, -1);
            blockGraph[6] = new Edge(EdgeType.blank, null, null, 8, -1);
            blockGraph[7] = new Edge(EdgeType.blank, null, null, 8, -1);
            blockGraph[8] = new Edge(EdgeType.symbol, "VAR", null, 9, 13); // Kanten var
            blockGraph[9] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckVarIdentifier), 10, -1);
            blockGraph[10] = new Edge(EdgeType.symbol, ",", null, 9, 11);
            blockGraph[11] = new Edge(EdgeType.symbol, ";", null, 12, -1);
            blockGraph[12] = new Edge(EdgeType.blank, null, null, 14, -1);
            blockGraph[13] = new Edge(EdgeType.blank, null, null, 14, -1);
            blockGraph[14] = new Edge(EdgeType.symbol, "PROCEDURE", null, 15, 20); // Kanten procedure
            blockGraph[15] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(BlockCheckProcedureIdentifer), 16, -1);
            blockGraph[16] = new Edge(EdgeType.symbol, ";", null, 17, -1);
            blockGraph[17] = new Edge(EdgeType.graph, blockGraph, null, 18, -1);
            blockGraph[18] = new Edge(EdgeType.symbol, ";", new ActionDelegate(BlockEndProcedure), 19, -1);
            blockGraph[19] = new Edge(EdgeType.blank, null, null, 14, 20);
            blockGraph[20] = new Edge(EdgeType.blank, null, new ActionDelegate(BlockEnterStatement), 21, -1); // Zum statement
            blockGraph[21] = new Edge(EdgeType.graph, statementGraph, null, -1, -1);

            statementGraph[0] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementCheckVarIdentifier), 1, 3); // Kanten var
            statementGraph[1] = new Edge(EdgeType.symbol, ":=", null, 2, -1);
            statementGraph[2] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(StatementStoreVarValue), -1, -1);
            statementGraph[3] = new Edge(EdgeType.symbol, "IF", null, 4, 7); // Kanten if
            statementGraph[4] = new Edge(EdgeType.graph, conditionGraph, new ActionDelegate(StatementIfCondition), 5, -1);
            statementGraph[5] = new Edge(EdgeType.symbol, "THEN", null, 6, -1);
            statementGraph[6] = new Edge(EdgeType.graph, statementGraph, new ActionDelegate(StatementIfStatement), -1, -1);
            statementGraph[7] = new Edge(EdgeType.symbol, "WHILE", new ActionDelegate(StatementWhile), 8, 11); // Kanten while
            statementGraph[8] = new Edge(EdgeType.graph, conditionGraph, new ActionDelegate(StatementWhileCondition), 9, -1);
            statementGraph[9] = new Edge(EdgeType.symbol, "DO", null, 10, -1);
            statementGraph[10] = new Edge(EdgeType.graph, statementGraph, new ActionDelegate(StatementWhileStatement), -1, -1);
            statementGraph[11] = new Edge(EdgeType.symbol, "BEGIN", null, 12, 15); // Kanten codeblock
            statementGraph[12] = new Edge(EdgeType.graph, statementGraph, null, 13, 14);
            statementGraph[13] = new Edge(EdgeType.symbol, ";", null, 12, 14);
            statementGraph[14] = new Edge(EdgeType.symbol, "END", null, -1, -1);
            statementGraph[15] = new Edge(EdgeType.symbol, "CALL", null, 16, 17); // Kanten call
            statementGraph[16] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementProcedureCall), -1, -1);
            statementGraph[17] = new Edge(EdgeType.symbol, "?", null, 18, 19);  // Kanten input
            statementGraph[18] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(StatementInput), -1, -1);
            statementGraph[19] = new Edge(EdgeType.symbol, "!", null, 22, 21);  // Kanten output
            statementGraph[20] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(StatementOutputExpression), -1, -1);
            statementGraph[21] = new Edge(EdgeType.blank, null, null, -1, -1);
            statementGraph[22] = new Edge(EdgeType.morphem, MorphemCode.strings, new ActionDelegate(StatementOutputString), -1, 20); // Erweiterung String output

            expressionGraph[0] = new Edge(EdgeType.symbol, "-", null, 1, 2);    // Kanten negative term
            expressionGraph[1] = new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionNegative), 4, -1);
            expressionGraph[2] = new Edge(EdgeType.blank, null, null, 3, -1);   // Kanten normal term
            expressionGraph[3] = new Edge(EdgeType.graph, termGraph, null, 4, -1);
            expressionGraph[4] = new Edge(EdgeType.blank, null, null, 5, -1);
            expressionGraph[5] = new Edge(EdgeType.symbol, "+", null, 6, 7);   // Kanten addition
            expressionGraph[6] = new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionAddition), 4, -1);
            expressionGraph[7] = new Edge(EdgeType.symbol, "-", null, 8, 9);   // Kanten subtraction
            expressionGraph[8] = new Edge(EdgeType.graph, termGraph, new ActionDelegate(ExpressionSubtraction), 4, -1);
            expressionGraph[9] = new Edge(EdgeType.blank, null, null, -1, -1);
            
            termGraph[0] = new Edge(EdgeType.graph, factorGraph, null, 1, -1);
            termGraph[1] = new Edge(EdgeType.blank, null, null, 2, -1);
            termGraph[2] = new Edge(EdgeType.symbol, "*", null, 3, 4);   // Kanten multiplication
            termGraph[3] = new Edge(EdgeType.graph, factorGraph, new ActionDelegate(TermMultiplication), 1, -1);
            termGraph[4] = new Edge(EdgeType.symbol, "/", null, 5, 6);    // Kanten division
            termGraph[5] = new Edge(EdgeType.graph, factorGraph, new ActionDelegate(TermDivision), 1, -1);
            termGraph[6] = new Edge(EdgeType.blank, null, null, -1, -1);

            factorGraph[0] = new Edge(EdgeType.morphem, MorphemCode.number, new ActionDelegate(FactorCheckNumber), -1, 1);  // Kante numeral
            factorGraph[1] = new Edge(EdgeType.symbol, "(", null, 2, 4);    // Kanten braced
            factorGraph[2] = new Edge(EdgeType.graph, expressionGraph, null, 3, -1);
            factorGraph[3] = new Edge(EdgeType.symbol, ")", null, -1, -1);
            factorGraph[4] = new Edge(EdgeType.morphem, MorphemCode.identifier, new ActionDelegate(FactorCheckIdentifier), -1, -1);  // Knte identifier

            conditionGraph[0] = new Edge(EdgeType.symbol, "ODD", null, 1, 2);  // Kanten odd
            conditionGraph[1] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(ConditionOdd), -1, -1);
            conditionGraph[2] = new Edge(EdgeType.graph, expressionGraph, null, 3, -1);    // Kanten comparsion
            conditionGraph[3] = new Edge(EdgeType.symbol, "=", new ActionDelegate(ConditionSaveEQ), 9, 4);
            conditionGraph[4] = new Edge(EdgeType.symbol, "#", new ActionDelegate(ConditionSaveNE), 9, 5);
            conditionGraph[5] = new Edge(EdgeType.symbol, "<", new ActionDelegate(ConditionSaveLT), 9, 6);
            conditionGraph[6] = new Edge(EdgeType.symbol, "<=", new ActionDelegate(ConditionSaveLE), 9, 7);
            conditionGraph[7] = new Edge(EdgeType.symbol, ">", new ActionDelegate(ConditionSaveGT), 9, 8);
            conditionGraph[8] = new Edge(EdgeType.symbol, ">=", new ActionDelegate(ConditionSaveGE), 9, -1);
            conditionGraph[9] = new Edge(EdgeType.graph, expressionGraph, new ActionDelegate(ConditionApplyOperand), -1, -1);
            */

            // Kopiere die temporären Graphen in die tätschlich benutzten.
            for (int i = 0; i < PROGRAMMGRAPH_SIZE; i++)
                programmGraph[i] = programmGraphTemp[i];
            for (int i = 0; i < BLOCKGRAPH_SIZE; i++)
                blockGraph[i] = blockGraphTemp[i];
            for (int i = 0; i < STATEMENTGRAPH_SIZE; i++)
                statementGraph[i] = statementGraphTemp[i];
            for (int i = 0; i < EXPRESSIONGRAPH_SIZE; i++)
                expressionGraph[i] = expressionGraphTemp[i];
            for (int i = 0; i < TERMGRAPH_SIZE; i++)
                termGraph[i] = termGraphTemp[i];
            for (int i = 0; i < FACTORGRAPH_SIZE; i++)
                factorGraph[i] = factorGraphTemp[i];
            for (int i = 0; i < CONDITIONGRAPH_SIZE; i++)
                conditionGraph[i] = conditionGraphTemp[i];

            // Initialisiere Lexer mit der zu parsenden Datei.
            lexer = new Lexer(filePath);

            // Initialisiere CodeGenerator mit der zu parsenden Datei (entspricht - ausgenommen der Endung - der Ausgabedatei).
            codeGenerator = new CodeGenerator(filePath);
        }

        /// <summary>
        /// Starte einen neuen Parse-/Kompiliervorgang. Das Parsen wird demnach mit dem Programmgraphen aufgerufen.
        /// </summary>
        /// <returns>Erfolg des Kompilierens</returns>
        public bool Parse() {
            if (Parse(programmGraph)) {
                return true;
            } else {
                return false;
            }
        }

        /// <summary>
        /// Parse einen Graphen, indem Schrittweise vergleichen wird, ob das nächste untersuchte Zeichen an der entsprechend Stelle stehen darf oder nicht.
        /// Gegebenenfalls werden Aktionen an den Codegenerator weitergeleitet.
        /// </summary>
        /// <param name="currentGraph">Zu parsender Graph</param>
        /// <returns>Erfolg des Parsens des Graphen</returns>
        private bool Parse(Edge[] currentGraph) {
            int currentEdgeNumber = 0;
            bool success = false;
            Edge currentEdge;
            // Wenn das Morphem leer ist, lasse Lexer das nächste holen.
            if (currentMorphem.Code == MorphemCode.empty)
                currentMorphem = lexer.NextMorphem();
            while (true) {
                // Wähle die zu untersuchende Kante aus
                currentEdge = currentGraph[currentEdgeNumber];
                switch (currentEdge.Type) {
                    case EdgeType.blank:
                        // Leere Kanten sind erlaubt und werden übersprungen.
                        success = true;
                        break;
                    case EdgeType.symbol:
                        // Bei einem Symbol muss der tatsächlich dem erwarteten Wert entsprechen.
                        success = (currentMorphem.Code == MorphemCode.symbol && currentMorphem.Value == currentEdge.Value);
                        break;
                    case EdgeType.morphem:
                        // Bei einem Morphem das kein Symbol ist, muss der Morphemcode stimmen.
                        success = (currentMorphem.Code == currentEdge.Value);
                        break;
                    case EdgeType.graph:
                        // Wenn die Kante ein Graph ist, muss dieser erfolgreich geparst werden.
                        success = Parse(currentEdge.Value);
                        break;
                }
                if (!success) {
                    // Bei nicht passender Kante Alternativkante ausprobieren (falls vorhanden).
                    if (currentEdge.AlternativeEdge != -1)
                        currentEdgeNumber = currentEdge.AlternativeEdge;
                    else {
                        PrintError("Error in line ", currentMorphem.position[1], " (Column " + currentMorphem.position[0] + "). Expected " + currentEdge.Value + "!");
                        return false;
                    }
                } else {
                    // Codegenerierungsfunktion aufrufen, falls vorhanden. Bei Fehlschlag parsen beenden.
                    if (currentEdge.Action != null) {
                        if (!((ActionDelegate)currentEdge.Action)())
                            return false;
                    }
                    // Gegebenenfalls Symbol/Morphem akzeptieren und nächstes holen.
                    if (currentEdge.Type == EdgeType.symbol || currentEdge.Type == EdgeType.morphem) {
                        PrintProgressA("Consumed ", currentMorphem.Value, "");
                        currentMorphem = lexer.NextMorphem();
                        if (currentMorphem.Value != null) {
                            PrintProgressB(" (Next: ", currentMorphem.Value, ").");
                        } else {
                            PrintProgressB("", "", ". Nothing more to read.");
                        }
                    }
                    // Wenn die letzte Kante akzeptiert wurde, beenden.
                    if (currentEdge.NextEdge == -1)
                        return true;
                    // Nächste Kante untersuchen.
                    currentEdgeNumber = currentEdge.NextEdge;
                }
            }
        }

        // ============================================================
        // Kantenfunktionen
        // ============================================================

        // Kantefunktionen Programm:
        // ------------------------------------------------------------
        private bool ProgrammEnd() {
            PrintCodeGen("ProgrammEnd");
            // Mainprozedur beenden.
            BlockEndProcedure();
            // Konstantenblock schreiben.
            codeGenerator.GenerateConstantBlock(constantList);
            // Fertig kompilierten Code schreiben.
            codeGenerator.WriteCodeToFile();
            return true;
        }

        // Kantefunktionen Block:
        // ------------------------------------------------------------
        private bool BlockCheckConstIdentifier() {
            String name = currentMorphem.Value;
            PrintCodeGen("BlockCheckConstIdentifier " + name);
            // Überprüfe, ob bereits ein Eintrag mit dem gleichen Bezeichner existiert.
            if (currentProcedure.HasEntry(name)) {
                PrintError("The identifier ", name, " already exists in this context.");
                return false;
            }
            // Speichere den Namen.
            currentName = name;
            return true;
        }

        private bool BlockCheckConstValue() {
            PrintCodeGen("BlockCheckConstValue " + currentMorphem.Value);
            int value = currentMorphem.Value;
            // Index des Konstantenwerts herausfinden.
            int index = FindConstantValuePosition(value);
            // Bei neuem Wert, neuen Eintrag in Konstantenliste anlegen.
            if (index < 0) {
                // Index berechnet sich aus der Größe der Konstantenliste.
                index = constantList.Count();
                // Konstantenliste um neuen Eintrag ergänzen.
                constantList.Add(new NamelistConstant(currentProcedure.ProcedureID, currentName, value, index));
            }
            // Konstante in Namensliste der aktuellen Prozedur einfügen.
            currentProcedure.namelist.Add(new NamelistConstant(currentProcedure.ProcedureID, currentName, value, index));
            return true;
        }

        private bool BlockCheckVarIdentifier() {
            String name = currentMorphem.Value;
            PrintCodeGen("BlockCheckVarIdentifier " + name);
            // Überprüfe, ob bereits ein Eintrag mit dem gleichen Bezeichner existiert.
            if (currentProcedure.HasEntry(name)) {
                PrintError("The identifier ", name, " already exists in this context.");
                return false;
            }
            // Variable in Namenliste der aktuellen Prozedur einfügen.
            currentProcedure.namelist.Add(new NamelistVariable(currentProcedure.ProcedureID, name, currentProcedure.variablesMemorySize));
            // Relativadresse für nächsten Eintrag erhöhen.
            currentProcedure.variablesMemorySize += VALUE_SIZE;
            return true;
        }

        private bool BlockCheckProcedureIdentifer() {
            String name = currentMorphem.Value;
            PrintCodeGen("BlockCheckProcedureIdentifer " + name);
            // Überprüfe, ob bereits ein Eintrag mit dem gleichen Bezeichner existiert.
            if (currentProcedure.HasEntry(name)) {
                PrintError("The identifier ", name, " already exists in this context.");
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
            PrintCodeGen("BlockEnterStatement " + currentProcedure.Name);
            // Generiere entryProc mit zunächst unbekannter Länge, der Prozedur-ID und die Größe des Variablenbereichs.
            codeGenerator.GenerateCode(CommandCode.entryProc, 0, currentProcedure.ProcedureID, currentProcedure.variablesMemorySize);
            return true;
        }

        private bool BlockEndProcedure() {
            PrintCodeGen("BlockEndProcedure " + currentProcedure.Name);
            // Generiere retProc.
            codeGenerator.GenerateCode(CommandCode.retProc);
            // Aktualisiere die Prozedurlänge.
            codeGenerator.UpdateProcedureLength();
            // Namenliste der Prozedur löschen.
            currentProcedure.namelist.Clear();
            // Elternprozedur ist nun aktuelle Prozedur.
            currentProcedure = currentProcedure.ParentProcedure;
            return true;
        }

        // Kantefunktionen Statement:
        // ------------------------------------------------------------
        private bool StatementCheckVarIdentifier() {
            String identifier = currentMorphem.Value;
            PrintCodeGen("StatementCheckVarIdentifier " + identifier);
            // Identifier global suchen. 
            NamelistEntry identifierEntry = FindGlobalEntry(identifier);
            // Überprüfen, ob Identifier existiert und eine Variable ist.
            // Codegenerierung dann davon und vom Fundort abhängig.
            if (identifierEntry == null) {
                // Bezeichner nicht vorhanden. Fehler!
                PrintError("The identifier ", identifier, " does not exists in this context.");
                return false;
            } else if (identifierEntry.GetType() == typeof(NamelistProcedure)) {
                // Bezeichner ist Prozedur. Fehler!
                PrintError("The identifier ", identifier, " describes a procedure and not a variable.");
                return false;
            } else if (identifierEntry.GetType() == typeof(NamelistConstant)) {
                // Bezeichner ist Konstante. Fehler!
                PrintError("The identifier ", identifier, " describes a constant and not a variable.");
                return false;
            } else {
                // Bezeichner ist Variable. Unterscheide, woher sie kommt:
                NamelistVariable variableEntry = (NamelistVariable)identifierEntry;
                if (variableEntry.MemberProcedureID == currentProcedure.ProcedureID) {
                    // Variable ist lokale Variable. Generiere puAdrVrLocl mit der entsprechenden Verschiebung.
                    codeGenerator.GenerateCode(CommandCode.puAdrVrLocl, variableEntry.Displacement);
                } else if (variableEntry.MemberProcedureID == 0) {
                    // Variable befindet sich in der Main-Funktion. Generiere puAdrVrMain mit der entsprechenden Verschiebung.
                    codeGenerator.GenerateCode(CommandCode.puAdrVrMain, variableEntry.Displacement);
                } else {
                    // Variable ist globale Variable. Generiere puAdrVrGlob mit der entsprechenden Verschiebung und der dazugehörigen Prozedurnummer.
                    codeGenerator.GenerateCode(CommandCode.puAdrVrGlob, variableEntry.Displacement, variableEntry.MemberProcedureID);
                }
            }
            return true;
        }

        private bool StatementStoreVarValue() {
            PrintCodeGen("StatementStoreVarValue");
            // Wert vom Stack im Adresse vom Stack schreiben. Generiere storeVal.
            codeGenerator.GenerateCode(CommandCode.storeVal);
            return true;
        }

        private bool StatementIfCondition() {
            PrintCodeGen("StatementIfCondition");
            // Sprung vorbereiten, indem ein Label generiert wird. Das Ziel ist die Position nach dem if-Block.
            codeGenerator.PrepareJumpForward();
            // Generiere jnot mit noch unbestimmter Sprunggröße.
            codeGenerator.GenerateCode(CommandCode.jnot, 0);
            return true;
        }

        private bool StatementIfStatement() {
            PrintCodeGen("StatementIfStatement");
            // Sprungadresse nachtragen.
            codeGenerator.UpdateJumpFoward();
            return true;
        }

        private bool StatementWhile() {
            PrintCodeGen("StatementWhile");
            // Sprung vorbereiten, indem ein Label generiert wird.
            codeGenerator.PrepareJumpBackward();
            return true;
        }

        private bool StatementWhileCondition() {
            PrintCodeGen("StatementWhileCondition");
            // Sprung vorbereiten, indem ein Label generiert wird. Das Ziel ist die Position nach dem while-Block.
            codeGenerator.PrepareJumpForward();
            // Generiere jnot mit noch unbestimmter Sprunggröße.
            codeGenerator.GenerateCode(CommandCode.jnot, 0);
            return true;
        }

        private bool StatementWhileStatement() {
            PrintCodeGen("StatementWhileStatement");
            // Sprungadresse für den Sprung des Überspringens der while-Schleife nachtragen.
            codeGenerator.UpdateJumpFoward(3);
            // Sprungadresse für den Rücksprung zum Anfang der Schleife herausfinden.
            int jumpAddress = codeGenerator.GetJumpBackwardAddress();
            // Mit Sprungadressen jmp generieren.
            codeGenerator.GenerateCode(CommandCode.jmp, jumpAddress);
            return true;
        }

        private bool StatementProcedureCall() {
            String identifier = currentMorphem.Value;
            PrintCodeGen("StatementProcedureCall " + identifier);
            // Identifier global suchen. 
            NamelistEntry identifierEntry = FindGlobalEntry(identifier);
            // Überprüfen, ob Identifier existiert und eine Prozedur ist.
            if (identifierEntry == null) {
                // Bezeichner nicht vorhanden. Fehler!
                PrintError("The identifier ", identifier, " does not exists in this context.");
                return false;
            } else if (identifierEntry.GetType() != typeof(NamelistProcedure)) {
                // Bezeichner ist keine Prozedur. Fehler!
                PrintError("The identifier ", identifier, " does not describe a procedure.");
                return false;
            } else {
                // Generiere call, um die Prozedur mit dem gefundenen Index aufzurufen.
                codeGenerator.GenerateCode(CommandCode.call, ((NamelistProcedure)identifierEntry).ProcedureID);
            }
            return true;
        }

        private bool StatementInput() {
            String identifier = currentMorphem.Value;
            PrintCodeGen("StatementInput " + identifier);
            // Identifier global suchen. 
            NamelistEntry identifierEntry = FindGlobalEntry(identifier);
            // Überprüfen, ob Identifier existiert und eine Variable/Konstante ist.
            // Codegenerierung dann davon und vom Fundort abhängig.
            if (identifierEntry == null) {
                // Bezeichner nicht vorhanden. Fehler!
                PrintError("The identifier ", identifier, " does not exists in this context.");
                return false;
            } else if (identifierEntry.GetType() == typeof(NamelistProcedure)) {
                // Bezeichner ist Prozedur. Fehler!
                PrintError("The identifier ", identifier, " describes a procedure and not a variable.");
                return false;
            } else if (identifierEntry.GetType() == typeof(NamelistConstant)) {
                // Bezeichner ist Konstante. Fehler!
                PrintError("The identifier ", identifier, " describes a constant and not a variable.");
                return false;
            } else {
                // Bezeichner ist Variable. Unterscheide, woher sie kommt:
                NamelistVariable variableEntry = (NamelistVariable)identifierEntry;
                if (variableEntry.MemberProcedureID == currentProcedure.ProcedureID) {
                    // Variable ist lokale Variable. Generiere puAdrVrLocl mit der entsprechenden Verschiebung.
                    codeGenerator.GenerateCode(CommandCode.puAdrVrLocl, variableEntry.Displacement);
                } else if (variableEntry.MemberProcedureID == 0) {
                    // Variable befindet sich in der Main-Funktion. Generiere puAdrVrMain mit der entsprechenden Verschiebung.
                    codeGenerator.GenerateCode(CommandCode.puAdrVrMain, variableEntry.Displacement);
                } else {
                    // Variable ist globale Variable. Generiere puAdrVrGlob mit der entsprechenden Verschiebung und der dazugehörigen Prozedurnummer.
                    codeGenerator.GenerateCode(CommandCode.puAdrVrGlob, variableEntry.Displacement, variableEntry.MemberProcedureID);
                }
            }
            // Generiere getVal, um den Wert, der in diese Variable gespeichert werden soll, abzufragen.
            codeGenerator.GenerateCode(CommandCode.getVal);
            return true;
        }

        private bool StatementOutputExpression() {
            PrintCodeGen("StatementOutputExpression");
            // Generiere putVal für die Ausgabe eines Ausdrucks.
            codeGenerator.GenerateCode(CommandCode.putVal);
            return true;
        }

        private bool StatementOutputString() {
            String value = currentMorphem.Value;
            PrintCodeGen("StatementOutputString " + value);
            // Generiere putStrg mit dem auszugebenden String.
            codeGenerator.GenerateCode(CommandCode.putStrg, value);
            return true;
        }

        // Kantefunktionen Expression:
        // ------------------------------------------------------------
        private bool ExpressionNegative() {
            PrintCodeGen("ExpressionNegative");
            // Generiere vzMinus, um negativen Term anzukündigen.
            codeGenerator.GenerateCode(CommandCode.vzMinus);
            return true;
        }

        private bool ExpressionAddition() {
            PrintCodeGen("ExpressionAddition");
            // Generiere opAdd, um weiter Terme zu addieren.
            codeGenerator.GenerateCode(CommandCode.opAdd);
            return true;
        }

        private bool ExpressionSubtraction() {
            PrintCodeGen("ExpressionSubtraction");
            // Generiere opSub, um weiter Terme zu subtrahieren.
            codeGenerator.GenerateCode(CommandCode.opSub);
            return true;
        }

        // Kantefunktionen Term:
        // ------------------------------------------------------------
        private bool TermMultiplication() {
            PrintCodeGen("TermMultiplication");
            // Generiere opMul, um weiter Faktoren zu multiplizieren.
            codeGenerator.GenerateCode(CommandCode.opMult);
            return true;
        }

        private bool TermDivision() {
            PrintCodeGen("TermDivision");
            // Generiere opDiv, um weiter Faktoren zu dividieren.
            codeGenerator.GenerateCode(CommandCode.opDiv);
            return true;
        }

        // Kantefunktionen Factor:
        // ------------------------------------------------------------
        private bool FactorCheckNumber() {
            int value = currentMorphem.Value;
            PrintCodeGen("FactorCheckNumber " + value);
            // Index des Konstantenwerts herausfinden.
            int index = FindConstantValuePosition(value);
            // Bei neuem Wert, neuen Eintrag in Konstantenliste anlegen.
            if (index < 0) {
                // Index berechnet sich aus der Größe der Konstantenliste.
                index = constantList.Count();
                // Konstantenliste um neuen Eintrag (ohne Prozedurzugehörigkeit) ergänzen.
                constantList.Add(new NamelistConstant(-1, currentName, value, index));
            }
            // Codegenerierung puConst mit dem Index der Konstante.
            codeGenerator.GenerateCode(CommandCode.puConst, index);
            return true;
        }

        private bool FactorCheckIdentifier() {
            String identifier = currentMorphem.Value;
            PrintCodeGen("FactorCheckIdentifier " + identifier);
            // Identifier global suchen. 
            NamelistEntry identifierEntry = FindGlobalEntry(identifier);
            // Überprüfen, ob Identifier existiert und eine Variable/Konstante ist.
            // Codegenerierung dann davon und vom Fundort abhängig.
            if (identifierEntry == null) {
                // Bezeichner nicht vorhanden. Fehler!
                PrintError("The identifier ", identifier, " does not exists in this context.");
                return false;
            } else if (identifierEntry.GetType() == typeof(NamelistProcedure)) {
                // Bezeichner ist Prozedur. Fehler!
                PrintError("The identifier ", identifier, " describes a procedure and not a value.");
                return false;
            } else if (identifierEntry.GetType() == typeof(NamelistConstant)) {
                // Bezeichner ist Konstante. Generiere puConst mit dem Index der Konstante.
                codeGenerator.GenerateCode(CommandCode.puConst, ((NamelistConstant)identifierEntry).Index);
            } else {
                // Bezeichner ist Variable. Unterscheide, woher sie kommt:
                NamelistVariable variableEntry = (NamelistVariable)identifierEntry;
                if (variableEntry.MemberProcedureID == currentProcedure.ProcedureID) {
                    // Variable ist lokale Variable. Generiere puValVrLocl mit der entsprechenden Verschiebung.
                    codeGenerator.GenerateCode(CommandCode.puValVrLocl, variableEntry.Displacement);
                } else if (variableEntry.MemberProcedureID == 0) {
                    // Variable befindet sich in der Main-Funktion. Generiere puValVrMain mit der entsprechenden Verschiebung.
                    codeGenerator.GenerateCode(CommandCode.puValVrMain, variableEntry.Displacement);
                } else {
                    // Variable ist globale Variable. Generiere puValVrGlob mit der entsprechenden Verschiebung und der dazugehörigen Prozedurnummer.
                    codeGenerator.GenerateCode(CommandCode.puValVrGlob, variableEntry.Displacement, variableEntry.MemberProcedureID);
                }
            }
            return true;
        }

        // Kantefunktionen Condition:
        // ------------------------------------------------------------
        private bool ConditionOdd() {
            PrintCodeGen("ConditionOdd");
            // Generiere odd, um einfachen Ungerade-Vergleich durchzuführen.
            codeGenerator.GenerateCode(CommandCode.odd);
            return true;
        }

        private bool ConditionSaveEQ() {
            PrintCodeGen("ConditionSaveEQ");
            // Speichere Vergleichsoperator.
            currentCondition = CommandCode.cmpEQ;
            return true;
        }

        private bool ConditionSaveNE() {
            PrintCodeGen("ConditionSaveNE");
            // Speichere Vergleichsoperator.
            currentCondition = CommandCode.cmpNE;
            return true;
        }

        private bool ConditionSaveLT() {
            PrintCodeGen("ConditionSaveLT");
            // Speichere Vergleichsoperator.
            currentCondition = CommandCode.cmpLT;
            return true;
        }

        private bool ConditionSaveLE() {
            PrintCodeGen("ConditionSaveLE");
            // Speichere Vergleichsoperator.
            currentCondition = CommandCode.cmpLE;
            return true;
        }

        private bool ConditionSaveGT() {
            PrintCodeGen("ConditionSaveGT");
            // Speichere Vergleichsoperator.
            currentCondition = CommandCode.cmpGT;
            return true;
        }

        private bool ConditionSaveGE() {
            PrintCodeGen("ConditionSaveGE");
            // Speichere Vergleichsoperator.
            currentCondition = CommandCode.cmpGE;
            return true;
        }

        private bool ConditionApplyOperand() {
            PrintCodeGen("ConditionApplyOperand");
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
        /// <returns>Position der Konstanten in der Konstanetliste</returns>
        int FindConstantValuePosition(int value) {
            // Konstantenlisteneinträge einzeln überprufen.
            foreach (var entry in constantList) {
                // Wenn Wert übereinstimmt, die Position von diesem Eintrag ausgeben.
                if (entry.Value == value)
                    return entry.Index;
            }
            return -1;
        }

        /// <summary>
        /// Globale suche nach einem Eintrag in der Namenliste mit dem gegebenen Namen.
        /// </summary>
        /// <param name="name">Zu suchender Eintragsname</param>
        /// <returns></returns>
        NamelistEntry FindGlobalEntry(String name) {
            NamelistProcedure procedureToSearch = currentProcedure;
            while (procedureToSearch != null) {
                // Namensliste der aktuellen Prozedur suchen.
                foreach (var entry in procedureToSearch.namelist) {
                    // Wenn Name übereinstimmt, diesen Eintrag ausgeben.
                    if (entry.Name == name) {
                        return entry;
                    }
                }
                // Übergeordnete Prozedur als nächstes durchsuchen
                procedureToSearch = procedureToSearch.ParentProcedure;
            }
            return null;
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
            Console.WriteLine("\t" + a);
            Console.ResetColor();
        }

    }
}
