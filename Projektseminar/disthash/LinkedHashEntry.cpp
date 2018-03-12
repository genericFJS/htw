/// <summary>
/// LinkedHashEntry beschreibt einen Eintrag in der HashMap, der zeitgleich auch eine (einfach verkettete) Überlaufliste darstellt.
/// </summary>
#include "LinkedHashEntry.h"

/// <summary>
/// Erstelle neue verkettete Liste, die mit dem gegebenen Schlüssel und Wert als Eintrag beginnt.
/// </summary>
/// <param name="key">Schlüssel des neuen Eintrags</param>
/// <param name="value">Wert des neuen Eintrags</param>
LinkedHashEntry::LinkedHashEntry(int key, string value) {
	this->key = key;
	this->value = value;
	this->next = NULL;
}

/// <summary>
/// Gibt den Schlüssel des Eintrags zurück.
/// </summary>
/// <returns>Schlüssel des Eintrags</returns>
int LinkedHashEntry::getKey() {
	return key;
}

/// <summary>
/// Gibt den Wert des Eintrags zurück.
/// </summary>
/// <returns>Wert (Zeichenkette) des Eintrags</returns>
string LinkedHashEntry::getValue() {
	return value;
}

/// <summary>
/// Setzt den Wert des Eintrags auf den übergebenen.
/// </summary>
/// <param name="value">Neuer Wert des Eintrags</param>
void LinkedHashEntry::setValue(string value) {
	this->value = value;
}

/// <summary>
/// Gibt den nächsten Eintrag zurück.
/// </summary>
/// <returns>Nächster Eintrag</returns>
LinkedHashEntry* LinkedHashEntry::getNext() {
	return next;
}

/// <summary>
/// Setzt den nächsten Eintrag.
/// </summary>
/// <param name="next">Neuer nächster Eintrag</param>
void LinkedHashEntry::setNext(LinkedHashEntry *next) {
	this->next = next;
}