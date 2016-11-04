#include "helper.h"

void sqlConnect(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt)
{
	// sql vars
	SQLRETURN rc;

	// allocate environment handle
	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, henv);
	if (!checkReturnCode("SQLAllocHandle [henv]", rc, *henv, SQL_HANDLE_ENV)){
		freeSQLHandles(henv, hdbc, SQL_NULL_HSTMT);
		exit(0);
	}

	rc = SQLSetEnvAttr(*henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER*)SQL_OV_ODBC3, 0);
	if (!checkReturnCode("SQLSetEnvAttr [henv]", rc, henv, SQL_HANDLE_ENV)){
		freeSQLHandles(henv, hdbc, SQL_NULL_HSTMT);
		exit(0);
	}

	// allocate connection handle
	rc = SQLAllocHandle(SQL_HANDLE_DBC, *henv, hdbc);
	if (!checkReturnCode("SQLAllocHandle [hdbc]", rc, *hdbc, SQL_HANDLE_DBC)){
		freeSQLHandles(henv, hdbc, SQL_NULL_HSTMT);
		exit(0);
	}

	// set login timeout to 5 seconds
	rc = SQLSetConnectAttr(*hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);
	if (!checkReturnCode("SQLSetConnectAttr [hdbc]", rc, *hdbc, SQL_HANDLE_DBC)){
		freeSQLHandles(henv, hdbc, SQL_NULL_HSTMT);
		exit(0);
	}

	// linux
	// connect to data source
	/*char* server = "MSSQLSERVER";
	char* login = "stud01";
	char* password = "stud01";
	rc = SQLConnect(*hdbc, (SQLCHAR*)server, SQL_NTS, (SQLCHAR*)login, SQL_NTS, (SQLCHAR*)password, SQL_NTS);
	if (!checkReturnCode("SQLConnect [hdbc]", rc, *hdbc, SQL_HANDLE_DBC)) {
		freeSQLHandles(henv, hdbc, hstmt);
		exit(0);
	}*/

	// windows
	// sql driver connect
	SQLCHAR retconstring[1024];
	char *connStr = "DRIVER={SQL Server};SERVER=141.56.2.45,1433;DATABASE=ii15s74053;UID=s74053;PWD=s74053;";
	rc = SQLDriverConnect(*hdbc, NULL, (SQLCHAR*)connStr, SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT);
	if (!checkReturnCode("SQLDriverConnect [hdbc]", rc, *hdbc, SQL_HANDLE_DBC)) {
		freeSQLHandles(henv, hdbc, SQL_NULL_HSTMT);
		exit(0);
	}

	// allocate statement handle
	rc = SQLAllocHandle(SQL_HANDLE_STMT, *hdbc, hstmt);
	if (!checkReturnCode("SQLAllocHandle [hstmt]", rc, *hstmt, SQL_HANDLE_STMT)) {
		freeSQLHandles(henv, hdbc, hstmt);
		exit(0);
	}
}

void sqlDisconnect(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt) {
	SQLRETURN rc = SQLCancel(*hstmt);
	checkReturnCode("SQLCancel [hstmt]", rc, hstmt, SQL_HANDLE_STMT);
	freeSQLHandles(henv, hdbc, SQL_NULL_HSTMT);
}

void freeSQLHandles(SQLHENV *henv, SQLHDBC *hdbc, SQLHSTMT *hstmt) {
	SQLRETURN rc;

	// free handles
	// statement
	if (hstmt != SQL_NULL_HSTMT) {
		rc = SQLFreeHandle(SQL_HANDLE_STMT, *hstmt);
		checkReturnCode("SQLFreeHandle [hstmt]", rc, *hstmt, SQL_HANDLE_STMT);
	}

	// connection
	if (hdbc != SQL_NULL_HDBC) {
		rc = SQLDisconnect(*hdbc);
		checkReturnCode("SQLDisconnect [hdbc]", rc, *hdbc, SQL_HANDLE_DBC);
		rc = SQLFreeHandle(SQL_HANDLE_DBC, *hdbc);
		checkReturnCode("SQLFreeHandle [hdbc]", rc, *hdbc, SQL_HANDLE_DBC);
	}

	// environment
	if (henv != SQL_NULL_HENV) {
		rc = SQLFreeHandle(SQL_HANDLE_ENV, *henv);
		checkReturnCode("SQLFreeHandle [henv]", rc, *henv, SQL_HANDLE_ENV);
	}
}

int checkReturnCode(char* title, SQLRETURN rc, SQLHANDLE handle, SQLSMALLINT type) {
	if (rc == SQL_SUCCESS) {
		if (DEBUGINFO == 1) printf("%s ... true\n", title);
		return 1;
	}

	printf("%s ... ", title);
	if (rc == SQL_SUCCESS_WITH_INFO) {
		printf("true (Warning!)\n");
		extractError(handle, type);
		return 1;
	}
	else {
		printf("false\n^\n");
		extractError(handle, type);
		printf("\n");
		return 0;
	}
}

// http://www.easysoft.com/developer/languages/c/odbc_tutorial.html#diags_retrieve
void extractError(SQLHANDLE handle, SQLSMALLINT type) {
	SQLSMALLINT i = 0;
	SQLINTEGER native;
	SQLCHAR state[7];
	SQLCHAR text[256];
	SQLSMALLINT len;
	SQLRETURN ret;

	do {
		ret = SQLGetDiagRec(type, handle, ++i, state, &native, text,
			sizeof(text), &len);
		if (SQL_SUCCEEDED(ret))
			printf("%s:%d:%ld:%s\n", state, i, native, text);
	} while (ret == SQL_SUCCESS);
}
