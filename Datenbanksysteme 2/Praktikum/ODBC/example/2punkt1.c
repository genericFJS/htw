#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

#define VBUFSIZE 128
#define BERUFSIZE 15
#define MITIDSIZE 3
#define NAMESIZE 20

int getBerufe(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *ort);
int getKunden(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt, char *ort);

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
		//getKunden(&henv, &hdbc, &hstmt, ort);
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
	printf("\n nochmal ? ");
	fgets(vBuf, VBUFSIZE, stdin);
	vBuf[strlen(vBuf) - 1] = 0;
	//strncpy(ort, vBuf, ORTSIZE); // linux
	strncpy_s(beruf, BERUFSIZE, vBuf, VBUFSIZE); // windows

	return strlen(beruf);
}