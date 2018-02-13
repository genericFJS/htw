/********************************************************************************
* A. Beck (2011)
* Diese Variante verwendet int32_t anstelle von int um Kompatibilität zw.
* 32-bit und 64-bit-systemen zu wahren
* ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "code.h"
#include "debug.h"

#define OK 1
#define FAIL 0
typedef struct {
	char* pCode;
	char* pVar;
	/*int   nProc;*/
}tInfProc;

/*--------------------------------------------------------------------------*/
FILE     *pCodeFile;
char     *pCode, *pC;
int       Ende = 0;
long      SizeCode;
/*--------------------------------------------------------------------------*/

short gtSrtPar(char*pX) {
	return (unsigned char)* pX
		| (unsigned char)(*(pX + 1)) << 8;
}

long gtLngPar(char*pX) {
	return ((unsigned char)* pX
		| (unsigned char)*(pX + 1) << 8
		| (unsigned char)*(pX + 2) << 16
		| (unsigned char)*(pX + 3) << 24);
}

/*--------------------------------------------------------------------------*/
/*--- Implementation der Befehle  ------------------------------------------*/

/*--- Push Value Variable local ---*/
int FcpuValVrLocl(void) {
	unsigned short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X\n", "PushValVarLocal", Displ);
	return OK;
}

/*--- Push Value Variable main ---*/
int FcpuValVrMain(void) {
	unsigned   short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X\n", "PushValVarMain", Displ);
	return OK;
}

/*--- Push Value Variable global ---*/
int FcpuValVrGlob(void) {
	unsigned   short Displ;
	short iProc;
	Displ = gtSrtPar(pC); pC += 2;
	iProc = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X,%04X\n", "PushValVarGobal", Displ, iProc);
	return OK;
}

/*--- Push Address Variable local ---*/
int FcpuAdrVrLocl(void) {
	unsigned   short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X\n", "PushAdrVarLocal", Displ);
	return OK;
}

/*--- Push Address Variable main ---*/
int FcpuAdrVrMain(void) {
	unsigned   short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X\n", "PushAdrVarMain", Displ);
	return OK;
}

/*--- Push Address Variable global ---*/
int FcpuAdrVrGlob(void) {
	unsigned  short Displ;
	short iProc;
	Displ = gtSrtPar(pC); pC += 2;
	iProc = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X, %04X\n", "PushAdrVarGobal", Displ, iProc);
	return OK;
}

/*--- Push Value Constant ---*/
int FcpuConst(void) {
	unsigned  short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X\n", "PushConst", Displ);
	return OK;
}

/*--- Store Value From Stack To Address From Stack ---*/
int FcstoreVal(void) {
	printf("%-20s\n", "StoreVal");
	return OK;
}

/*--- Output Value From Stack ---*/
int FcputVal(void) {
	printf("%-20s\n", "PutVal");
	return OK;
}

/*--- Input Value To Address From Stack ---*/
int FcgetVal(void) {
	printf("%-20s\n", "GetVal");
	return OK;
}

/*--- Sign '-' On Stack ---*/
int FcvzMinus(void) {
	printf("%-20s\n", "VzMinus");
	return OK;
}

/*--- Sign 'ODD' On Stack ---*/
int Fcodd(void) {
	printf("%-20s\n", "Odd");
	return OK;
}

/*--- Operand From Stack + Operand From Stack To Stack ---*/
int FcOpAdd(void) {
	printf("%-20s\n", "Add");
	return OK;
}

/*--- Operand From Stack - Operand From Stack To Stack ---*/
int FcOpSub(void) {
	printf("%-20s\n", "Sub");
	return OK;
}

/*--- Operand From Stack * Operand From Stack To Stack ---*/
int FcOpMult(void) {
	printf("%-20s\n", "Mul");
	return OK;
}

/*--- Operand From Stack * Operand From Stack To Stack ---*/
int FcOpDiv(void) {
	printf("%-20s\n", "Div");
	return OK;
}

/*--- Test Operator From Stack == Operator From Stack: 1 else 0 To Stack ---*/
int FccmpEQ(void) {
	printf("%-20s\n", "CmpEqual");
	return OK;
}

/*--- Test Operator From Stack != Operator From Stack: 1 else 0 To Stack ---*/
int FccmpNE(void) {
	printf("%-20s\n", "CmpNotEqual");
	return OK;
}

/*--- Test Operator From Stack <  Operator From Stack: 1 else 0 To Stack ---*/
int FccmpLT(void) {
	printf("%-20s\n", "CmpLessThen");
	return OK;
}

/*--- Test Operator From Stack >  Operator From Stack: 1 else 0 To Stack ---*/
int FccmpGT(void) {
	printf("%-20s\n", "CmpGreaterThen");
	return OK;
}

/*--- Test Operator From Stack <= Operator From Stack: 1 else 0 To Stack ---*/
int FccmpLE(void) {
	printf("%-20s\n", "CmpLessEqual");
	return OK;
}

