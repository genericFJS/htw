#include <iostream>   // private1.cpp
using namespace std;

class Y { public: Y(long w=20L):y(w){ y++; }
                  long y;
};

class X:private Y { 
          public: X(long w=0L):x(w){};  // Y(20) implizit !
                  long x;
			      void aus(){ cout<<"y="<<y<<'\n'; }
};

class W: public X {
         public: // long get_y(){ return y; }  // kein Zugriff auf y
};

void main(){ Y yps(5L);
             cout<<"Y.y = "<<yps.y<<endl;
             X ix(7L);
//           cout<<"X.y = "<<ix.y<<endl;  //Fehler, weil private-Ableitung
             cout<<"X.x = "<<ix.x<<endl;
			 ix.aus();
             cin.ignore();
}

/*
Y.y = 6
X.x = 7
y=21
*/