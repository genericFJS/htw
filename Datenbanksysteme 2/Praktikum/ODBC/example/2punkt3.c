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
#define GEBDATSIZE sizeof(SQLDATE)
#define TELNRSIZE 20
#define PRONRSIZE sizeof(SQLINTEGER)
#define PRONAMESIZE 20
#define ISTANTSIZE sizeof(SQLFLOAT)
#define PLANANTSIZE sizeof(SQLFLOAT)

int getBerufe(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *ort);
int getMitarbeiter(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *ort);
int getProjekte(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *ort);

int main(int argc, char *argv[]) {
	// sql vars
	SQLHENV henv = SQL_NULL_HENV; // environment
	SQLHDBC hdbc = SQL_NULL_HDBC; // connection
	SQLHSTMT hstmt = SQL_NULL_HSTMT; // statement

									 // input vars
	char beruf[BERUFSIZE + 1];

	// sql connect
	sqlConnect(&henv, &hdbc, &hstmt);

	// program logic
	while (getBerufe(&henv, &hdbc, &hstmt, beruf)) {
		getMitarbeiter(&henv, &hdbc, &hstmt, beruf);
		getProjekte(&henv, &hdbc, &hstmt, beruf);
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
	//strncpy(ort, vBuf, ORTSIZE); // linux
	strncpy_s(beruf, BERUFSIZE, vBuf, VBUFSIZE); // windows

	return strlen(beruf);
}

int getMitarbeiter(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *beruf) {
	// sql vars
	SQLINTEGER mitID;
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
	rc = SQLBindCol(*hstmt, 1, SQL_C_LONG, &mitID, 0, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, mitID]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, mitNName, NNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, mitNName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 3, SQL_C_CHAR, mitVName, VNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, mitVName]", rc, *hstmt, SQL_HANDLE_STMT);

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
		printf("  %ld %-*s %-*s\n", mitID, NNAMESIZE, mitNName, VNAMESIZE, mitVName);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  Beruf '%s' ist nicht vorhanden.\n", beruf);
		return 0;
	}

	// wait
	printf("\n Mitarbeiter-ID ? ");
	fgets(vBuf, sizeof(vBuf), stdin);

	return 0;
}


int getProjekte(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *mitID) {
	// sql vars
	SQLCHAR mitNName[VNAMESIZE + 1];
	SQLCHAR mitVName[NNAMESIZE + 1];
	SQLCHAR ort[ORTSIZE + 1];
	SQLCHAR beruf[BERUFSIZE + 1];
	SQLDATE gebDat[GEBDATSIZE + 1];
	SQLCHAR telNr[TELNRSIZE + 1];
	SQLINTEGER proNr;
	SQLCHAR proName[PRONAMESIZE + 1];
	SQLFLOAT istAnt;
	SQLFLOAT sollAnt;
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
	rc = SQLBindCol(*hstmt, 1, SQL_C_LONG, &mitID, 0, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 1, mitID]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 2, SQL_C_CHAR, mitNName, NNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, mitNName]", rc, *hstmt, SQL_HANDLE_STMT);
	rc = SQLBindCol(*hstmt, 3, SQL_C_CHAR, mitVName, VNAMESIZE + 1, &bindLen);
	checkReturnCode("SQLBindCol [hstmt, 2, mitVName]", rc, *hstmt, SQL_HANDLE_STMT);

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
		printf("  %ld %-*s %-*s\n", mitID, NNAMESIZE, mitNName, VNAMESIZE, mitVName);

		i++;
	}

	// cancel statement handle
	rc = SQLCancel(*hstmt);
	if (!checkReturnCode("SQLCancel [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt); exit(0);
	}

	if (i == 0) {
		printf("  Beruf '%s' ist nicht vorhanden.\n", beruf);
		return 0;
	}

	// wait
	printf("\n ? ");
	fgets(vBuf, sizeof(vBuf), stdin);

	return 0;	
}