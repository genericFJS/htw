#include <iostream>  // format.cpp
#include <iomanip>

using namespace std;

auto main() -> void {
//----------------------------------------------
	/*
    cout.width(20);
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(3);
    cout.fill('*');
    cout<<123.4<<endl;
	*/
//----------------------------------------------
// aequivalent:
	cout<<setw(20)<<fixed<<setprecision(3)
		<<setfill('*')<<123.4<<endl;
//----------------------------------------------
	/*
    cout.width(20);
    cout.setf(ios::scientific, ios::floatfield);
    cout.precision(8);
    cout.fill('*');
    cout<<123.456789<<endl;
	*/
//----------------------------------------------
// aequivalent:
	cout<<setw(20)<<scientific<<setprecision(8)
		<<setfill('*')<<123.456789<<endl;
//----------------------------------------------
	cin.get();
}

/*
*************123.400
*****1.23456789e+002
*/