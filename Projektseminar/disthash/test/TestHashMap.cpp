#include "../MyLibs.h"
#include "../HashMap.h"

int main(int argc, char *argv[]) {
	HashMap* hashMap = new HashMap(HASHMAP_SIZE);

	int key1 = 42;
	int key2 = HASHMAP_SIZE + 42;
	int key3 = 21;

	hashMap->Insert(key1, "Hans");
	hashMap->Insert(key2, "Brunhilde");
	hashMap->Insert(key3, "Franz");

	std::cout << "Entry " << key1 << " contains " << hashMap->Get(key1) << "." << std::endl;
	std::cout << "Entry " << key2 << " contains " << hashMap->Get(key2) << "." << std::endl;
	std::cout << "Entry " << key3 << " contains " << hashMap->Get(key3) << "." << std::endl;
}