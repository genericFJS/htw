#include <iostream>
#include <string>
using namespace std;

class person {  string name;
				int  jahr;
  public:
	person(string n="", int j=2005):jahr(j),name(n){}

	int get_jahr() const { return jahr; }
	string get_name() const { return name; }
	person get_person() const { return *this; }
};

class student : public person {
	unsigned long matrnr;
	string studg;
  public:
	student(string n="", int j=2005, unsigned long m=4711, 
	string s="WI04"): person(n, j), matrnr(m),studg(s){}

	unsigned long get_matrnr() const { return matrnr; }
	string get_studg() const { return studg; }
	student get_person() const { return *this; } //overwritten
};

void main(){
			student s1("Lehmann", 1984, 22337, "WI07");
			person p1(s1);
			cout<<"s1.jahr   = "<<p1.get_jahr()<<endl;
			cout<<"s1.matrnr = "<<s1.get_matrnr()<<endl;
			cout<<"s1.name   = "<<p1.get_name()<<endl;
			cout<<"s1.studg  = "<<s1.get_studg()<<endl;
			p1 = s1.get_person();
			p1 = ((person)s1).get_person();
			student s2 = s1.get_person();
			person p2(s1);
		//	student s3 = ((person)s1).get_person();  //Compile-Error
		//	student s4 = p1.get_person();            //Compile-Error
		//	student s5 = ((student)p1).get_person(); //Compile-Error
			
			cin.ignore();
}

/* s1.jahr   = 1984
   s1.matrnr = 22337
   s1.name   = Lehmann
   s1.studga = WI07    */

