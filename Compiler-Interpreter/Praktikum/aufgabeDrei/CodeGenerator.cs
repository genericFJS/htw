using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace pl0Compiler {

    enum CommandCode : int {
        /*--- Kellerbefehle ---*/
        puValVrLocl,    //00 (short Displ)              [Kellern Wert lokale Variable]
        puValVrMain,    //01 (short Displ)              [Kellern Wert Main Variable]
        puValVrGlob,    //02 (short Displ,short Proc)   [Kellern Wert globale Variable]
        puAdrVrLocl,    //03 (short Displ)	            [Kellern Adresse lokale Variable]
        puAdrVrMain,    //04 (short Displ)	            [Kellern Adresse Main Variable]
        puAdrVrGlob,    //05 (short Displ,short Proc)   [Kellern Adresse globale Variable]
        puConst,        //06 (short Index)	            [Kellern einer Konstanten]
        storeVal,       //07 ()							[Speichern Wert ->Adresse, beides aus Keller]
        putVal,         //08 ()							[Ausgabe eines Wertes aus Keller nach stdout]
        getVal,         //09 () 		                [Eingabe eines Wertes von stdin -> Addr. im Keller ]
                        /*--- arithmetische Befehle ---*/
        vzMinus,        //0A ()						 	[Vorzeichen ]
        odd,            //0B ()						 	[ungerade -> 0/1]
                        /*--- binäre Operatoren kellern 2 Operanden aus und das Ergebnis ein ---*/
        opAdd,          //0C ()						 	[Addition]
        opSub,          //0D ()						 	[Subtraktion ]
        opMult,         //0E ()						 	[Multiplikation ]
        opDiv,          //0F ()						 	[Division ]
        cmpEQ,          //10 ()						 	[Vergleich =  -> 0/1]
        cmpNE,          //11 ()						 	[Vergleich #  -> 0/1]
        cmpLT,          //12 ()						 	[Vergleich <  -> 0/1]
        cmpGT,          //13 ()						 	[Vergleich >  -> 0/1]
        cmpLE,          //14 ()						 	[Vergleich <= -> 0/1]
        cmpGE,          //15 ()						 	[Vergleich >= -> 0/1]
                        /*--- Sprungbefehle ---*/
        call,           //16 (short ProzNr) [Prozeduraufruf]
        retProc,        //17 ()							[Rücksprung]
        jmp,            //18 (short RelAdr)             [SPZZ innerhalb der Funktion]
        jnot,           //19 (short RelAdr)             [SPZZ innerhalb der Funkt.,Beding.aus Keller]
        entryProc,      //1A (short lenCode,short ProcIdx,short lenVar)
                        /*--- Zusätzliche, (für uns) nicht benötigte Befehle ---*/
        putStrg,        //1B (char[])
        pop,            //1C
        swap,           //1D							[Austausch Adresse gegen Wert]
        EndOfCode 	    //1E
    }

    class CodeGenerator {

        struct JumpLabel {
            public int jumpLabelPosition;
            public int jumpFrom;
            public int jumpTo;

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

        private int currentProcedureLengthPosition;
        private int currentProcedureLength;
        private int procedureCount = 0;
        private int currentCodePosition = 0;

        private Stack<JumpLabel> jumpLabelList = new Stack<JumpLabel>();

        private String cl0FilePath;

        /// <summary>
        /// Erzeuge CodeGenerator mit dem Pfad der Quelldatei. 
        /// Die kompilierte Datei den gleichen Namen haben (mit der Endung .cl0).
        /// </summary>
        /// <param name="filePath"></param>
        public CodeGenerator(String filePath) {
            cl0FilePath = filePath.Remove(filePath.Length - 3);
            cl0FilePath += "cl0";
            if (!BitConverter.IsLittleEndian) {
                Parser.PrintError("Byteformat ", "Big Endian", " ist nicht erlaubt. Beende.");
                Environment.Exit(1);
            }
        }

        /// <summary>
        /// Generiert Code von dem Befehl.
        /// </summary>
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

        public void GenerateCode(CommandCode command, String stringValue) {
            // String in Char-Array umwandeln, damit es als Parameterliste zu übergeben ist.
            char[] parameters = stringValue.ToCharArray();
            // GenerateCode mit Int-Array aufrufen, in dem die Werte der Chars stecken.
            GenerateCode(command, Array.ConvertAll(parameters, c => (int)c));
        }

        /// <summary>
        /// Füge ein Byte ein. Beispielsweise für Befehlscodes und Buchstaben eines Strings.
        /// </summary>
        /// <param name="value">Zahl kleiner 256.</param>
        private void Insert1Byte(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 42 -> 2A 00 00 00)
            byte[] byteArray = BitConverter.GetBytes(value);
            // Füge erstes Byte (little Endian) in Liste ein.
            codeBuffer.Add(byteArray[0]);
            // Prozedurlänge erhöhen.
            currentProcedureLength++;
            // Codeposition erhöhen.
            currentCodePosition++;
        }

        /// <summary>
        /// Füge zwei Bytes ein. Beispielsweise für Adressen.
        /// </summary>
        /// <param name="value">Zahl kleiner 655356.</param>
        private void Insert2Byte(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 12345 -> 39 30 00 00)
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
        /// Füge vier Bytes ein. Beispielsweise Konstantenwerte.
        /// </summary>
        /// <param name="value">Zahl kleiner 655356.</param>
        private void Insert4Byte(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 123456789 -> 15 CD 5B 07)
            byte[] byteArray = BitConverter.GetBytes(value);
            // Füge ersten beiden Bytes (little Endian) in Liste ein.
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
        /// Aktualisiere Länge der aktuellen Prozedur.
        /// </summary>
        /// <param name="length"></param>
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
            jumpLabelList.Push(new JumpLabel(currentCodePosition + 1, currentCodePosition + 3, 0));
        }

        public void PrepareJumpBackward() {
            // Position des Labels: noch unbekannt.
            // Startadresse: noch unbekannt.
            // Zieladresse: diese Adresse.
            jumpLabelList.Push(new JumpLabel(-1, -1, currentCodePosition));
        }

        public void UpdateJumpFoward(int commandSize = 0) {
            // Label holen.
            JumpLabel jumpLabel = jumpLabelList.Pop();
            // Relative Sprungadresse berechnen (Ziel - Start). Wobei das Ziel die nächste Adresse ist (diese ist abhängig von der Größe des Befehls).
            int targetAddress = (currentCodePosition + commandSize) - jumpLabel.jumpFrom;
            // Sprungadresse an entsprechende Stelle nachtragen.
            byte[] byteArray = BitConverter.GetBytes(targetAddress);
            codeBuffer[jumpLabel.jumpLabelPosition] = byteArray[0];
            codeBuffer[jumpLabel.jumpLabelPosition + 1] = byteArray[1];
        }

        public int GetJumpBackwardAddress() {
            // Label holen.
            JumpLabel jumpLabel = jumpLabelList.Pop();
            // Relative Sprungadresse berechnen (Ziel - Start ... ergibt negative Zahl bspw. 21 - 42 = -21 = 0xFF FF FF EB)
            // Bei der Startadresse muss noch die Länge des Sprungbefehls (3) aufgerechnet werden.
            // Berechnete Adresse zurück geben. 
            return jumpLabel.jumpTo - (currentCodePosition + 3) ;
        }

        /// <summary>
        /// Ergänze Code um Konstantenblock.
        /// </summary>
        /// <param name="constants"></param>
        public void GenerateConstantBlock(List<NamelistConstant> constants) {
            // Jede Konstante als Bytepaar einfügen.
            foreach (var constant in constants) {
                Insert4Byte(constant.Value);
            }
        }

        /// <summary>
        /// Schreibe den gepufferten Code in die Datei.
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
                    // gepufferten Code schreiben.
                    foreach (var codeByte in codeBuffer) {
                        fileStream.WriteByte(codeByte);
                    }
                }
            } catch (Exception ex) {
                Console.WriteLine("Exception caught in process: {0}", ex);
            }
        }
    }
}
