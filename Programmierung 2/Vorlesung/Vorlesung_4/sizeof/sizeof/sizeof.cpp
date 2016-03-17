#include <iostream>      // sizeof.cpp
using namespace std;

auto main() -> void {
    cout<<"Test von sizeof fuer Zeichenketten:\n\n";

    char n[]="1234567890"; 
	cout<<"sizeof(n) = "<<sizeof(n)<<'\n';  // 11

    char k[20]="1234567890"; 
	cout<<"sizeof(k) = "<<sizeof(k)<<'\n';  // 20

    char *z="1234567890"; 
	cout<<"sizeof(z) = "<<sizeof(z)<<'\n';  // 4
	cout<<"sizeof(*z)= "<<sizeof(*z)<<'\n'; // 1

	cin.get();
}

/*
Test von sizeof fuer Zeichenketten:
sizeof(n) = 11
sizeof(k) = 20
sizeof(z) = 4
sizeof(*z)= 1
*/

