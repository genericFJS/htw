#include "mpi.h"
#include <pthread.h>
#include <unistd.h>

#define TAG_EXIT 0
#define TAG_CONTENT 1

int providedThreads, numProcesses, rank;

void* testThread(void* ptr) {
	int buf;
	MPI_Comm thread_comm = *(MPI_Comm*)ptr;
	MPI_Status status;
	while (1) {
		printf("\t\tWaiting for message on thread in %d.\n", rank);
		MPI_Recv(&buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, thread_comm, &status);
		if (status.MPI_TAG == TAG_EXIT)
			break;
		printf("\t\t%d: Received %d from %d.\n", rank, buf, status.MPI_SOURCE);
	}
	printf("\t\tLeaving thread %d.\n", rank);
	/*
		Idee: Threads potentiell gemeinsam beenden? MPI Barrier funktioniert nicht (s.o.)
	*/
	//MPI_Barrier(thread_comm);
	pthread_exit((void *)NULL);
}

int main(int argc, char *argv[]) {
	/*
		Kompiliern über bspw.
			mpic++ ThreadComm.cpp -o threadComm -lpthread
		Ausführen über (braucht machinefile; getestet mit machinefile die alle isys-Rechner enthält):
			mpiexec -f machinefile -n 3 ./threadComm
	*/
	int data = 42, recipient;
	pthread_t thread;
	MPI_Comm thread_comm, main_comm;
	MPI_Status status;

	// MPI mit Thread initialisieren.
	MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &providedThreads);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (providedThreads < MPI_THREAD_MULTIPLE)
		MPI_Abort(MPI_COMM_WORLD, 0);

	// Für jeden Prozess Thread mit gesondertem Communicator erstellen.
	MPI_Comm_dup(MPI_COMM_WORLD, &thread_comm);
	/*
		Thread erstellen. Wird kein Thread erstellt (und die entsprechenden Send/Receive auskommentiert), so funktioniert MPI Barrier usw.
	*/
	pthread_create(&thread, NULL, testThread, &thread_comm);

	/* 
		MPI Barrier hier, um sicher zu stellen, dass alle Threads gestartet sind. MPI_Barrier funktioniert nicht!
	*/
	MPI_Barrier(MPI_COMM_WORLD);

	/* 
		Code funktioniert (bei n=3) nicht, wenn es vom Prozess 2 ausgeführt wird (der an 1 sendet). Warum? (kommentiert man if... ein, so geht es entsprechend)
	*/
	//if (rank == 0) {
		recipient = (rank + 1)% numProcesses;
		printf("Sending something from %d to %d.\n", rank, recipient);
		//MPI_Ssend(&data, 1, MPI_INT, recipient, TAG_CONTENT, MPI_COMM_WORLD);
		MPI_Ssend(&data, 1, MPI_INT, recipient, TAG_CONTENT, thread_comm);
	//}

	/*
		MPI Barrier hier, damit kein Prozess/Thread beendet wird, bevor nicht alle ihre Aufgaben abgearbeitet haben. Geht nicht (s.o.)
	*/
	//sleep(2);
	MPI_Barrier(MPI_COMM_WORLD);
	printf("Process %d waiting to exit.\n", rank);
	printf("Process %d telling thread to leave.\n", rank);
	MPI_Ssend(MPI_BOTTOM, 0, MPI_INT, rank, TAG_EXIT, thread_comm);
	printf("Process %d waiting to for all threads to be closed.\n", rank);
	/*
		MPI Barrier hier, damit alle Threads beendet sind, bevor Finalized wird. Geht nicht (s.o.)
	*/
	//MPI_Barrier(main_comm);

	MPI_Finalize();
	return 0;
}