#include <iostream>			// Les2_3.cpp
#include <iomanip>
using namespace std;

auto main() -> void
{
 int Wert1(0), Wert2(0), Wert3(0), Wert4(0);
 cout<<"Vier int-Zahlen eingeben:\n";
 cin>>Wert1>>Wert2>>Wert3>>Wert4;
 cin.clear(); cin.ignore(INT_MAX, '\n');
 cout<<"Zahlen: "<<Wert1<<", "<<Wert2
	 <<", "<<Wert3<<", "<<Wert4<<endl;
 cin.get();
}
/*
Vier int-Zahlen eingeben:
1
2
3
4
Zahlen: 1, 2, 3, 4
*/
/*
Vier int-Zahlen eingeben:
O
Zahlen: 0, 0, 0, 0
*/