#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

#define VBUFSIZE 128
#define BERUFSIZE 15
#define MITIDSIZE 3
#define VNAMESIZE 20
#define NNAMESIZE 20
#define ORTSIZE 30
#define GEBDATSIZE 10 //sizeof(SQLDATE)
#define TELNRSIZE 20
#define PRONRSIZE sizeof(SQLINTEGER)
#define PRONAMESIZE 20
#define ISTANTSIZE sizeof(SQLFLOAT)
#define PLANANTSIZE sizeof(SQLFLOAT)

int getBerufe(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf);
int getMitarbeiter(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitID);
int getMitDetails(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitID);
int getProjektDetails(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitID);


int main(int argc, char *argv[]) {
	// sql vars
	SQLHENV henv = SQL_NULL_HENV; // environment
	SQLHDBC hdbc = SQL_NULL_HDBC; // connection
	SQLHSTMT hstmt = SQL_NULL_HSTMT; // statement

	// sql connect
	sqlConnect(&henv, &hdbc, &hstmt);

	// input vars
	char beruf[BERUFSIZE + 1];
	char mitID[MITIDSIZE + 1];

	// program logic
	while (getBerufe(&henv, &hdbc, &hstmt, beruf)) {
		if (getMitarbeiter(&henv, &hdbc, &hstmt, beruf, mitID)) {
			if (getMitDetails(&henv, &hdbc, &hstmt, beruf, mitID)) {
				getProjektDetails(&henv, &hdbc, &hstmt, beruf, mitID);
			}
		}
	}

	puts("");

	// sql disconnect
	sqlDisconnect(&henv, &hdbc, &hstmt);

	return 0;
}

int getBerufe(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf) {
	// sql vars
	SQLCHAR kBeruf[BERUFSIZE + 1];
	SQLLEN bindLen;
	SQLRETURN rc;

	// input buffer
	char vBuf[VBUFSIZE];

	// SQL statement
	char *sqlStatement = "SELECT DISTINCT(Beruf) FROM Mitarbeiter";
	if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

	// perform the SQL statement
	rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
	if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	// bind columns
	rc = SQLBindCol(*hstmt, 1, SQL_C_CHAR, kBeruf, BERUFSIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, kOrt]", rc, *hstmt, SQL_HANDLE_STMT);

	puts("");

	// fetch and print each row of data
	int i = 0;
	while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
		// check error and warning
		if (rc == SQL_ERROR) {
			printf("SQLFetch [hstmt]: SQL_ERROR\n");
			break;
		}
		if (rc == SQL_SUCCESS_WITH_INFO) {
			printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
		}

		// process data
		printf("  %-*s\n", BERUFSIZE, kBeruf);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  Keine Berufe vorhanden.\n");
	}

	// get input
	printf("\n Beruf ? ");
	fgets(vBuf, VBUFSIZE, stdin);
	vBuf[strlen(vBuf) - 1] = 0;
	strncpy_s(beruf, BERUFSIZE, vBuf, VBUFSIZE);

	return strlen(beruf);
}

int getMitarbeiter(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitID) {
	// sql vars
	SQLCHAR mitVName[VNAMESIZE + 1];
	SQLCHAR mitNName[NNAMESIZE + 1];
	SQLLEN bindLen;
	SQLRETURN rc = 0;

	// input buffer
	char vBuf[VBUFSIZE];

	// SQL statement
	char *part1 = "SELECT MitID, Nachname, Vorname FROM Mitarbeiter WHERE Beruf = '";
	char *part2 = "'";
	int size = strlen(part1) + strlen(beruf) + strlen(part2) + 1;
	char *sqlStatement = malloc(sizeof(char)* size);
	sprintf_s(sqlStatement, sizeof(char) * size, "%s%s%s", part1, beruf, part2);
	if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

	// perform the SQL statement
	rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
	if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	// bind columns
	rc = SQLBindCol(*hstmt, 1, SQL_C_CHAR, mitID, MITIDSIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, mitID]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, mitNName, NNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, mitNName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 3, SQL_C_CHAR, mitVName, VNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 3, mitVName]", rc, *hstmt, SQL_HANDLE_STMT);

	puts("");

	// fetch and print each row of data
	int i = 0;
	while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
		// check error and warning
		if (rc == SQL_ERROR) {
			printf("SQLFetch [hstmt]: SQL_ERROR\n");
			break;
		}
		if (rc == SQL_SUCCESS_WITH_INFO) {
			printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
		}

		// process data
		printf("  %-*s %-*s %-*s\n", MITIDSIZE, mitID, NNAMESIZE, mitNName, VNAMESIZE, mitVName);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  Beruf '%s' ist nicht vorhanden.\n", beruf);
		printf("\n ? ");
		fgets(vBuf, sizeof(vBuf), stdin);
		printf("----------------------------------------------------------------------------\n");
		return 0;
	}

	// wait
	printf("\n Mitarbeiter-ID ? ");
	fgets(vBuf, VBUFSIZE, stdin);
	vBuf[strlen(vBuf) - 1] = 0;
	//strncpy_s(mitID, MITIDSIZE + 1 , vBuf, VBUFSIZE);
	strncpy_s(mitID, MITIDSIZE + 1, vBuf, MITIDSIZE);

	return 1;
}

