#include <iostream>
using namespace std;

class x {
      public: static void xm(){ cout<<"from xm\n"; }

};

void main(){
	x::xm();
	cin.get();
}