/*--- Test Operator From Stack >= Operator From Stack: 1 else 0 To Stack ---*/
int FccmpGE(void) {
	printf("%-20s\n", "CmpGeaterEqual");
	return OK;
}

/*--- Jump Displacement ---*/
int Fcjmp(void) {
	unsigned  short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	//pC+=(long)Displ;
	printf("%-20s %04X\n", "Jmp", Displ);
	return OK;
}

/*--- Jump if Value From Stack == 0 ---*/
int Fcjnot(void) {
	unsigned  short Displ;
	Displ = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X\n", "JmpNot", Displ);
	return OK;
}

/*--- Entry Procedure */
int FcEntryProc(void) {
	short lVar, lCode, ProcNr;
	lCode = gtSrtPar(pC); pC += 2;
	ProcNr = gtSrtPar(pC); pC += 2;
	lVar = gtSrtPar(pC); pC += 2;

	printf("%-20s %04X,%04X,%04X <-- Procedure\n", "EntryProc", lCode, ProcNr, lVar);
	return OK;
}

/*--- Return From Procedure ---*/
int FcRetProc(void) {
	printf("%-20s\n", "ReturnProc");
	if (*pC != entryProc) {
		int i;
		for (i = 0; (pC < pCode + SizeCode); i++, pC += 4)
			printf("Const %04d:%04d\n", i, *((int32_t*)pC));
		Ende = 1;
	}
	return OK;
}

/*--- CALL Procedure ---*/
int Fccall(void) {
	short ProcNr;
	ProcNr = gtSrtPar(pC); pC += 2;
	printf("%-20s %04X\n", "Call", ProcNr);
	return OK;
}

/*--- Leave The Interpreter ---*/
int FcEndOfCode(void)  // Wird nie erreicht!!
{
	return OK;
}

int FcputStrg(void) {
	printf("%-20s ", "PutString");
	while (*pC)
		//    if(*pC=='\\'&&*(pC+1)=='n'){fputc('\n',stdout);pC+=2;}
		//    else                       
	{
		fputc(*pC, stdout); pC++;
	}
	printf("\n");
	pC++;
	/*printf("%s",pC);*/
	/*pC+=strlen(pC)+1;*/
	return OK;
}

int Fpop(void) {
	printf("%-20s\n", "Pop");
	/*  puts("pop");*/
	return OK;
}

int Fswap(void) {
	printf("%-20s\n", "Swap");
	return OK;
}

int Fcput(void) {
	printf("%-20s\n", "Put");
	return OK;
}

int Fcget(void) {
	printf("%-20s\n", "Get");
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
		printf("No Codefile\n"); exit(-1);
	}
	strcpy(vName, argv[1]);
	if (strstr(vName, ".cl0") == NULL) strcat(vName, ".cl0");
	pCodeFile = fopen(vName, "rb");

	/*--- Speicher bereitstellen ---*/
	fseek(pCodeFile, 0, SEEK_END);
	SizeCode = (size_t)ftell(pCodeFile);
	fseek(pCodeFile, 0, SEEK_SET);
	pCode = malloc(SizeCode + sizeof(long));
	if (pCode == NULL) { printf("no Memory to read Code\n"); exit(-1); }
	/*--- Datei lesen ---*/
	LenRead = fread(pCode, sizeof(char), SizeCode, pCodeFile);
	if (LenRead != SizeCode) {
		printf("Read Error\n"); exit(-1);
	}
	fclose(pCodeFile);
	/*--- Proceduretabelle aufbauen ---*/

	/*
	nProc=(short)(*pCode+*(pCode+1)*256);
	if ((nProc==0)||(nProc>32766))
					{printf("illegal Codefile\n"); exit (-1);}
	pInfProc=malloc(nProc*sizeof(tInfProc));
	pStack  =malloc(StackSize);
	if (pInfProc==NULL)
					{printf("No Memory for ProcTable\n"); exit (-1);}
	if (pStack==NULL)
					{printf("No Memory for Stack\n"); exit (-1);}
	pS=pStack;
	/* Nachbildung eines CALL im Stack
	push4(0L);
	push4((long)pExitProgram);
	push4(0L);
	{
	  short X;
	   int iProc,iPrCnt;
	  for (iPrCnt=0,pC=pCode+4;iPrCnt<nProc;iPrCnt++)
	  {
		iProc=gtSrtPar(pC+3);
		pInfProc[iProc].pCode=pC;
		pInfProc[iProc].pVar =0;
		if (iPrCnt+1<nProc) pC+=     (gtSrtPar(pC+1));
		else             pConst=pC + (X=gtSrtPar(pC+1));
	  }
	}
	*/
	pC = pCode + 4;
	while (!Ende) {
		printf("%04lX: %02X ", pC - pCode - 4, *pC);
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
	/*  free(pInfProc);*/
	return OK;
}

