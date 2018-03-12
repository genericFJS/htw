/// <summary>
/// DistHash ist die Hauptanwendung. Hier werden die MPI-Verbindungen, die Threads und die MPI-HashMap initialisiert.
/// </summary>
#include "LinkedHashEntry.h"
#include "HashMap.h"
#include "MPIHash.h"
#include "MPIHashThread.h"
#include "MyLibs.h"

int providedThreads = 0, numProcesses = 1, rank = 0;
pthread_t thread;
MPI_Comm thread_comm;
MPI_Status status;
MPIHash* mpiHash;
int hashMapSize = HASHMAP_SIZE;
int randomTests = RANDOM_TESTS;

bool verbose = false;
// 0: local HashMap, 1: remote HashMap, 2: distributed HashMap 
int mode = MODE_DISTRIBUTED;
bool executeTests = false;
HashMap* hashMap = new HashMap(hashMapSize);
double startTime, endTime, totalTime;
// Ergebnisse:
double testResults[12];

// Vorbereitung vom Zufall
std::random_device seeder;
std::mt19937 engine(seeder());

/// <summary>
/// Gibt einen Text nur einmalig (im Prozess 0) aus.
/// </summary>
/// <param name="text">Auszugebender Text</param>
/// <param name="">Parameter der printf-Funktion</param>
void PrintOnce(const char * text, ...) {
	if (rank == 0) {
		va_list args;
		va_start(args, text);
		vprintf(text, args);
		va_end(args);
	}
}

/// <summary>
/// Beginnt einen Messvorgang.
/// </summary>
void MeasurementStart() {
	startTime = MPI_Wtime();
}

/// <summary>
/// Beendet einen Messvorgang und speichert die Zeit zwischen.
/// </summary>
void MeasurementEnd() {
	endTime = MPI_Wtime();
	totalTime = endTime - startTime;
}

/// <summary>
/// Beendet einen Messvorgang und speichert die Zeit in dem Array der Messergebnisse.
/// </summary>
/// <param name="i">Position im Array der Messergebnisse</param>
void MeasurementEnd(int i) {
	MeasurementEnd();
	testResults[i] = totalTime;
}

/// <summary>
/// Erzeugt eine zufällige Zahl zwischen zwei Werten. Quelle: https://stackoverflow.com/a/11766794/8805428
/// </summary>
/// <param name="min">Kleinste mögliche Zahl</param>
/// <param name="max">Größte mögliche Zahl</param>
/// <returns>Zufällige Zahl zwischen min und max.</returns>
int RandBetween(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	// Nächste zufällige:
	engine.operator()();
	return dist(engine);
}

