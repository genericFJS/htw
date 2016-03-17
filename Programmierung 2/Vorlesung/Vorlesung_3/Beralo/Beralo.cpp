// Bereichsaufloeseoperator ::

#include <iostream>

using namespace std;

int zahl; // global, wird mit 0 initialisiert !

auto main() -> void {
	    auto zahl(815);  // local
        char loc[] = "innen";
		cout<<"  zahl="<<zahl<<"    ::zahl="
			<<::zahl<<endl;
		cout<<"++zahl="<<++zahl<<"  ++::zahl="
			<<++::zahl<<endl;
	//	cout<<"::loc= "<<::loc<<endl; // Error
		{ // one more level
		  auto zahl=11.0f;
          cout<<"  zahl="<<zahl<<"     ::zahl="
			  <<::zahl<<endl;
		}
        cin.get();
}

/*
  zahl=815    ::zahl=0
++zahl=816  ++::zahl=1
  zahl=11     ::zahl=1
*/