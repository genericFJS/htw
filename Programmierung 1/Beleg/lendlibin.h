/**
 * @defgroup LendLibIn
 * @brief Funktionen für jegliche Art von Ausgabe.
 * @{
 */

#define CSVFILE lendlib.csv

FILE *libdb;
int listSize = 0;


void readfile();
int getSize(FILE *libdb);

/// @}