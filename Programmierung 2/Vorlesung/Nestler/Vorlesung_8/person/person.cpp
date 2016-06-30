#include <iostream>

using namespace std;

const int na = 30;
const int sg = 20;

class person { char name[na];
	       int  jahr;
  public:
	person(char n[na]="", int j=2005):jahr(j){
	    strncpy_s(name,sizeof(name),n,sizeof(name)-1); 
	}

	int get_jahr() const { return jahr; }
	const char * const get_name() const { return name; }
};

class student : public person {
	unsigned long matrnr;
	char studg[sg];
  public:
	student(char n[na]="", int j=2005, 
	unsigned long m=4711, 
	char s[sg]="WI04"): person(n, j), matrnr(m){
	  strncpy_s(studg, sizeof(studg), s, sizeof(studg)-1); 
	}
	unsigned long get_matrnr() const { return matrnr; }
	const char * const get_studg() const { 
		return studg; 
	}
};

void main(){
	student s1("Lehmann", 1984, 22337, "WI07");
	cout<<"s1.jahr   = "<<s1.get_jahr()<<endl;
	cout<<"s1.matrnr = "<<s1.get_matrnr()<<endl;
	cout<<"s1.name   = "<<s1.get_name()<<endl;
	cout<<"s1.studg  = "<<s1.get_studg()<<endl;
	cin.ignore();
}

/* s1.jahr   = 1984
   s1.matrnr = 22337
   s1.name   = Lehmann
   s1.studga = WI07    */

