#include <iostream>   //higher.cpp

using namespace std;

int &higher(int &i){
	i++;
	int k = i; // Warning 1	warning C4172: returning address of local variable or temporary

	return k;  // korrekt: return i;
}

void main(){ 
	int n(5);

	higher(n)=++n,      // (++n)++,

	cout<<"higher(n) = "
		<<higher(n)
		<<'\n',

	cout<<"n         = "<<n<<endl,
	cin.get();
}

/*
higher(n) = 8
n         = 8
*/