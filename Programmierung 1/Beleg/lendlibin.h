/**
 * @defgroup LendLibIn
 * @brief Funktionen für jegliche Art von Ausgabe.
 * @{
 */

#define MALLOCERR "Fehler bei der Speicherzuweisung"

FILE *libdb;
char vbuf[128];
const char *filename;

void readfile();
int getSize(FILE *libdb);
void getInput();
char * strtok2 (char * str, char const * delims);

/// @}