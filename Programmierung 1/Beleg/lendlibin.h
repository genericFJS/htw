/**
 * @defgroup LendLibIn
 * @brief Funktionen für jegliche Art von Ausgabe.
 * @{
 */

#define MALLOCERR "Fehler bei der Speicherzuweisung"

FILE *libdb;
char vbuf[128];
const char *filename;
char posted[256];
char pTemp1[256];
char pTemp2[256];
char pTemp3[256];

void readfile();
int getSize(FILE *libdb);
void getInput();
char * strtok2 (char * str, char const * delims);
void getPost();

/// @}