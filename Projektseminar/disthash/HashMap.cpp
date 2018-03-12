/// <summary>
/// HashMap realisiert die Hashtabelle. Bis auf die Berechnung des Schlüssels ist sie unabhängig von der Anwendung, von der sie benötigt wird.
/// </summary>
#include "HashMap.h"

extern int numProcesses;
extern int mode;

/// <summary>
/// Initialisiert die HashMap: Ein Tabelle von LinkedHashEntrys der entsprechenden Größe wird angelegt und vorerst mit NULL gefüllt.
/// </summary>
/// <param name="tableSize">Größe der HashMap (Anzahl der Einträge)</param>
HashMap::HashMap(int tableSize) {
	table = new LinkedHashEntry*[tableSize];
	this->tableSize = tableSize;
	for (int i = 0; i < tableSize; i++)
		table[i] = NULL;
}

/// <summary>
/// Alle Elemente von vorhandenen LinkedHashEntrys werden vor dem Löschen der Tabelle gelöscht.
/// </summary>
HashMap::~HashMap() {
	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {
			LinkedHashEntry *prevEntry = NULL;
			LinkedHashEntry *entry = table[i];
			while (entry != NULL) {
				prevEntry = entry;
				entry = entry->getNext();
				delete prevEntry;
			}
		}
	}
	delete[] table;
}

/// <summary>
/// Berechnet den Key abhängig vom Modus, der Tabellengröße und gegebenenfalls von der Anzahl der Prozessen.
/// </summary>
/// <param name="key">Key des Eintrags</param>
/// <returns>Key des Eintrags in der HashMap</returns>
int HashMap::GetHashKey(int key) {
	if (mode == MODE_DISTRIBUTED)
		return (key / numProcesses) % tableSize;
	else
		return key % tableSize;
}

/// <summary>
/// Gibt den Eintrag (Value) des entsprechenden Keys. Dazu wird gegebenenfalls der LinkedHashEntry durchsucht.
/// </summary>
/// <param name="key">Key des Eintrags.</param>
/// <returns>Leer, wenn Key nicht vorhanden. Value, sonst.</returns>
string HashMap::Get(int key) {
	int hash = GetHashKey(key);
	if (table[hash] == NULL) {
		return string();
	} else {
		LinkedHashEntry *entry = table[hash];
		while (entry != NULL && entry->getKey() != key)
			entry = entry->getNext();
		if (entry == NULL)
			return string();
		else
			return entry->getValue();
	}
}

/// <summary>
/// Fügt einen Eintrag (Key mit entsprechendem Value) in die HashMap ein. Falls noch kein Eintrag an der HashMap-Stelle existiert, wird ein neuer erzeugt.
/// Ansonsten wird in der LinkkedHashEntry nach dem Key gesucht und ggf. ein neuer Eintrag angehängt.
/// </summary>
/// <param name="key">Der Key des zu erstellenden Eintrags.</param>
/// <param name="value">Der Value des zu erstellenden Eintrags.</param>
void HashMap::Insert(int key, string value) {
	int hash = GetHashKey(key);
	if (table[hash] == NULL) {
		table[hash] = new LinkedHashEntry(key, value);
	} else {
		LinkedHashEntry *entry = table[hash];
		while (entry->getNext() != NULL && entry->getKey() != key)
			entry = entry->getNext();
		if (entry->getKey() == key)
			entry->setValue(value);
		else
			entry->setNext(new LinkedHashEntry(key, value));
	}
	//printf("Inserted: %d, %s.\n", key, this->Get(key).c_str());
}

/// <summary>
/// Löscht ein Element aus der HashMap anhand des Keys.
/// </summary>
/// <param name="key">Der Key des zu löschenden Eintrags.</param>
/// <returns>true, wenn Eintrag gelöscht wurde. false, wenn Eintrag nicht gelöscht wurde (weil er nicht existiert).</returns>
bool HashMap::Delete(int key) {
	int hash = GetHashKey(key);
	// Überprüfe, ob Element existiert. Sonst kann nichts gelöscht werden.
	if (table[hash] != NULL) {
		LinkedHashEntry *prevEntry = NULL;
		LinkedHashEntry *entry = table[hash];
		// Durchsuche LinkedHashEntry nach Element.
		while (entry->getNext() != NULL && entry->getKey() != key) {
			prevEntry = entry;
			entry = entry->getNext();
		}
		// Wenn Element gefunden, lösche es.
		if (entry->getKey() == key) {
			// Wenn Element am Anfang steht, lösche es und setze das nächste Element als Startelement des LinkedHashEntry. Ansonsten nehme Element aus dem LinkedHashEntry.
			if (prevEntry == NULL) {
				LinkedHashEntry *nextEntry = entry->getNext();
				delete entry;
				table[hash] = nextEntry;
			} else {
				LinkedHashEntry *next = entry->getNext();
				delete entry;
				prevEntry->setNext(next);
			}
			//printf("Deleted: %d.\n", key);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}