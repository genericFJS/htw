#include "MyLibs.h"

int colors[13] = { 31, 32, 33, 34, 35, 36, 91, 92, 93, 94, 95, 96, 97 };

/// <summary>
/// Ruft printf mit den übergebenen Argumenten auf, färbt die Ausgabe allerdings (entsprechend des Prozesses) ein.
/// </summary>
/// <param name="text">Text</param>
/// <param name="">Argumente</param>
void PrintColored(const char * text, ...) {
	extern int rank;
	extern bool verbose;
	if (verbose) {
		printf("\x1b[%dm", colors[rank % 13]);
		va_list args;
		va_start(args, text);
		vprintf(text, args);
		va_end(args);
		printf("\x1b[0m");
	}
}