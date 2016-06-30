#include <iostream>

using namespace std;

class musiker { public: ~musiker();  // nicht virtuell
			// ...
	      };

musiker::~musiker(){ cout<<"Musiker wird zerstoert\n"; }

class trompeter : public musiker { // nicht virtuell
				   public: ~trompeter();
				 };

trompeter::~trompeter(){ cout<<"Trompeter wird zerstoert\n"; }

void main(){ 
	trompeter *pt;
	musiker *pm;
	pt=new trompeter;
	delete pt;       //OK, beide Destruktoren im Aufruf
	pm=new trompeter;
	delete pm;       //Problem, nur musiker-Destruktor
	cin.get();
}
