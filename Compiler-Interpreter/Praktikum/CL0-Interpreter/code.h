typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;

typedef enum TCODE
{
  /*--- Kellerbefehle ---*/
  puValVrLocl,/*00 (short Displ)  [Kellern Wert lokale  Variable]             */
  puValVrMain,/*01 (short Displ)  [Kellern Wert Main    Variable]             */
  puValVrGlob,/*02 (short Displ,short Proc)  [Kellern Wert globale Variable]  */
  puAdrVrLocl,/*03 (short Displ)  [Kellern Adresse lokale  Variable]          */
  puAdrVrMain,/*04 (short Displ)  [Kellern Adresse Main    Variable]          */
  puAdrVrGlob,/*05 (short Displ,short Proc) [Kellern Adresse globale Variable]*/
  puConst    ,/*06 (short Index)  [Kellern einer Konstanten]                  */
  storeVal   ,/*07 ()           [Speichern Wert -> Adresse, beides aus Keller]*/
  putVal     ,/*08 ()           [Ausgabe eines Wertes aus Keller nach stdout] */
  getVal     ,/*09 ()           [Eingabe eines Wertes von stdin in Adresse aus Keller ]  */
  /*--- arithmetische Befehle ---*/
  vzMinus    ,/*0A ()           [Vorzeichen -]                                */
  odd        ,/*0B ()           [ungerade -> 0/1]                             */
  /*--- binaere Operatoren kellern 2 Operanden aus und das Ergebnis ein ----*/
  OpAdd      ,/*0C ()           [Addition]                                    */
  OpSub      ,/*0D ()           [Subtraktion ]                                */
  OpMult     ,/*0E ()           [Multiplikation ]                             */
  OpDiv      ,/*0F ()           [Division ]                                   */
  cmpEQ      ,/*10 ()           [Vergleich = -> 0/1]                          */
  cmpNE      ,/*11 ()           [Vergleich # -> 0/1]                          */
  cmpLT      ,/*12 ()           [Vergleich < -> 0/1]                          */
  cmpGT      ,/*13 ()           [Vergleich > -> 0/1]                          */
  cmpLE      ,/*14 ()           [Vergleich <=-> 0/1]                          */
  cmpGE      ,/*15 ()           [Vergleich >=-> 0/1]                          */
  /*--- Sprungbefehle ---*/
  call       ,/*16 (short ProzNr) [Prozeduraufruf]                              */
  retProc    ,/*17 ()           [Ruecksprung]                                 */
  jmp        ,/*18 (short RelAdr) [SPZZ innerhalb der Funktion]               */
  jnot       ,/*19 (short RelAdr) [SPZZ innerhalb der Funkt.,Beding.aus Keller]*/
  entryProc  ,/*1A (short lenCode,short ProcIdx,lenVar)                       */

  /* Code f�r Spracherweiterungen */
  putStrg    ,/*1B (char[])                                                   */
  pop        ,/*1C  Entfernt einen Wert aus dem Stack - nicht implentiert     */
  swap       ,/*1D  Austausch Adressse gegen Wert     - nicht implementiert   */

  EndOfCode   /*1E               fuer interne Verwendung durch die VM         */
}tCode;
#define MAX_LEN_OF_CODE 81
