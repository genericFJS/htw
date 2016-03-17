#include <iostream> //bar1.cpp

using namespace std;

auto bar(double i) -> void { 
	cout<<"Double-Wert: "<<i<<endl; 
}

auto bar(long i) -> void { 
	cout<<"Long-Wert:   "<<i<<endl; 
}

void main(){ 
// 	bar(3);     // ambiguous
    bar(3.0);
	bar(3.0f);
	bar(3L);
	
	auto i=5;
	bar(long(i));
	bar(double(i));
	cin.get();
}

/*
Double-Wert: 3
Double-Wert: 3
Long-Wert:   3
Long-Wert:   5
Double-Wert: 5
*/