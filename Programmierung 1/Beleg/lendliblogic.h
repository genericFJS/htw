/**
 * @defgroup LendLibLogic
 * @brief Logische Funktionen rund um die Verleihverwaltung
 * 
 * - Struktur der Medienverwaltung im Speicher
 * - Sortieren und Durchsuchen der Medien
 * @{
 */

void insertItem(medium *iMedium);
void deleteItem(medium *iMedium);
void sortItems(int sortBy);
void findItem(char *sItem, int findBy);

///@}