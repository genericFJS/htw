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
	in,		///< folgende Eingabe
	out,	///< normale Ausgabe
	error,	///< Fehlermeldungen
	status,	///< Statusmeldungen
	extra	///< Fehlerbehebung
} ptype;

void libprint(ptype type, const char* printable, ...);
void setColor(int ptype);
void resetColor();
void printHead();
void printTLine(char type, int length);
void printItems();
void printFoot();
void sleep_ms(int milliseconds);

///@}