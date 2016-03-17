#include <iostream>   // test.cpp
using namespace std;

class test {
public:
	static void change(int **x){
		delete *x;
		*x = nullptr;
		*x = new int(5);
	}
};

void main(){
	
	int *x = new int(4);


	// int k(4), *pk(&k);
	// test::change(&pk);

	test::change(&x);

	cout<<"*x = "<<*x<<endl;
	cin.get();
}

// *x = 5