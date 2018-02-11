using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace aufgabeDrei {

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
        OpAdd,          //0C ()						 	[Addition]
        OpSub,          //0D ()						 	[Subtraktion ]
        OpMult,         //0E ()						 	[Multiplikation ]
        OpDiv,          //0F ()						 	[Division ]
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
        /// <summary>
        /// Buffert des gesamten Code, bevor er in Datei geschrieben wird.
        /// </summary>
        private List<Byte> codeBuffer = new List<Byte>();

        private int currentProcedureLengthPosition;
        private int currentProcedureLength;

        private String cl0FilePath;

        public CodeGenerator(String filePath) {
            cl0FilePath = filePath.Remove(filePath.Length - 3);
            cl0FilePath += "cl0";
        }

        /// <summary>
        /// Generiert Code von dem Befehl.
        /// </summary>
        public void GenerateCode(CommandCode command, params int[] parameters) {
            // Befehl einfügen.
            InsertByte((int)command);
            // Bei entryProc Position für Prozedurlänge merken und diese zurück setzen.
            if (command == CommandCode.entryProc) {
                currentProcedureLengthPosition = codeBuffer.Count();
                currentProcedureLength = 1;
            }
            // Alle Parameter einfügen.
            if (command != CommandCode.putStrg) {
                // Gewöhnliche Parameter als Bytepaar einfügen.
                foreach (var parameter in parameters) {
                    InsertBytes(parameter);
                }
            } else {
                // Buchstaben von String als Byte einfügen.
                foreach (var parameter in parameters) {
                    InsertByte(parameter);
                }
                // Stringende einfügen.
                InsertByte(0);
            }
        }

        /// <summary>
        /// Füge ein Byte ein. Beispielsweise für Befehlscodes und Buchstaben eines Strings.
        /// </summary>
        /// <param name="value">Zahl kleiner 655356.</param>
        private void InsertByte(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 42 -> 2A 00 00 00)
            byte[] byteArray = BitConverter.GetBytes(value);
            // Füge erstes Byte (little Endian) in Liste ein.
            codeBuffer.Add(byteArray[0]);
            // Prozedurlänge erhöhen.
            currentProcedureLength++;
        }

        /// <summary>
        /// Füge zwei Bytes ein. Beispielsweise für Adressen und Variablen-/Konstantenwerte.
        /// </summary>
        /// <param name="value">Zahl kleiner 256.</param>
        private void InsertBytes(int value) {
            // Konvertiere Zahl zu Byte-Arary (Beispiel: 12345 -> 39 30 00 00)
            byte[] byteArray = BitConverter.GetBytes(value);
            // Füge ersten beiden Bytes (little Endian) in Liste ein.
            codeBuffer.Add(byteArray[0]);
            codeBuffer.Add(byteArray[1]);
            // Prozedurlänge erhöhen.
            currentProcedureLength += 2;
        }

        /// <summary>
        /// Aktualisiere Länge der aktuellen Prozedur.
        /// </summary>
        /// <param name="length"></param>
        private void UpdateProcedureLength() {
            byte[] byteArray = BitConverter.GetBytes(currentProcedureLength);
            // Aktualisiere Byte an der Stelle, wo die Prozedurlänge der aktuellen Prozedur gespeichert ist.
            codeBuffer[currentProcedureLengthPosition] = byteArray[0];
            codeBuffer[currentProcedureLengthPosition + 1] = byteArray[1];
        }
    }
}