int getMitDetails(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitID) {
	// sql vars
	SQLCHAR mitNName[VNAMESIZE + 1];
	SQLCHAR mitVName[NNAMESIZE + 1];
	SQLCHAR ort[ORTSIZE + 1];
	SQLCHAR gebDat[GEBDATSIZE + 1];
	SQLCHAR telNr[TELNRSIZE + 1];
	SQLLEN bindLen;
	SQLRETURN rc = 0;

	// input buffer
	char vBuf[VBUFSIZE];

	// SQL statement
	char *part1 = "SELECT Nachname, Vorname, Ort, Beruf, Gebdat, Telnr FROM Mitarbeiter WHERE Beruf = '";
	char *part2 = "' AND MitID='";
	char *part3 = "'";
	int size = strlen(part1) + strlen(beruf) + strlen(part2) + strlen(mitID) + strlen(part3) + 1;
	char *sqlStatement = malloc(sizeof(char)* size);
	sprintf_s(sqlStatement, sizeof(char) * size, "%s%s%s%s%s", part1, beruf, part2, mitID, part3);
	if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

	// perform the SQL statement
	rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
	if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	// bind columns
	rc = SQLBindCol(*hstmt, 1, SQL_C_CHAR, mitNName, NNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, mitNName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, mitVName, VNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, mitVName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 3, SQL_C_CHAR, ort, ORTSIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 3, ort]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 4, SQL_C_CHAR, beruf, BERUFSIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 4, beruf]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 5, SQL_C_CHAR, gebDat, GEBDATSIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 5, gebDat]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 6, SQL_C_CHAR, telNr, TELNRSIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 6, telNr]", rc, *hstmt, SQL_HANDLE_STMT);

	puts("");

	// fetch and print each row of data
	int i = 0;
	while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
		// check error and warning
		if (rc == SQL_ERROR) {
			printf("SQLFetch [hstmt]: SQL_ERROR\n");
			break;
		}
		if (rc == SQL_SUCCESS_WITH_INFO) {
			printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
		}

		// process data
		printf("  %-*s %-*s %-*s %-*s %-*s %-*s\n", NNAMESIZE, mitNName, VNAMESIZE, mitVName, ORTSIZE, ort, BERUFSIZE, beruf, GEBDATSIZE, gebDat, TELNRSIZE, telNr);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  '%s' ist in dem Kontext keine gueltige Mitarbeiter-ID.\n", mitID);
		printf("\n ? ");
		fgets(vBuf, sizeof(vBuf), stdin);
		printf("----------------------------------------------------------------------------\n");
		return 0;
	}

	return 1;	
}

int getProjektDetails(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf, char *mitID) {
	// sql vars
	SQLINTEGER proNr;
	SQLCHAR proName[PRONAMESIZE + 1];
	SQLDOUBLE istAnt;
	SQLDOUBLE planAnt;
	SQLCHAR istAnt2[4];
	SQLCHAR planAnt2[4];
	SQLLEN bindLen;
	SQLRETURN rc = 0;

	// input buffer
	char vBuf[VBUFSIZE];

	// SQL statement
	char *part1 = "SELECT p.ProNr, p.ProName, z.Istanteil, z.Plananteil FROM Zuordnung z JOIN Projekt p ON p.ProNr = z.ProNr WHERE z.MitID ='";
	char *part2 = "'";
	int size = strlen(part1) + strlen(mitID) + strlen(part1) + 1;
	char *sqlStatement = malloc(sizeof(char)* size);
	sprintf_s(sqlStatement, sizeof(char) * size, "%s%s%s", part1, mitID, part2);
	if (DEBUGINFO) printf("sqlStatement: \"%s\"\n", sqlStatement);

	// perform the SQL statement
	rc = SQLExecDirect(*hstmt, (SQLCHAR *)sqlStatement, SQL_NTS);
	if (!checkReturnCode("SQLExecDirect [hstmt, sqlStatement2]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	// bind columns
	rc = SQLBindCol(*hstmt, 1, SQL_C_LONG, &proNr, 0, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, proNr]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, proName, PRONAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, proName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 3, SQL_C_DOUBLE, &istAnt, 1024, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 3, &istAnt]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 4, SQL_C_DOUBLE, &planAnt, 1024, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 4, &planAnt]", rc, *hstmt, SQL_HANDLE_STMT);
	//rc = SQLBindCol(*hstmt, 3, SQL_C_FLOAT, &istAnt, 0, &bindLen);
	//checkReturnCode("SQLBindCol [hstmt, 3, &istAnt]", rc, *hstmt, SQL_HANDLE_STMT);
	//rc = SQLBindCol(*hstmt, 4, SQL_C_FLOAT, &planAnt, 0, &bindLen);
	//checkReturnCode("SQLBindCol [hstmt, 4, &planAnt]", rc, *hstmt, SQL_HANDLE_STMT);

	// fetch and print each row of data
	int i = 0;
	while ((rc = SQLFetch(*hstmt)) != SQL_NO_DATA) {
		// check error and warning
		if (rc == SQL_ERROR) {
			printf("SQLFetch [hstmt]: SQL_ERROR\n");
			break;
		}
		if (rc == SQL_SUCCESS_WITH_INFO) {
			//printf("SQLFetch [hstmt]: SQL_SUCCESS_WITH_INFO\n");
		}

		// process data
		printf("  %ld %-*s %.2f %.2f \n", proNr, PRONAMESIZE, proName, istAnt, planAnt);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  '%s' hat keine Projekte.\n", mitID);
		printf("\n ? ");
		fgets(vBuf, sizeof(vBuf), stdin);
		printf("----------------------------------------------------------------------------\n");
		return 0;
	}

	// wait
	printf("\n ? ");
	fgets(vBuf, sizeof(vBuf), stdin);
	printf("----------------------------------------------------------------------------\n");

	return 1;
}

// Testdaten: Mitarbeiter 103
// Mitarbeiter ohne Projekt: 110 (Vertreter)