#include "../MyLibs.h"

int main(int argc, char *argv[]) {
	string testString = "Brunhilde";
	string testString2 = "Frank (1880: ~2.738000%)";

	int numProcesses, rank;
	MPI_Status status;
	int dest, source, rc, count, tag = 1;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	const int lentag = 0;
	const int datatag = 1;
	if (rank == 0) {
		string send = testString;

		// Send length, then data
		int len = send.length() +1;
		MPI_Ssend(&len, 1, MPI_INT, 1, lentag, MPI_COMM_WORLD);

		char* send_data = new char[len];
		send.copy(send_data, len);
		send_data[len-1] = '\0';
		//send_data[len+1] = '\0';
		printf("Rank %d sending %s (len: %d).\n", rank, send_data, len);


		//std::cout << "Rank " << rank << " sends: " << send << std::endl;
		MPI_Ssend(send_data, len, MPI_CHAR, 1, datatag, MPI_COMM_WORLD);

	} else if (rank == 1) {

		int len;
		MPI_Recv(&len, 1, MPI_INT, 0, lentag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		////allocate the array
		//int** arr = new int*[row];
		//for (int i = 0; i < row; i++)
		//	arr[i] = new int[col];

		//// use the array

		////deallocate the array
		//for (int i = 0; i < row; i++)
		//	delete[] arr[i];
		//delete[] arr;

		char* recv_data;

		recv_data = new char[len];
		
		//char recv_data[len];
		MPI_Recv(recv_data, len, MPI_CHAR, 0, datatag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		//recv_data[len] = '\0';
		

		string recv = recv_data;

		usleep(200);
		printf("Rank %d got %s (len: %d).\n", rank, recv.c_str(), len);
		//std::cout << "Rank " << rank << " got: " << recv << std::endl;
	}

	MPI_Finalize();
}