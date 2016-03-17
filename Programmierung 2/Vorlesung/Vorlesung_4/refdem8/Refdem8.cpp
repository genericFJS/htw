#include <iostream>  // refdem8.cpp
using namespace std;

int &func(){ 
	         /*static*/ int loc=5;
	         return loc;
	       }

auto main() -> void {
	         int &k = func();
	         cout<<"k = "<<k<<endl;
			 cin.get();
	       }
