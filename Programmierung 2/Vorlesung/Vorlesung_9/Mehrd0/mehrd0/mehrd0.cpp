#include <iostream>
using namespace std;

class X { public: int wert;
                  void str(){ cout<<"X wert = "<<wert<<endl; }
};

class Y : public X { public: float wert;
                             void  str(float x){ cout<<"Y x    = "<<x<<endl; 
						     }
						     void htw(){ X::str();  // str von X
							             str(wert); // str, wert von Y
						     }
};

void main(){
			Y aha;
			aha.wert=47.11f;     // Komponente von Y
			aha.Y::wert=47.11f;  //     "       "  "
			aha.X::wert=4711;    // Komponente von X
			aha.htw(); 
		//	aha.str();			 // Compile-Error
			aha.X::str();        // OK
			cin.get();
}

/*
X wert = 4711
Y x    = 47.11
X wert = 4711
*/