/// <summary>
/// Erzeugt eine zufällige Zeichenkette der gegebenen Länge. Quelle: https://stackoverflow.com/a/12468109/8805428
/// </summary>
/// <param name="length">Länge des zufälligen Strings</param>
/// <returns>Zufälligen String</returns>
std::string RandString(size_t length) {
	auto randchar = []() -> char {
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}

/// <summary>
/// Beendet das Programm, indem alle Threads beendet werden.
/// </summary>
/// <returns>Status beim Beenden</returns>
int ExitApp() {
	// Warte, bis alle Prozesse bereit zum Beenden sind.
	MPI_Barrier(MPI_COMM_WORLD);
	// Threads Beenden-Signal schicken.
	MPI_Ssend(MPI_BOTTOM, 0, MPI_INT, rank, TAG_EXIT, thread_comm);
	// Warten, bis alle Prozesse ihre Threads beendet haben.
	pthread_join(thread, NULL);
	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();
	PrintOnce("==================================\nThank you for using DistHash by FJS.\n");
	return 0;
}

int main(int argc, char *argv[]) {
	// MPI mit Thread initialisieren.
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &providedThreads);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (providedThreads < MPI_THREAD_MULTIPLE)
		MPI_Abort(MPI_COMM_WORLD, 0);

	// Für jeden Prozess Thread mit gesondertem Communicator erstellen.
	MPI_Comm_dup(MPI_COMM_WORLD, &thread_comm);
	pthread_create(&thread, NULL, MPIHashThread, &thread_comm);

	// ================================================================
	//                Vorbereitung/Optionen einlesen
	// ================================================================

	int opt;
	// Fehler selber abfangen (return '?'): 
	opterr = 0;

	// Optionen Verarbeiten:
	while ((opt = getopt(argc, argv, "vlrdth:")) != -1) {
		switch (opt) {
		case 'v':
			// (v)erbose: Zeige Vorgänge an
			verbose = true;
			break;
		case 'l':
			// (l)ocal mode: HashMap wird lokal erstellt und verwaltet.
			mode = MODE_LOCAL;
			if (numProcesses > 1) {
				PrintOnce("LOCAL tests require n=1 process (has %d).\n", numProcesses);
				return ExitApp();
			}
			break;
		case 'r':
			// (r)emote mode: HashMap wird von entferntem Prozess 1 verwaltet, Prozess 0 macht nur Anfragen. 
			mode = MODE_REMOTE;
			if (numProcesses > 2) {
				PrintOnce("REMOTE tests require n=2 processes (has %d).\n", numProcesses);
				return ExitApp();
			}
			break;
		case 'd':
			// (d)istributed mode: HashMap wird von allen Prozessen verwaltet, jeder Prozess kann Anfragen ausführen.
			mode = MODE_DISTRIBUTED;
			break;
		case 't':
			// (t)est: Tests werden ausgeführt.
			executeTests = true;
			break;
		case 'h':
			// (h)ashMap size: Größe der HashMap (pro Prozess)
			if (optarg) {
				hashMapSize = atoi(optarg);
			}
			break;
		case '?':
			PrintOnce("Unknown option: '%c'!\n", char(optopt));
			break;
		}
	}

	// Gebe Informationen zu den festgelegten Einstellungen.
	string modeString = "";
	switch (mode) {
	case MODE_LOCAL:
		modeString = "LOCAL";
		break;
	case MODE_REMOTE:
		modeString = "REMOTE";
		break;
	case MODE_DISTRIBUTED:
		modeString = "DISTRIBUTED";
		break;
	}

	PrintOnce("==================================\nWelcome to DistHash by FJS.\n");
	PrintOnce("Mode: %s\t Processes: %d  HashMap size: %d\n==================================\n", modeString.c_str(), numProcesses, hashMapSize);

	// Die (MPI-)HashMap erstellen.
	mpiHash = new MPIHash(hashMapSize);

	// ================================================================
	//                   Datei zwischenspeichern
	// ================================================================

	// Einlesen der Test-Datei in Zwischenpseicher
	std::ifstream inputFile("baby-names.csv");

	// Zähle die Anzahl der Zeilen
	inputFile.unsetf(std::ios_base::skipws);
	unsigned dataEntrys = std::count(std::istream_iterator<char>(inputFile), std::istream_iterator<char>(), '\n');

	// Setze filepointer zurück
	inputFile.clear();
	inputFile.seekg(0, std::ios::beg);

	// Erstelle Zwischenspeicher
	int processEntrys = (dataEntrys - 1) / numProcesses;
	//string inputData[processEntrys];
	string* inputData = new string[processEntrys];

	string entry;
	int line = -1;
	while (inputFile.good()) {
		line++;
		// Lese nächste Zeile
		std::getline(inputFile, entry, '\n');
		// Überspringe erste Zeile (Spaltenüberschriften)
		if (line <= 0)
			continue;
		// Überspringe nicht relevante Zeilen
		if (line < processEntrys*(rank)+1)
			continue;
		// Stoppe, wenn alle relevanten Zeilen bearbeitet
		if (line > processEntrys*(rank + 1))
			break;
		// Speicher Zeile in Array
		string entryValues[4];
		size_t pos = 0;
		int index = 0;
		std::string token;
		while ((pos = entry.find(",")) != std::string::npos) {
			entryValues[index] = entry.substr(0, pos);
			entry.erase(0, pos + 1);
			index++;
		}
		// Speicher Eintrag in Zwischenspeicher
		string data = entryValues[1].substr(1, (entryValues[1]).size() - 2) + " [" + entryValues[0] + ": ~" + std::to_string(std::stod(entryValues[2]) * 100) + "%]";

		inputData[(line - 1) % processEntrys] = data;
	}
	// Zufällig Reihenfolge festlegen (für Messungen später):
	std::vector<int> randomOrder(processEntrys);
	for (int i = 0; i < processEntrys; i++) {
		randomOrder[i] = i;
	}
	std::iota(std::begin(randomOrder), std::end(randomOrder), 0);
	std::random_shuffle(std::begin(randomOrder), std::end(randomOrder));

	// Warte, bis alle Prozesse vorbereitet sind und ihren Teil in den Zwischenspeicher geladen haben.
	MPI_Barrier(MPI_COMM_WORLD);

	// ================================================================
	//                            Tests
	// ================================================================
	srand(time(NULL));
	int id;
	string value;

	// Tests ggf. überspringen.
	if (!executeTests) {
		PrintOnce("Inserting test data set. Please wait.\n");
		// Trage alle Einträge aus Zwischenspeicher ein:
		for (int i = 0; i < processEntrys; i++) {
			mpiHash->InsertDistEntry(rank*processEntrys + i, inputData[i]);
		}
		goto userInput;
	}
	// ============= Beginne Tests ================

	// ============= Leere HashMap, nicht existierende Einträge: DELETE ================
	PrintOnce("Delete not existing entrys in empty HashMap (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < processEntrys; i++) {
		mpiHash->DeleteDistEntry(rank*processEntrys + i);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_DEL_EMPTY_NONEXIST);
	PrintOnce("Not existing entrys deleted in empty HashMap in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Leere HashMap, nicht existierende Einträge: GET ================
	PrintOnce("Get not existing entrys in empty HashMap (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < processEntrys; i++) {
		mpiHash->GetDistEntry(rank*processEntrys + i);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_GET_EMPTY_NONEXIST);
	PrintOnce("Not existing entrys got in empty HashMap in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Leere HashMap, nicht existierende Einträge: INSERT ================
	PrintOnce("Inserting cached data (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	// Trage alle Einträge aus Zwischenspeicher ein:
	for (int i = 0; i < processEntrys; i++) {
		mpiHash->InsertDistEntry(rank*processEntrys + i, inputData[i]);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_INS_EMPTY);
	PrintOnce("Cached data inserted in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Existierende Einträge: INSERT ================
	PrintOnce("Rewriting cached data (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	// Trage alle Einträge aus Zwischenspeicher ein:
	for (int i = 0; i < processEntrys; i++) {
		mpiHash->InsertDistEntry(rank*processEntrys + i, inputData[i]);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_INS_EXIST);
	PrintOnce("Cached data rewritten in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Existierende Einträge, zufällig: GET ================
	PrintOnce("Get random existing entrys (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < processEntrys; i++) {
		id = RandBetween(0, (processEntrys*numProcesses) - 1);
		mpiHash->GetDistEntry(id);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_GET_EXIST_RANDOM);
	PrintOnce("Random existing entrys got in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Nicht existierende Einträge, zufällig: GET ================
	PrintOnce("Get random not existing entrys (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < processEntrys; i++) {
		id = RandBetween((processEntrys*numProcesses), (processEntrys*numProcesses) + numProcesses);
		mpiHash->GetDistEntry(id);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_GET_NONEXIST_RANDOM);
	PrintOnce("Random not existing entrys got in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Existierende Einträge, zufällig: INSERT ================
	PrintOnce("Rewrite random data in cached data (%d actions).\n", randomTests);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < (randomTests / numProcesses); i++) {
		id = RandBetween(0, (processEntrys*numProcesses) - 1);
		value = RandString(RandBetween(RANDOM_MIN_STRING_LENGTH, RANDOM_MAX_STRING_LENGTH));
		mpiHash->InsertDistEntry(id, value);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_INS_EXIST_RANDOM);
	PrintOnce("Random data rewritten in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Nicht existierende Einträge: DELETE ================
	PrintOnce("\"Delete\" not existing entrys (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < processEntrys; i++) {
		mpiHash->DeleteDistEntry(2 * rank*processEntrys + i);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_DEL_NONEXIST);
	PrintOnce("Not existing entrys \"deleted\" in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Existierende Einträge: DELETE ================
	PrintOnce("Delete all existing entrys (%d actions).\n", processEntrys*numProcesses);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < processEntrys; i++) {
		mpiHash->DeleteDistEntry(randomOrder[i]);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_DEL_EXIST);
	PrintOnce("All existing entrys deleted in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Größtenteils nicht existierende Einträge, zufällig: INSERT/GET/DELETE ================
	PrintOnce("Process random data (%d actions -- Insert: %d%%   Get: %d%%   Delete: %d%%).\n", randomTests, RANDOM_INS_PERCENT, RANDOM_GET_PERCENT, RANDOM_DEL_PERCENT);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < (randomTests / numProcesses); i++) {
		int action = RandBetween(1, 100);
		id = RandBetween(0, std::numeric_limits<std::int32_t>::max());
		if (action <= RANDOM_GET_PERCENT) {
			// Frage zufälligen Eintrag ab.
			mpiHash->GetDistEntry(id);
		} else if (action <= RANDOM_DEL_PERCENT + RANDOM_GET_PERCENT) {
			// Lösche zufälligen Eintrag.
			mpiHash->DeleteDistEntry(id);
		} else {
			// Füge zufälligen Eintrag ein.
			value = RandString(RandBetween(RANDOM_MIN_STRING_LENGTH, RANDOM_MAX_STRING_LENGTH));
			mpiHash->InsertDistEntry(id, value);
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_ACT_MOSTLYNONEXIST_RANDOM);
	PrintOnce("Random data processed in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Größtenteils nicht existierende Einträge, zufällig: INSERT ================
	PrintOnce("Insert random data (%d actions).\n", randomTests);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < (randomTests / numProcesses); i++) {
		id = RandBetween(0, std::numeric_limits<std::int32_t>::max());
		value = RandString(RandBetween(RANDOM_MIN_STRING_LENGTH, RANDOM_MAX_STRING_LENGTH));
		mpiHash->InsertDistEntry(id, value);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_INS_MOSTLYNONEXIST_RANDOM);
	PrintOnce("Random data inserted in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Gecachte Werte für spätere Tests erneut einfügen ================
	PrintOnce("Reinserting cached data...\n");
	for (int i = 0; i < processEntrys; i++) {
		mpiHash->InsertDistEntry(rank*processEntrys + i, inputData[i]);
	}
	// ============= Größtenteils existierende Einträge, zufällig: INSERT/GET/DELETE  ================
	PrintOnce("Process random actions on inserted data (%d actions -- Insert: %d%%   Get: %d%%   Delete: %d%%).\n", randomTests, RANDOM_INS_PERCENT, RANDOM_GET_PERCENT, RANDOM_DEL_PERCENT);
	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementStart();

	for (int i = 0; i < (randomTests / numProcesses); i++) {
		int action = RandBetween(1, 100);
		id = RandBetween(0, (processEntrys*numProcesses) - 1);
		if (action <= RANDOM_GET_PERCENT) {
			// Frage zufälligen Eintrag ab.
			mpiHash->GetDistEntry(id);
		} else if (action <= RANDOM_DEL_PERCENT + RANDOM_GET_PERCENT) {
			// Lösche zufälligen Eintrag.
			mpiHash->DeleteDistEntry(id);
		} else {
			// Füge zufälligen Eintrag ein.
			value = RandString(RandBetween(RANDOM_MIN_STRING_LENGTH, RANDOM_MAX_STRING_LENGTH));
			mpiHash->InsertDistEntry(id, value);
		}
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MeasurementEnd(STAT_ACT_MOSTLYEXIST_RANDOM);
	PrintOnce("Random data processed in   \x1b[97m%f\x1b[0m   seconds.\n", totalTime);
	// ============= Tests fertig ================
	PrintOnce(
		"------------------------------------------------------\n"
		"Insert  empty                               %2.6fs\n"
		"Insert         mostly not existing  random  %2.6fs\n"
		"Insert                                      %2.6fs\n"
		"Insert                              random  %2.6fs\n"
		"Get                                 random  %2.6fs\n"
		"Get                   not existing  random  %2.6fs\n"
		"Get     empty         not existing          %2.6fs\n"
		"Delete                                      %2.6fs\n"
		"Delete                not existing          %2.6fs\n"
		"Delete  empty         not existing          %2.6fs\n"
		"Actions            mostly existing  random  %2.6fs\n"
		"Actions        mostly not existing  random  %2.6fs\n"
		"------------------------------------------------------\n",
		testResults[STAT_INS_EMPTY],
		testResults[STAT_INS_MOSTLYNONEXIST_RANDOM],
		testResults[STAT_INS_EXIST],
		testResults[STAT_INS_EXIST_RANDOM],
		testResults[STAT_GET_EXIST_RANDOM],
		testResults[STAT_GET_NONEXIST_RANDOM],
		testResults[STAT_GET_EMPTY_NONEXIST],
		testResults[STAT_DEL_EXIST],
		testResults[STAT_DEL_NONEXIST],
		testResults[STAT_DEL_EMPTY_NONEXIST],
		testResults[STAT_ACT_MOSTLYEXIST_RANDOM],
		testResults[STAT_ACT_MOSTLYNONEXIST_RANDOM]
	);
	// ============= Testdaten in Datei schreiben ================
	if (rank == 0) {
		std::string statFilename = "../tests/" + modeString + "-" + std::to_string(numProcesses) + "_" + std::to_string(hashMapSize) + ".csv";
		std::fstream statFile(statFilename, std::fstream::app);
		int statFileSize = statFile.tellg();
		if (statFileSize == 0) {
			statFile <<
				"Insert  empty                               ;"
				"Insert         mostly not existing  random  ;"
				"Insert                                      ;"
				"Insert                              random  ;"
				"Get                                 random  ;"
				"Get                   not existing  random  ;"
				"Get     empty         not existing          ;"
				"Delete                                      ;"
				"Delete                not existing          ;"
				"Delete  empty         not existing          ;"
				"Actions            mostly existing  random  ;"
				"Actions        mostly not existing  random  \n";
		}
		statFile <<
			testResults[STAT_INS_EMPTY] << ";" <<
			testResults[STAT_INS_MOSTLYNONEXIST_RANDOM] << ";" <<
			testResults[STAT_INS_EXIST] << ";" <<
			testResults[STAT_INS_EXIST_RANDOM] << ";" <<
			testResults[STAT_GET_EXIST_RANDOM] << ";" <<
			testResults[STAT_GET_NONEXIST_RANDOM] << ";" <<
			testResults[STAT_GET_EMPTY_NONEXIST] << ";" <<
			testResults[STAT_DEL_EXIST] << ";" <<
			testResults[STAT_DEL_NONEXIST] << ";" <<
			testResults[STAT_DEL_EMPTY_NONEXIST] << ";" <<
			testResults[STAT_ACT_MOSTLYEXIST_RANDOM] << ";" <<
			testResults[STAT_ACT_MOSTLYNONEXIST_RANDOM] << "\n";
		statFile.close();
	}

	// ================================================================
	//                      Benutzereingabe
	// ================================================================
userInput:
	MPI_Barrier(MPI_COMM_WORLD);
	// Ab jetzt (auf jeden Fall) detaillierte Rückmeldung.
	verbose = true;
	// Nur Prozess 0 hat Nutzereingabe für weiter Bedienung.
	if (rank == 0) {
		usleep(200);
		string helpText = "Commands: 'get ID', 'ins ID string', 'del ID', 'h(elp), 'q(uit)''\n";
		if (executeTests) {
			// Bei Tests Programm sofort beenden.
			for (int i = rank; i < numProcesses - 1; i++) {
				MPI_Ssend(MPI_BOTTOM, 0, MPI_INT, i + 1, TAG_EXIT, MPI_COMM_WORLD);
			}
		} else {
			printf("==================================\n");
			printf(helpText.c_str());
			// Sonst Nutzereingabe verarbeiten.
			for (std::string line; printf("   Command: "), std::getline(std::cin, line); usleep(200)) {
				if (line == "quit" || line == "q") {
					// Sende Beenden-Signal an alle Prozesse.
					for (int i = rank; i < numProcesses - 1; i++) {
						MPI_Ssend(MPI_BOTTOM, 0, MPI_INT, i + 1, TAG_EXIT, MPI_COMM_WORLD);
					}
					break;
				} else if (line == "help" || line == "h") {
					// Gebe Hilfstext (erneut) aus.
					printf(helpText.c_str());
				} else {
					// Prüfe auf Aktion.
					int action;
					int id;
					size_t pos = 0;
					if ((pos = line.find(" ")) != std::string::npos) {
						string actionString = line.substr(0, pos);
						// Aktion herausfinden.
						if (actionString == "ins") {
							action = ACTION_INS;
						} else if (actionString == "get") {
							action = ACTION_GET;
						} else if (actionString == "del") {
							action = ACTION_DEL;
						} else {
							printf("Unkown command '%s'.\n", actionString.c_str());
							continue;
						}
						line.erase(0, pos + 1);
						// ID herausfinden.
						if ((pos = line.find(" ")) != std::string::npos) {
							id = std::stoi(line.substr(0, pos));
							if (action == ACTION_INS) {
								// Insert mit ID und Rest der Eingabe ausführen.
								line.erase(0, pos + 1);
								mpiHash->InsertDistEntry(id, line);
							} else {
								printf("Command '%s' only has one argument.\n", actionString.c_str());
							}
						} else {
							id = std::stoi(line);
							if (action == ACTION_GET) {
								// Get mit ID ausführen.
								mpiHash->GetDistEntry(id);
							} else if (action == ACTION_DEL) {
								// Delete mit ID ausführen.
								mpiHash->DeleteDistEntry(id);
							} else {
								printf("Too few arguments for command '%s'.\n", actionString.c_str());
							}
						}
					} else {
						printf("'%s' is no command.\n", line.c_str());
					}
				}
			}
		}
	} else {
		// Alle anderen Prozesse warten auf das Beenden.
		int buf;
		MPI_Recv(&buf, 1, MPI_INT, 0, TAG_EXIT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	return ExitApp();
}