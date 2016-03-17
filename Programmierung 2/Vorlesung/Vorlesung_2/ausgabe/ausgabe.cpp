#include <iostream>  // ausgabe.cpp
#include <iomanip>

using namespace std;

auto main() -> void {

	auto d = 123.456;
	auto x = 4711;

	cout<<setw(15)<<"decimal x = "
		<<setw(10)<<setfill('.')<<dec<<showpos<<x<<'\n'
		<<setfill(' ')<<setw(15)<<"hexadec x = "
		<<setfill('.')<<setw(10)<<hex<<showbase<<x<<'\n'
		<<setfill(' ')<<setw(15)<<"octal x = "
		<<setfill('.')<<setw(10)<<oct<<showbase<<x<<'\n'
		<<setfill(' ')<<setw(15)<<"double d = "
		<<setprecision(4)<<setw(10)<<setfill('#')<<d
		<<endl;

	cout<<setfill(' ')<<setw(15)<<"double d = ";
    cout.setf(ios::fixed);  // zum Test herauskommentieren
//	cout.flags(ios::fixed); // alternativ
	cout<<fixed<<setprecision(4)<<setw(10)
		<<setfill('#')<<d
		<<endl;
	cin.get();
}

/*
   decimal x = .....+4711
   hexadec x = ....0x1267
     octal x = ....011147
    double d = ####+123.5
    double d = #+123.4560
*/
