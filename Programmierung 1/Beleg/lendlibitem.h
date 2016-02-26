/**
 * @defgroup LendLibItem
 * @brief Funktionen und Deklarationen rund um ausgeliehene Medien.
 * @{
 */

/**
 * @brief Typ des ausgeliehenen Mediums.
 */
typedef enum{
	other,	///< Medium ohne Kategorie
	book,	///< Bücher
	cd,		///< CDs
	dvd		///< DVDs
} mType;

/**
 * @brief Das ausgeliehene Medium.
 */
typedef struct{
	mType	type;	///< Typ des ausgeliehen Mediums
	char*	title;		///< Titel des Mediums
	char*	author;		///< Autor bzw. Interpret des Mediums
	char*	lendee;		///< Name der Person, dem das Medium verliehen wurde
} medium;

void createItem(int ntype, char* ntitle, char* nauthor, char* nlendee);
/// @}