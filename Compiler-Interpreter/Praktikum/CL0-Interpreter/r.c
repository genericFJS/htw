/********************************************************************************
 * A. Beck (2011)
 * Diese Variante verwendet int32_t anstelle von int um Kompatibilität zw.
 * 32-bit und 64-bit-systemen zu wahren
 * ******************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#define int32_t int32_t
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "code.h"
#include "debug.h"

#define OK 1
#define FAIL 0
#define INIT_STACK_SIZE 4096
#define EXTD_STACK_SIZE 1024

typedef struct {
	char* pCode;
	char* pVar;
	/*int   nProc;*/
}tInfProc;

/*--------------------------------------------------------------------------*/
FILE     *pCodeFile;
char     *pCode, *pC;
char     *pStack, *pS;
char     *pConst;
tInfProc *pInfProc;
size_t    SizeCode;
short     nProc;
int       StackSize = INIT_STACK_SIZE;
char      ExitProgram = EndOfCode, *pExitProgram = &ExitProgram;
short     iCProc;
short     Ende;

/*--------------------------------------------------------------------------*/
int ExtendStack(void);

#define wr4(pD,x) (*((int32_t* )(pD))=x)
#define wr2(pD,x) (*((short*)(pD))=x)
#define rd4(pS)   (*((int32_t* )(pS)))
#define rd2(pS)   (*((short*)(pS)))

short gtSrtPar(char*pX) {
	return (unsigned char)* pX
		| (unsigned char)(*(pX + 1)) << 8;
}

int32_t gtLngPar(char*pX) {
	return ((unsigned char)* pX
		| (unsigned char)*(pX + 1) << 8
		| (unsigned char)*(pX + 2) << 16
		| (unsigned char)*(pX + 3) << 24);
}

int push4(int32_t x) {
	if ((pS + 4) >= pStack + StackSize)
		if (ExtendStack() == FAIL) { printf("No Memory To Extend Stack\n"); exit(-1); }
	wr4(pS, x);
	pS += 4;
	return OK;
}
int32_t pop4(void) {
	if (pS - 4 < pStack) { printf("Stackunderflow\n"); exit(-1); }
	pS -= 4;
	return rd4(pS);
}
int push2(short x) {
	if ((pS + 2) >= pStack + StackSize)
		if (ExtendStack() == FAIL) { printf("No Memory To Extend Stack\n"); exit(-1); }
	wr2(pS, x);
	pS += 2;
	return OK;
}
short pop2(void) {
	pS -= 2;
	return rd4(pS);
}
int ExtendStack(void) {
	char* pX = realloc(pStack, StackSize += EXTD_STACK_SIZE);
	if (pX != NULL) {
		pStack = pX;
		return OK;
	} else return FAIL;
}
/*--------------------------------------------------------------------------*/
/*--- Implementation der Befehle  ------------------------------------------*/

