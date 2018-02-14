#if defined DEBUG

#include <stdio.h>

#define FNAME "DEBUG.dbg"
FILE *ProtFile;  /* externe und static-Variablen haben bei 
                    Programmstart den Wert 0 (KernRi s. 83) */

#define DEBUG_STR(Str ) {\
                        if (ProtFile==NULL) ProtFile=fopen(FNAME,"w");\
                        fprintf(ProtFile,"%s",Str);\
                        fclose (ProtFile);\
                        ProtFile=fopen(FNAME,"a");\
                        }

#define DEBUG_INT(iVal) {\
                        if (ProtFile==NULL) ProtFile=fopen(FNAME,"w");\
                        fprintf(ProtFile,"%d",iVal);\
                        fclose (ProtFile);\
                        ProtFile=fopen(FNAME,"a");\
                        }

#define DEBUG_CHR(cVal) {\
                        if (ProtFile==NULL) ProtFile=fopen(FNAME,"w");\
                        fprintf(ProtFile,"%c",cVal);\
                        fclose (ProtFile);\
                        ProtFile=fopen(FNAME,"a");\
                        }

#define DEBUG_LNG(lVal) {\
                        if (ProtFile==NULL) ProtFile=fopen(FNAME,"w");\
                        fprintf(ProtFile,"%ld",lVal);\
                        fclose (ProtFile);\
                        ProtFile=fopen(FNAME,"a");\
                        }

#define DEBUG_UNL(uVal) {\
                        if (ProtFile==NULL) ProtFile=fopen(FNAME,"w");\
                        fprintf(ProtFile,"%lu",uVal);\
                        fclose (ProtFile);\
                        ProtFile=fopen(FNAME,"a");\
                        }
#define DEBUG_PRN(Argl) {\
                        if (ProtFile==NULL) ProtFile=fopen(FNAME,"w");\
                        fprintf Argl;\
                        fclose (ProtFile);\
                        ProtFile=fopen(FNAME,"a");\
                        }

#else
#define DEBUG_STR(Str ) /**/

#define DEBUG_INT(iVal) /**/

#define DEBUG_CHR(cVal) /**/

#define DEBUG_LNG(lVal) /**/

#define DEBUG_UNL(uVal) /**/

#endif

