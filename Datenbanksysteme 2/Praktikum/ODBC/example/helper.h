#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlext.h>
#include <sql.h>

#define DEBUGINFO 0

void sqlConnect(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt);
void sqlDisconnect(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt);
void freeSQLHandles(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt);
int checkReturnCode(char *title, SQLRETURN rc, SQLHANDLE handle, SQLSMALLINT type);
void extractError(SQLHANDLE handle, SQLSMALLINT type);
