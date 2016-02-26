/**
 * @defgroup LendLibOut
 * @brief Funktionen für jegliche Art von Ausgabe.
 * 
 * Ausgabe abhängig von den übers kompilieren definierten Parameter: 
 * @param CGI		für eine .cgi-Datei
 * @param DCOLOR	für eingefärbte Terminalausgaben
 * @{
 */

/**
 * @brief Verschieden Ausgabemöglichkeiten.
 */
typedef enum{
	status,	///< Statusmeldungen
	out,	///< normale Ausgabe
	error	///< Fehlermeldungen
} ptype;

///@}

void libprint(ptype type, const char* printable, ...);
void printHead();
void printTLine(char type, int length);