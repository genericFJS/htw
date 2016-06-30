#include <iostream>
#include <string>
using namespace std;

class zk {
	string s; 
public:
	zk(string z = 0):s(z){
		cout<<"Konstruktor zk, s = "<<this->s<<endl;
	}

	~zk(){ cout<<"Destruktor zk,  s = "<<s<<endl; }

	string get_s(){ return s; }
	
	void set_s(string z=0){this->s =z;}
};

void main(){
	string temp = "HTW Dresden";
	string z = temp;
	zk *s1 = new zk(z);
	string s01 = s1->get_s();  // Kopie von s1->s
	cout<<"s1->s = "<<s01<<endl;
	         

	s1->set_s("TU Dresden");
	s01 = s1->get_s();        // Kopie von s1->s
	cout<<"s1->s = "<<s01<<endl;
	cin.get();
}
/*
  Konstruktor zk, s = HTW Dresden
s1->s = HTW Dresden
s1->s = TU Dresden    
*/