/*--- Push Value Variable local ---*/
int FcpuValVrLocl(void) {
	short Displ;
	int32_t Val;
	Displ = gtSrtPar(pC); pC += 2;
	Val = rd4(pInfProc[iCProc].pVar + Displ);
	wr4(pS, Val);
	pS += 4;
	DEBUG_STR("puValVrLocl ("); DEBUG_LNG((int32_t)Displ); DEBUG_STR(")->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Push Value Variable main ---*/
int FcpuValVrMain(void) {
	short Displ;
	int32_t Val;
	Displ = gtSrtPar(pC); pC += 2;
	Val = rd4(pInfProc[0].pVar + Displ);
	wr4(pS, Val);
	pS += 4;
	DEBUG_STR("puValVrMain ("); DEBUG_LNG((int32_t)Displ); DEBUG_STR(")->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Push Value Variable global ---*/
int FcpuValVrGlob(void) {
	short Displ;
	short iProc;
	int32_t  Val;
	Displ = gtSrtPar(pC); pC += 2;
	iProc = gtSrtPar(pC); pC += 2;
	Val = rd4(pInfProc[iProc].pVar + Displ);
	wr4(pS, Val);
	DEBUG_STR("puValVrGlbl ("); DEBUG_LNG((int32_t)Displ); DEBUG_LNG((int32_t)iProc); DEBUG_STR(")->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	pS += 4;
	return OK;
}

/*--- Push Address Variable local ---*/
int FcpuAdrVrLocl(void) {
	short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	wr4(pS, (int32_t)((long)(pInfProc[iCProc].pVar + Displ)));
	pS += 4;
	DEBUG_STR("puAdrVrLocl ("); DEBUG_LNG((int32_t)Displ); DEBUG_STR(")"); DEBUG_STR("\n");
	return OK;
}

/*--- Push Address Variable main ---*/
int FcpuAdrVrMain(void) {
	short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	wr4(pS, (int32_t)((long)(pInfProc[0].pVar + Displ)));
	pS += 4;
	DEBUG_STR("puAdrVrMain ("); DEBUG_LNG((int32_t)Displ); DEBUG_STR(")"); DEBUG_STR("\n");
	return OK;
}

/*--- Push Address Variable global ---*/
int FcpuAdrVrGlob(void) {
	short Displ;
	short iProc;
	Displ = gtSrtPar(pC); pC += 2;
	iProc = gtSrtPar(pC); pC += 2;
	wr4(pS, (int32_t)((long)(pInfProc[iProc].pVar + Displ)));
	pS += 4;
	DEBUG_STR("puAdrVrGlobl ("); DEBUG_LNG((int32_t)Displ); DEBUG_LNG((int32_t)iProc); DEBUG_STR(")"); DEBUG_STR("\n");
	return OK;
}

/*--- Push Value Constant ---*/
int FcpuConst(void) {
	short Displ;
	int32_t Val;
	Displ = gtSrtPar(pC); pC += 2;
	wr4(pS, Val = gtLngPar(pConst + Displ * sizeof(int32_t)));
	DEBUG_STR("puConst ("); DEBUG_LNG((int32_t)Displ); DEBUG_STR(")->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	pS += 4;
	return OK;
}

/*--- Store Value From Stack To Address From Stack ---*/
int FcstoreVal(void) {
	int32_t Val, *pDest;
	pS -= 4;
	Val = rd4(pS);
	pS -= 4;
	pDest = (int32_t*)(long)rd4(pS);
	*pDest = Val;
	DEBUG_STR("StoreVal <-"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Output Value From Stack ---*/
int FcputVal(void) {
	int32_t Val;
	pS -= 4;
	printf("%d", Val = rd4(pS));
#ifdef NEWLINE
	printf("\n");
#endif
	DEBUG_STR("PutVal <-"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Input Value To Address From Stack ---*/
int FcgetVal(void) {
	int32_t *pDest, l;
	pS -= 4;
	l = rd4(pS);
	pDest = (int32_t*)(long)l;
	scanf("%d", pDest);
	DEBUG_STR("GetVal\n");
	return OK;
}

/*--- Sign '-' On Stack ---*/
int FcvzMinus(void) {
	int32_t Val;
	Val = rd4(pS - 4);
	Val = wr4(pS - 4, -Val);
	DEBUG_STR("VzMinus ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Sign 'ODD' On Stack ---*/
int Fcodd(void) {
	int32_t Val;
	Val = rd4(pS - 4);
	Val = wr4(pS - 4, Val & 1);
	DEBUG_STR("Odd ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Operand From Stack + Operand From Stack To Stack ---*/
int FcOpAdd(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = wr4(pS - 4, Val1 + Val2);
	DEBUG_STR("OpAdd ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Operand From Stack - Operand From Stack To Stack ---*/
int FcOpSub(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = wr4(pS - 4, Val1 - Val2);
	DEBUG_STR("OpSub ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Operand From Stack * Operand From Stack To Stack ---*/
int FcOpMult(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = wr4(pS - 4, Val1*Val2);
	DEBUG_STR("OpMul ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Operand From Stack * Operand From Stack To Stack ---*/
int FcOpDiv(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = wr4(pS - 4, Val1 / Val2);
	DEBUG_STR("OpDiv ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Test Operator From Stack == Operator From Stack: 1 else 0 To Stack ---*/
int FccmpEQ(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = (Val1 == Val2);
	wr4(pS - 4, Val);
	DEBUG_STR("cmpEQ ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Test Operator From Stack != Operator From Stack: 1 else 0 To Stack ---*/
int FccmpNE(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = (Val1 != Val2);
	wr4(pS - 4, Val);
	DEBUG_STR("cmpNE ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Test Operator From Stack <  Operator From Stack: 1 else 0 To Stack ---*/
int FccmpLT(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = (Val1 < Val2);
	wr4(pS - 4, Val);
	DEBUG_STR("cmpLT ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Test Operator From Stack >  Operator From Stack: 1 else 0 To Stack ---*/
int FccmpGT(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = (Val1 > Val2);
	wr4(pS - 4, Val);
	DEBUG_STR("cmpGT ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Test Operator From Stack <= Operator From Stack: 1 else 0 To Stack ---*/
int FccmpLE(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = (Val1 <= Val2);
	wr4(pS - 4, Val);
	DEBUG_STR("cmpLE ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Test Operator From Stack >= Operator From Stack: 1 else 0 To Stack ---*/
int FccmpGE(void) {
	int32_t Val, Val1, Val2;
	pS -= 4;
	Val2 = rd4(pS);
	Val1 = rd4(pS - 4);
	Val = (Val1 >= Val2);
	wr4(pS - 4, Val);
	DEBUG_STR("cmpGE ->"); DEBUG_LNG(Val); DEBUG_STR("\n");
	return OK;
}

/*--- Jump Displacement ---*/
int Fcjmp(void) {
	short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	pC += (int32_t)Displ;
	DEBUG_STR("Jmp ("); DEBUG_LNG((int32_t)Displ); DEBUG_STR(")\n");
	return OK;
}

/*--- Jump if Value From Stack == 0 ---*/
int Fcjnot(void) {
	short Displ;
	int32_t Val;
	pS -= 4;
	Displ = gtSrtPar(pC); pC += 2;
	if ((Val = rd4(pS)) == 0) pC += Displ;
	DEBUG_STR("JmpNot ("); DEBUG_LNG((int32_t)Displ);
	DEBUG_LNG((int32_t)Val); DEBUG_STR(")\n");
	return OK;
}

/*--- Entry Procedure */
int FcEntryProc(void) {
	short lVar;
	pC += 2;
	iCProc = gtSrtPar(pC); pC += 2;
	lVar = gtSrtPar(pC); pC += 2;
	pInfProc[iCProc].pVar = pS;       /* Zeiger auf Variablenbereich */
	pS += lVar;                  /* Neuer Stackpointer          */
	DEBUG_STR("EntryProc ("); DEBUG_LNG((int32_t)iCProc);
	DEBUG_LNG((int32_t)lVar); DEBUG_STR(")\n");
	return OK;
}

/*--- Return From Procedure ---*/
int FcRetProc(void) {
	pS = pInfProc[iCProc].pVar;
	DEBUG_STR("Return From "); DEBUG_LNG((int32_t)iCProc);
	iCProc = pop4();
	pC = (char*)(long)pop4();
	pInfProc[iCProc].pVar = (char*)(long)pop4();
	DEBUG_STR(" TO "); DEBUG_LNG((int32_t)iCProc); DEBUG_STR("\n");
	return OK;
}

/*--- CALL Procedure ---*/
int Fccall(void) {
	short ProcNr;
	DEBUG_STR("Call From "); DEBUG_LNG((int32_t)iCProc);
	ProcNr = gtSrtPar(pC); pC += 2;
	push4((int32_t)(long)(pInfProc[iCProc].pVar));
	push4((int32_t)(long)pC);
	pC = pInfProc[ProcNr].pCode;
	push4(iCProc);
	DEBUG_STR(" TO "); DEBUG_LNG((int32_t)ProcNr); DEBUG_STR("\n");
	return OK;
}

/*--- Leave The Interpreter ---*/
int FcEndOfCode(void) {
	Ende = 1;
	return OK;
}

int FcputStrg(void) {
	printf("%s", pC);
#ifdef NEWLINE
	printf("\n");
#endif

	pC += strlen(pC) + 1;
}

int Fswap(void) {
	int32_t *pDest = (int32_t*)(long)pop4();
	int32_t  Val = *pDest;
	push4(Val);
	return OK;
}

int Fpop(void) {
	pop4();
	/*  puts("pop");*/
	return OK;
}
/*-----------------------------------------------------------*/

/* Aufbau des Codefiles                                      */
/* Len    Inhalt                   Bemerkungen               */
/*  4     Anzahl Prozeduren                                  */
/*  7     1Annnnmmmmllll   n:Codelen, m:Procnummer, l:Varlen */
/*        Code der Prozedur                                  */
/*  7     1Annnnmmmmllll   n:Codelen, m:Procnummer, l:Varlen */
/*        Code der Prozedur                                  */
/*  . . .                                                    */
/*        Konstanten                                         */

int main(int argc, char*argv[]) {
	size_t LenRead;

	char vName[128 + 1];

	/*--- Datei oeffnen ---*/
	if (argc <= 1) {
		printf("Codefile: ");
		fgets(vName, sizeof(vName), stdin);
		size_t ln = strlen(vName) - 1;
		if (vName[ln] == '\n')
			vName[ln] = '\0';
		printf("========================\n");
	} else {
		strcpy(vName, argv[1]);
	}
	if (strstr(vName, ".cl0") == NULL) 
		strcat(vName, ".cl0");
	pCodeFile = fopen(vName, "rb");
	if (pCodeFile == NULL) {
		fprintf(stderr, "Could not open Codefile %s\n", vName);
		exit(-1);
	}
	/*--- Speicher bereitstellen ---*/
	fseek(pCodeFile, 0, SEEK_END);
	SizeCode = (size_t)ftell(pCodeFile);
	fseek(pCodeFile, 0, SEEK_SET);
	pCode = malloc(SizeCode + sizeof(int32_t));
	if (pCode == NULL) { printf("no Memory to read Code\n"); exit(-1); }
	/*--- Datei lesen ---*/
	LenRead = fread(pCode, sizeof(char), SizeCode, pCodeFile);
	if (LenRead != SizeCode) {
		printf("Read Error\n"); exit(-1);
	}
	fclose(pCodeFile);
	/*--- Proceduretabelle aufbauen ---*/
	nProc = (short)(*pCode + *(pCode + 1) * 256);
	if ((nProc == 0) || (nProc > 32766)) {
		printf("illegal Codefile\n"); exit(-1);
	}
	pInfProc = malloc(nProc * sizeof(tInfProc));
	pStack = malloc(StackSize);
	if (pInfProc == NULL) {
		printf("No Memory for ProcTable\n"); exit(-1);
	}
	if (pStack == NULL) {
		printf("No Memory for Stack\n"); exit(-1);
	}
	pS = pStack;
	/* Nachbildung eines CALL im Stack */
	push4(0L);
	push4((int32_t)(long)pExitProgram);
	push4(0L);
	{
		short X;
		int iProc, iPrCnt;
		for (iPrCnt = 0, pC = pCode + 4; iPrCnt < nProc; iPrCnt++) {
			iProc = gtSrtPar(pC + 3);
			pInfProc[iProc].pCode = pC;
			pInfProc[iProc].pVar = 0;
			if (iPrCnt + 1 < nProc) pC += (gtSrtPar(pC + 1));
			else             pConst = pC + (X = gtSrtPar(pC + 1));
		}
	}

	while (!Ende) {

#ifdef _TEST_ 
		fprintf(stderr, "%02X\n", *(pC + 1));
#endif

		switch (*pC++) {
		case puValVrLocl:FcpuValVrLocl(); break;
		case puValVrMain:FcpuValVrMain(); break;
		case puValVrGlob:FcpuValVrGlob(); break;
		case puAdrVrLocl:FcpuAdrVrLocl(); break;
		case puAdrVrMain:FcpuAdrVrMain(); break;
		case puAdrVrGlob:FcpuAdrVrGlob(); break;
		case puConst:FcpuConst();     break;
		case storeVal:FcstoreVal();    break;
		case putVal:FcputVal();      break;
		case getVal:FcgetVal();      break;
		case vzMinus:FcvzMinus();     break;
		case odd:Fcodd();         break;
		case OpAdd:FcOpAdd();       break;
		case OpSub:FcOpSub();       break;
		case OpMult:FcOpMult();      break;
		case OpDiv:FcOpDiv();       break;
		case cmpEQ:FccmpEQ();       break;
		case cmpNE:FccmpNE();       break;
		case cmpLT:FccmpLT();       break;
		case cmpGT:FccmpGT();       break;
		case cmpLE:FccmpLE();       break;
		case cmpGE:FccmpGE();       break;
		case call:Fccall();        break;
		case retProc:FcRetProc();     break;
		case jmp:Fcjmp();         break;
		case jnot:Fcjnot();        break;
		case entryProc:FcEntryProc();   break;
		case putStrg:FcputStrg();     break;
		case pop:Fpop();          break;
		case swap:Fswap();         break;
		case EndOfCode:FcEndOfCode();   break;
		}
	}
	free(pCode);
	free(pInfProc);
	return OK;
}

