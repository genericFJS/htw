#include <iostream>
#include <cstring>
using namespace std;

class zk { // Beispiel fuer korrekte Klasse mit dynamischen C-strings
	       // Hier wird nur s als const-Inhalt und const Zeiger
	       // zurueckgegeben, solange dieser nicht wieder ausserhalb
	       // nach (char *) "gecastet" wird, kann von ausserhalb eines
	       // zk-Objektes nicht auf das im Objekt befindliche s zuge-
	       // griffen werden. Jedoch kann ein (char *) - cast nicht 
	       // verhindert werden
	char *s; 
public:
	zk(char *z = 0):s(z ? strcpy(new char[strlen(z)+1], z) : 0){
		cout<<"Konstruktor zk, s = "<<(this->s ? this->s : "0")<<endl;
		cout<<"        Adresse s = "<<(int *)s<<endl;
	}

	// Kopierkonstruktor
	zk(const zk &zkd):s(&zkd && zkd.s ? strcpy(new char[strlen(zkd.s)+1], zkd.s) : 0){
		cout<<"Kopierkonstruktor zk, zkd.s = "<<((&zkd && zkd.s) ? zkd.s : "0")<<endl;
	}
	// Zuweisungsoperator ueberladen
	zk &operator=(const zk &zkd){
		if(this && &zkd != this){
			delete [] s; s=0;
			if(&zkd)
			   s=zkd.s ? strcpy(new char[strlen(zkd.s)+1], zkd.s) : 0;
		}
		return *this;
	}

	~zk(){ if(this){ cout<<"Destruktor zk,  s = "<<(s ? s : "0")<<endl; delete [] s; s=0; }}

	const char *const get_s() const { return this ? s : 0; }  // s und *s sind const !!

	void set_s(char *z=0){ 
		if(this){ delete [] s; this->s = z?strcpy(new char[strlen(z)+1], z) : 0; }
	}

	//Ueberladen des += - Operators
	zk &operator+=(const zk &zkd){
		if(this && &zkd){
			if(s && zkd.s){
				char *t = new char[strlen(s)+strlen(zkd.s)+1];
				strcpy(t, s); strcpy(t+strlen(s), zkd.s);
				delete [] s; s = t;
			}
			if(!s && zkd.s){
				s = zkd.s?strcpy(new char[strlen(zkd.s)+1], zkd.s):0;
			}
			if(s && !zkd.s){
              delete [] s; s = 0;
		    }
			return *this;
		}
		if(!&zkd){			// &zkd == 0
			return *this;   // *this unveraendert
		}
		return *this;       // this == 0, unveraendert
	}

	static void _(unsigned long *m){ // *m = Anzahl Zeichen in cin
		char c;                             //local
        if(cin.get(c)&&c!='\n')(*m)++,_(m); //down
        cin.putback(c);                     //up
    }
};

ostream &operator<<(ostream &cout, zk &zkd){
	if(&zkd){
		size_t laenge = zkd.get_s()?strlen(zkd.get_s()):0;
		cout<<"\nLaenge(zkd) = "<<laenge<<'\n';
		cout<<"Inhalt(zkd) = "<<(zkd.get_s()?zkd.get_s():"0")<<endl;
	}
	return cout;
}

istream &operator>>(istream &cin, zk &zkd){
	if(&zkd){
		unsigned long n=0UL;	
		cout<<"\nEingabe zk.s = ";
		zk::_(&n);
		char *s = new char[n+1UL];
		cin.getline(s, n+1UL, '\n');
		zkd.set_s(s);
		delete [] s; s=0;
	}
	return cin;
}

void main(){
	char *zt = "HTW Dresden";
	char *z = zt?strcpy(new char[strlen(zt)+1], zt):0;
	cout<<"        Adresse z = "<<(int *)z<<endl;

	zk *s1 = new zk(z);			          // Konstruktor

	zk *s2 = new zk(*s1);		          // Kopierkonstruktor
	delete [] z; z=0;

	// char *s04 = s2->get_s();           // Compile-Error

	//-------------------------------------------------------------
	// Gefahr durch cast:
	// char *s03 = (char *)s2->get_s();   // OK: cast nach char *
	// delete [] s03; s03 = 0; 
	// die folgende s2->get_s() - Ausgabe verursacht einen 
	// Abbruchfehler:
	// cout<<"s2->get_s() = "<<s2->get_s()<<endl;
	//-------------------------------------------------------------
 
	const char * const so5 = s2->get_s(); //OK, nichts aenderbar !!

	char *s02 = s2->get_s()?strcpy(new char[strlen(s2->get_s())+1], 
		                           s2->get_s()):0;
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 

	*s2 = *s1;					//Zuweisungsoperator
	cout<<"s2->s = "<<(s2->get_s()?s2->get_s():"0")<<endl;

	s1->set_s("TU Dresden");
	cout<<"s1->s = "<<(s1->get_s()?s1->get_s():"0")<<endl;

	*s2+=*s1;
	cout<<"s2->s = "<<(s2->get_s()?s2->get_s():"0")<<endl;

	cin>>*s2;
	operator>>(cin, *s2);
	cout<<*s2<<endl;
	operator<<(cout, *s2)<<endl;

	delete s1; s1 = 0;
	delete s2; s2 = 0;

	cin.get();
}