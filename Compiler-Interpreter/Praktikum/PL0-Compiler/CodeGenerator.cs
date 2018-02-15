// Code von Falk-Jonatan Strube (mail@fj-strube.de)
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PL0Compiler {

    /// <summary>
    /// Art des Befehls. Nummer des Enums entspricht der Bytenummer des Befehls.
    /// </summary>
    enum CommandCode : int {
        /*--- Kellerbefehle ---*/
        puValVrLocl,    //00 (short Displ)              [Kellern Wert lokale Variable]
        puValVrMain,    //01 (short Displ)              [Kellern Wert Main Variable]
        puValVrGlob,    //02 (short Displ,short Proc)   [Kellern Wert globale Variable]
        puAdrVrLocl,    //03 (short Displ)              [Kellern Adresse lokale Variable]
        puAdrVrMain,    //04 (short Displ)              [Kellern Adresse Main Variable]
        puAdrVrGlob,    //05 (short Displ,short Proc)   [Kellern Adresse globale Variable]
        puConst,        //06 (short Index)              [Kellern einer Konstanten]
        storeVal,       //07 ()                         [Speichern Wert in Adresse, beides aus Keller]
        putVal,         //08 ()                         [Ausgabe eines Wertes aus Keller nach stdout]
        getVal,         //09 ()                         [Eingabe eines Wertes von stdin in Addr. im Keller ]
                        /*--- arithmetische Befehle ---*/
        vzMinus,        //0A ()                         [Vorzeichen]
        odd,            //0B ()                         [ungerade -> 0/1]
                        /*--- binäre Operatoren kellern 2 Operanden aus und das Ergebnis ein ---*/
        opAdd,          //0C ()                         [Addition]
        opSub,          //0D ()                         [Subtraktion]
        opMult,         //0E ()                         [Multiplikation]
        opDiv,          //0F ()                         [Division ]
        cmpEQ,          //10 ()                         [Vergleich =  -> 0/1]
        cmpNE,          //11 ()                         [Vergleich #  -> 0/1]
        cmpLT,          //12 ()                         [Vergleich <  -> 0/1]
        cmpGT,          //13 ()                         [Vergleich >  -> 0/1]
        cmpLE,          //14 ()                         [Vergleich <= -> 0/1]
        cmpGE,          //15 ()                         [Vergleich >= -> 0/1]
                        /*--- Sprungbefehle ---*/
        call,           //16 (short ProzNr)             [Prozeduraufruf]
        retProc,        //17 ()                         [Rücksprung aus Prozedur]
        jmp,            //18 (short RelAdr)             [Sprung innerhalb der Funktion]
        jnot,           //19 (short RelAdr)             [Sprung innerhalb der Funktion, Bedingung stammt aus Keller]
        entryProc,      //1A (short lenCode,short ProcIdx,short lenVar)
        putStrg,        //1B (char[])
                        /*--- Zusätzliche, (für uns) nicht benötigte Befehle ---*/
        pop,            //1C
        swap,           //1D                            [Austausch Adresse gegen Wert]
        EndOfCode       //1E
    }

    /// <summary>
    /// Generiert Bytecode eines PL0-Programms.
    /// </summary>
    class CodeGenerator {

        /// <summary>
        /// Sprunglabel, das in einen Stack geschrieben wird, um später die relative Sprungadresse festzustellen.
        /// </summary>
        struct JumpLabel {
            public int jumpLabelPosition;
            public int jumpFrom;
            public int jumpTo;

            /// <summary>
            /// Weise dem Label die entsprechenden Werte zu.
            /// </summary>
            /// <param name="labelPosition">Position des Labels im Bytecode, wo später die relative Sprungadresse nachgetragen werden muss</param>
            /// <param name="from">Sprunganfang</param>
            /// <param name="to">Sprungende</param>
            public JumpLabel(int labelPosition, int from, int to) {
                jumpLabelPosition = labelPosition;
                jumpFrom = from;
                jumpTo = to;
            }
        }

        /// <summary>
        /// Buffert des gesamten Code, bevor er in Datei geschrieben wird.
        /// </summary>
        private List<Byte> codeBuffer = new List<Byte>();

        // Zähler zum Zwischenspeichern.
        private int currentProcedureLengthPosition;
        private int currentProcedureLength;
        private int procedureCount = 0;
        private int currentCodePosition = 0;

        // Stack der Sprunglabel.
        private Stack<JumpLabel> jumpLabelStack = new Stack<JumpLabel>();

        // Das Ziel: die kompilierte cl0-Datei.
        private String cl0FilePath;

        /// <summary>
        /// Erzeuge CodeGenerator mit dem Pfad der Quelldatei. 
        /// Die kompilierte Datei den gleichen Namen haben (mit der Endung .cl0).
        /// </summary>
        /// <param name="filePath"></param>
        public CodeGenerator(String filePath) {
            // Dateiendung von pl0 auf cl0 ändern.
            cl0FilePath = filePath.Remove(filePath.Length - 3);
            cl0FilePath += "cl0";
            // Sicherstellen, dass im Little Endian gearbeitet wird.
            if (!BitConverter.IsLittleEndian) {
                Parser.PrintError("Byteformat ", "'Big Endian'", " is not allowed. Quitting.");
                Environment.Exit(1);
            }
        }

        /// <summary>
        /// Generiert Code vom Befehl und den dazugehörigen Parametern.
        /// </summary>
        /// <param name="command">Befehl</param>
        /// <param name="parameters">Befehlsparameter</param>
        public void GenerateCode(CommandCode command, params int[] parameters) {
            // Befehl einfügen.
            Insert1Byte((int)command);
            // Bei entryProc Position für Prozedurlänge merken und diese zurück setzen.
            if (command == CommandCode.entryProc) {
                // Position der Länge merken.
                currentProcedureLengthPosition = currentCodePosition;
                currentProcedureLength = 1;
                procedureCount++;
            }
            // Alle Parameter einfügen.
            if (command != CommandCode.putStrg) {
                // Gewöhnliche Parameter als Bytepaar einfügen.
                foreach (var parameter in parameters) {
                    Insert2Byte(parameter);
                }
            } else {
                // Buchstaben von String als Byte einfügen.
                foreach (var parameter in parameters) {
                    Insert1Byte(parameter);
                }
                // Stringende einfügen.
                Insert1Byte(0);
            }
        }

        /// <summary>
        /// Generiert Code vom Befehl und einem dazugehörigen String.
        /// </summary>
        /// <param name="command">Befehl</param>
        /// <param name="stringValue">Stringparameter des Befehls</param>
        public void GenerateCode(CommandCode command, String stringValue) {
            // String in Char-Array umwandeln, damit es als Parameterliste zu übergeben ist.
            char[] parameters = stringValue.ToCharArray();
            // GenerateCode mit Int-Array aufrufen, in dem die Werte der Chars stecken.
            GenerateCode(command, Array.ConvertAll(parameters, c => (int)c));
        }

        /// <summary>
        /// Fügt ein Byte ein. Beispielsweise für Befehlscodes und Buchstaben eines Strings.
        /// </summary>
        /// <param name="value">Zahl kleiner 256.</param>
        private void Insert1Byte(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 42 -> 2A 00 00 00).
            byte[] byteArray = BitConverter.GetBytes(value);
            // Füge erstes Byte (little Endian) in Liste ein.
            codeBuffer.Add(byteArray[0]);
            // Prozedurlänge erhöhen.
            currentProcedureLength++;
            // Codeposition erhöhen.
            currentCodePosition++;
        }

        /// <summary>
        /// Fügt zwei Bytes ein. Beispielsweise für Adressen.
        /// </summary>
        /// <param name="value">Zahl kleiner 655356.</param>
        private void Insert2Byte(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 12345 -> 39 30 00 00).
            byte[] byteArray = BitConverter.GetBytes(value);
            // Füge ersten beiden Bytes (little Endian) in Liste ein.
            codeBuffer.Add(byteArray[0]);
            codeBuffer.Add(byteArray[1]);
            // Prozedurlänge erhöhen.
            currentProcedureLength += 2;
            // Codeposition erhöhen.
            currentCodePosition += 2;
        }

        /// <summary>
        /// Fügt vier Bytes ein. Beispielsweise Konstantenwerte.
        /// </summary>
        /// <param name="value">Zahl kleiner 655356.</param>
        private void Insert4Byte(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 123456789 -> 15 CD 5B 07).
            byte[] byteArray = BitConverter.GetBytes(value);
            // Füge ersten vier Bytes (little Endian) in Liste ein.
            codeBuffer.Add(byteArray[0]);
            codeBuffer.Add(byteArray[1]);
            codeBuffer.Add(byteArray[2]);
            codeBuffer.Add(byteArray[3]);
            // Prozedurlänge erhöhen.
            currentProcedureLength += 4;
            // Codeposition erhöhen.
            currentCodePosition += 4;
        }

        /// <summary>
        /// Aktualisiert Länge der aktuellen Prozedur im Bytecode.
        /// </summary>
        public void UpdateProcedureLength() {
            byte[] byteArray = BitConverter.GetBytes(currentProcedureLength);
            // Aktualisiere Byte an der Stelle, wo die Prozedurlänge der aktuellen Prozedur gespeichert ist.
            codeBuffer[currentProcedureLengthPosition] = byteArray[0];
            codeBuffer[currentProcedureLengthPosition + 1] = byteArray[1];
        }

        /// <summary>
        /// Erstellt Sprunglabel für den Sprung vorwärts.
        /// </summary>
        public void PrepareJumpForward() {
            // Position des Labels: fängt an der nächsten Stelle an (Position nach Sprungbefehl)
            // Startadresse: Adresse nach dem Sprungbefehl (inklusive 3 Byte Sprungbefehl)
            // Zieladresse: noch unbekannt
            jumpLabelStack.Push(new JumpLabel(currentCodePosition + 1, currentCodePosition + 3, 0));
        }

        /// <summary>
        /// Erstellt Sprunglabel für den Sprung vorwärts.
        /// </summary>
        public void PrepareJumpBackward() {
            // Position des Labels: noch unbekannt.
            // Startadresse: noch unbekannt.
            // Zieladresse: diese Adresse.
            jumpLabelStack.Push(new JumpLabel(-1, -1, currentCodePosition));
        }

        /// <summary>
        /// Aktualisiere relative Sprungadresse im Bytecode.
        /// </summary>
        /// <param name="commandSize">Bytes die auf relative Sprungadresse addiert werden müssen</param>
        public void UpdateJumpFoward(int commandSize = 0) {
            // Label holen.
            JumpLabel jumpLabel = jumpLabelStack.Pop();
            // Relative Sprungadresse berechnen (Ziel - Start). Wobei das Ziel die nächste Adresse ist (diese ist abhängig von der Größe des Befehls).
            int targetAddress = (currentCodePosition + commandSize) - jumpLabel.jumpFrom;
            // Sprungadresse an entsprechende Stelle nachtragen.
            byte[] byteArray = BitConverter.GetBytes(targetAddress);
            codeBuffer[jumpLabel.jumpLabelPosition] = byteArray[0];
            codeBuffer[jumpLabel.jumpLabelPosition + 1] = byteArray[1];
        }

        /// <summary>
        /// Hole die relative Sprungadresse des Rückwärtsprungs.
        /// </summary>
        /// <returns>Relative Sprungadresse</returns>
        public int GetJumpBackwardAddress() {
            // Label holen.
            JumpLabel jumpLabel = jumpLabelStack.Pop();
            // Relative Sprungadresse berechnen (Ziel - Start ... ergibt negative Zahl bspw. 21 - 42 = -21 = 0xFF FF FF EB)
            // Bei der Startadresse muss noch die Länge des Sprungbefehls (3) aufgerechnet werden.
            // Berechnete Adresse zurück geben. 
            return jumpLabel.jumpTo - (currentCodePosition + 3);
        }

        /// <summary>
        /// Ergänze Code um Konstantenblock um alle Konstanten.
        /// </summary>
        /// <param name="constants">Liste aller Konstanten</param>
        public void GenerateConstantBlock(List<NamelistConstant> constants) {
            // Jede Konstante als Bytepaar einfügen.
            foreach (var constant in constants) {
                Insert4Byte(constant.Value);
            }
        }

        /// <summary>
        /// Schreibe den gepufferten Code in die Datei und ergänze die Prozeduranzahl zu beginn.
        /// </summary>
        public void WriteCodeToFile() {
            try {
                using (var fileStream = new FileStream(cl0FilePath, FileMode.Create, FileAccess.Write)) {
                    // Anzahl der Prozeduren schreiben.
                    byte[] byteArray = BitConverter.GetBytes(procedureCount);
                    fileStream.WriteByte(byteArray[0]);
                    fileStream.WriteByte(byteArray[1]);
                    fileStream.WriteByte(byteArray[2]);
                    fileStream.WriteByte(byteArray[3]);
                    // Gepufferten Code schreiben.
                    foreach (var codeByte in codeBuffer) {
                        fileStream.WriteByte(codeByte);
                    }
                }
            } catch (Exception) {
                Parser.PrintError("Error while writing compiled code to file ", cl0FilePath, ".");
            }
        }
    }
}
