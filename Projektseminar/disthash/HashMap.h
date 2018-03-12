#pragma once
#include "LinkedHashEntry.h"
#include "MyLibs.h"

class HashMap {
private:
	LinkedHashEntry **table;
	int tableSize;
public:
	HashMap(int tableSize);
	~HashMap();
	int GetHashKey(int key);
	string Get(int key);
	void Insert(int key, string value);
	bool Delete(int key);
};