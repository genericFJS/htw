/// <summary>
/// MPIHash stellt die Schnittstelle zur eigentlichen HashMap dar. Durch sie werden Anfragen an die Threads gestellt und durch die Threads verarbeitet.
/// </summary>
#include "MPIHash.h"

extern int rank;
extern int numProcesses;
extern MPI_Comm thread_comm;
extern int mode;

/// <summary>
/// Erstellt neue HashMap mit der übergebenen Größe.
/// </summary>
/// <param name="hashmapSize">Gewünschte Größe der HashMap</param>
MPIHash::MPIHash(int hashmapSize) {
	hashMap = new HashMap(hashmapSize);
}

/// <summary>
/// Löscht HashMap.
/// </summary>
MPIHash::~MPIHash() {
	delete hashMap;
}

/// <summary>
/// Berechnet die Nummer des Prozesses, der für diesen Eintrag/Schlüssel verantwortlich ist.
/// </summary>
/// <param name="key">Schlüssel des Eintrags</param>
/// <returns>Prozessnummer, von dem Schlüssel verarbeitet wird</returns>
int MPIHash::GetDistHashLocation(int key) {
	if (mode < MODE_DISTRIBUTED) {
		// REMOTE
		return 1;
	} else {
		// DISTRIBUTED
		return key % numProcesses;
	}
}

/// <summary>
/// Fügt Eintrag in die lokale HashMap ein. Nur vom zuständigen Thread auszuführen!
/// </summary>
/// <param name="key">Key</param>
/// <param name="value">Value</param>
void MPIHash::InsertEntry(int key, string value) {
	hashMap->Insert(key, value);
}

/// <summary>
/// Holt den Eintrag aus der HashMap. Nur vom zuständigen Thread auszuführen!
/// </summary>
/// <param name="key">Schlüssel des Eintrags</param>
/// <returns>Eintrag</returns>
string MPIHash::GetEntry(int key) {
	return hashMap->Get(key);
}

/// <summary>
/// Löscht den Eintrag aus der HashMap. Nur vom zuständigen Thread auszuführen!
/// </summary>
/// <param name="key">Schlüssel des Eintrags</param>
/// <returns>Erfolg des Löschvorgangs</returns>
bool MPIHash::DeleteEntry(int key) {
	return hashMap->Delete(key);
}

/// <summary>
/// Fügt Eintrag in die HashMap des zuständigen Prozesses ein.
/// </summary>
/// <param name="key">Schlüssel des Eintrags</param>
/// <param name="value">Wert des Eintrags</param>
void MPIHash::InsertDistEntry(int key, string value) {
	int destination;
	int valueSize;
	char* valueArray;
	int action = ACTION_INS;
	if (mode == MODE_DISTRIBUTED || (mode == MODE_REMOTE && rank == 0)) {
		// DISTRIBUTED / REMOTE 0
		destination = GetDistHashLocation(key);
		// Action senden.
		MPI_Ssend(&action, 1, MPI_INT, destination, TAG_ACTION, thread_comm);
		PrintColored("Request to insert (%d, %s) into Process' %d HashMap for Process %d sent.\n", key, value.c_str(), destination, rank);
		// Key senden.
		MPI_Ssend(&key, 1, MPI_INT, destination, TAG_KEY, thread_comm);
		// Value Größe ermitteln.
		valueSize = value.size() + 1;
		// Value in char-Array zwischen speichen.
		valueArray = new char[valueSize];
		value.copy(valueArray, valueSize);
		valueArray[valueSize - 1] = '\0';
		// Sende Länge des Values.
		MPI_Ssend(&valueSize, 1, MPI_INT, destination, TAG_VALUE_SIZE, thread_comm);
		// Sende Value.
		MPI_Ssend(valueArray, valueSize, MPI_CHAR, destination, TAG_VALUE, thread_comm);
	} else if (mode == MODE_LOCAL) {
		// LOCAL
		this->InsertEntry(key, value);
		PrintColored("Inserted entry (%d, %s).\n", key, value.c_str());
	}
}

/// <summary>
/// Holt den Eintrag aus der HashMap des zuständigen Prozesses.
/// </summary>
/// <param name="key">Schlüssel des Eintrags</param>
/// <returns>Wert des Eintrags</returns>
string MPIHash::GetDistEntry(int key) {
	string value;
	int destination;
	int valueSize;
	char* valueArray;
	int action = ACTION_GET;
	if (mode == MODE_DISTRIBUTED || (mode == MODE_REMOTE && rank == 0)) {
		// DISTRIBUTED / REMOTE 0
		destination = GetDistHashLocation(key);
		// Action senden.
		MPI_Ssend(&action, 1, MPI_INT, destination, TAG_ACTION, thread_comm);
		PrintColored("Request to get entry (%d, ?) in Process' %d HashMap for Process %d sent.\n", key, destination, rank);
		// Key senden.
		MPI_Ssend(&key, 1, MPI_INT, destination, TAG_KEY, thread_comm);
		// Länge des Values herausfinden.
		MPI_Recv(&valueSize, 1, MPI_INT, destination, TAG_VALUE_SIZE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		// Bei leerem Eintrag nichts weiter empfangen, sonst schon.
		if (valueSize < 0) {
			value = "N/A";
		} else {
			// Puffer bereitstellen.
			valueArray = new char[valueSize];
			// Value empfangen.
			MPI_Recv(valueArray, valueSize, MPI_CHAR, destination, TAG_VALUE, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			// Value als String speichern.
			value = valueArray;
		}
	} else if (mode == MODE_LOCAL) {
		// LOCAL
		value = this->GetEntry(key);
		PrintColored("Got entry (%d, %s).\n", key, value.c_str());
	}
	return value;
}

/// <summary>
/// Löscht den EIntrag aus der HashMap des zuständigen Prozesses.
/// </summary>
/// <param name="key">Schlüssel des Eintrags</param>
/// <returns>Erfolg des Löschvorgangs</returns>
bool MPIHash::DeleteDistEntry(int key) {
	bool deleted = false;
	int destination;
	int feedback;
	int action = ACTION_DEL;
	if (mode == MODE_DISTRIBUTED || (mode == MODE_REMOTE && rank == 0)) {
		// DISTRIBUTED / REMOTE 0
		destination = GetDistHashLocation(key);
		// Action senden.
		MPI_Ssend(&action, 1, MPI_INT, destination, TAG_ACTION, thread_comm);
		PrintColored("Request to delete entry (%d, ?) in Process' %d HashMap for Process %d sent.\n", key, destination, rank);
		// Key senden.
		MPI_Ssend(&key, 1, MPI_INT, destination, TAG_KEY, thread_comm);
		// Feedback bekommen.
		MPI_Recv(&feedback, 1, MPI_INT, destination, TAG_FEEDBACK, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if (feedback == 1)
			deleted = true;
	} else if (mode == MODE_LOCAL) {
		// LOCAL
		deleted = this->DeleteEntry(key);
		if (deleted)
			PrintColored("Deleted entry (%d, ?).\n", key);
		else
			PrintColored("Could not delete entry (%d, ?).\n", key);
	}
	return deleted;
}