#pragma once
#include "HashMap.h"
#include "MyLibs.h"

class MPIHash {
private:
	HashMap* hashMap;
public:
	//MPIHash();
	MPIHash(int hashmapSize);
	~MPIHash();
	int GetDistHashLocation(int key);
	void InsertEntry(int key, string value);
	void InsertDistEntry(int key, string value);
	string GetEntry(int key);
	string GetDistEntry(int key);
	bool DeleteEntry(int key);
	bool DeleteDistEntry(int key);
};

