/* Hinweise: 
semget() - Erzeugen eines Semaphore-Sets (und Zugriff darauf erlangen)
semget(key, nsems, semflg)
key: Schlüssel (einfacher: unbenannt => IPC_PRIVATE)
nsems: Anzahl der Semaphore
semflg: IPC_CREAT (um Set anzulegen) | Zugriffsrechte => IPC_CREAT|0600

semop() - P() und V()
semop(semid, *sops, nsops)
semid: Rückgabe von semget()
*sops: (struct muss selbst erstellt werden!)
	sem_num: Nummer des semaphors im Set
	sem_op: -1 -> P()  +1 -> V()
	sem_flg: 0 (vorerst)
nsops: Anzahl der Felder des structs (idR 1)

semctl() - „Management“ des Semaphore-Sets z.B. Initialisieren, Löschen, Wertabfrage (müssen beim Programmende explizit zerstört werden!)
semctl(semid, semnum, cmd, ...)
	semid: die id des Semaphors sets
	semnum: nummer des semaphors im set (bei nur einer: 0)
	cmd: auszuführendes Kommando
		löschen:	
		initialisieren: SETVAL
		
Vorgehen:
Semaphor initialisieren:
1. union semnum definieren
2. Variable vom Typ union semnum definieren
3. In Feld val des unions (semnumvar.val=...) Initialisierungswert eintragen
4. Syscall: ret=semctl(id, nr, SETVAL, &semnumvar)
Löschen des Semaphorsets:
ret=semtcl(id, 0, IPC_RMID)
*/