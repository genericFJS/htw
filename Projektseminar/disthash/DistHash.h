#pragma once
#include "MPIHash.h"
#include "TestHashMap.h"
#include "TestMPIComm.h"
#include "mpi.h"
#include <locale>
#include <clocale>
#include <iostream>


class DistHash {
private:
	void TestTests(int argc, char* argv[]);
public:
	static int numtasks, rank, dest, source, rc, count, tag;
	static MPI_Status Stat;
	DistHash(int argc, char* argv[]);
};