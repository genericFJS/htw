#include <iostream>
#include <fstream>

using namespace  std;			//robust_ea1.cpp 

void main(){

    double d=0.0;
	char c='\n';
	do{
		if(cin.rdstate() || c!='\n'){
			cin.clear(); cin.ignore(INT_MAX,'\n');
		}
		cout<<"d = "; cin>>d; c=cin.peek(); //Returns the next character to be read
	} while(cin.rdstate() || c!='\n');
    cin.clear(); cin.ignore(INT_MAX,'\n');
	cout<<"Wert d = "<<d<<endl;
	cin.ignore();
}
/*
d = mmmmmm
d = 77xxx
d = 12345
*/