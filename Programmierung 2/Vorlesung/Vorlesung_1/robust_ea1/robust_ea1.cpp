#include <iostream>

using namespace  std;			//robust_ea1.cpp 

void main(){
    auto d=0.0;

	/* Variante 1:
	auto c='\n';
	do {
		if(c!='\n'){
			cin.ignore(INT_MAX,'\n');
		}
		cout<<"d = "; cin>>d; 
        if(cin.eof()) break;
		cin.clear();
	} while((c=cin.peek())!='\n');  */

	// --------------------------------------------
	// Variante 2:
	do {
		cout<<"d = "; cin>>d; 
		if(cin.eof()) break;
		if(cin.fail() || (cin.peek() != '\n')){
			cin.clear(); cin.ignore(INT_MAX,'\n');
			continue;
		}
		break;
	} while(true);
	// --------------------------------------------

	if(cin.eof()){ cin.clear(); cout<<"eof\n"; }
	else {
		cin.clear(); cin.ignore(INT_MAX,'\n');
		cout<<"Wert d = "<<d<<endl;
	}
	cin.ignore();
}
/*
d = mmmmmm
d = 77xxx
d = 12345
*/