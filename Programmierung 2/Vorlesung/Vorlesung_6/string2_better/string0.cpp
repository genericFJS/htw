#include <iostream>
#include <cstring>
using namespace std;

class zk {//Beispiel fuer korrekte Klasse mit dynamischen Zeichenketten,
	      //wie string0_true, zusaetzlich mit Zuweisungsoperator und
	      //operator+() zur Verkettung
	      //Nachteil ist wiederum, dass bei der Rueckgabe von s davon
	      //eine Kopie auf dem heap angelgt wird, d.h. Rueckgabe-Objekt
	      //und s sind vollstaendig getrennt. Die ueber get_s() erhaltene
	      //Kopie muﬂ vom get_s() - Aufrufer selbst freigegeben werden !! 
	char *s; 
public:
	zk(char *z = 0):s(z ? strcpy(new char[strlen(z)+1], z) : 0){
		cout<<"Konstruktor zk, s = "<<(this->s ? this->s : "0")<<endl;
		cout<<"        Adresse s = "<<(int *)s<<endl;
	}

	// Kopierkonstruktor
	zk(const zk &zkd):s(&zkd ? (zkd.s ? strcpy(new char[strlen(zkd.s)+1], zkd.s) : 0): 0){
		  cout<<"Kopierkonstruktor zk, zkd.s = "<<((&zkd && zkd.s) ? zkd.s : "0")<<endl;
	}

	//Zuweisungsoperator
	zk &operator=(const zk &zkd){
		cout<<"Aufruf Zuweisungsoperator\n";
		if(this && &zkd != this){
			  delete [] s; s=0;
			  if(&zkd)
			     s=zkd.s ? strcpy(new char[strlen(zkd.s)+1], zkd.s) : 0;
		}
		return *this;
	}

	//Destruktor
	~zk(){ if(this){ cout<<"Destruktor zk,  s = "<<(s?s:"0")<<endl; delete [] s; s=0; }}

	char *get_s() const { return this ? (s ? strcpy(new char[strlen(s)+1], s) : 0) : 0; }

	void set_s(char *z=0){ if(this) {delete [] s; this->s =z?strcpy(new char[strlen(z)+1], z):0; }}

	zk &operator+=(const zk &zkd){
		if(this && &zkd){  //this ex. und zkd ex.
		   if(s && zkd.s){
			   char *t = new char[strlen(s)+strlen(zkd.s)+1];
			   strcpy(t,s); strcpy(t+strlen(s), zkd.s);
			   delete [] s; s = t;
		   }
		   if(!s && zkd.s){
			   s = strcpy(new char[strlen(zkd.s)+1], zkd.s);
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

	// hier wird this->s durch zkd->s ersetzt, ist ueberfluessig
	void set_zk(zk &zkd){ 
		if(!this) return;
		if(!&zkd){ delete [] s; s = 0; return;}
		delete [] s; s=zkd.s ? strcpy(new char[strlen(zkd.s)+1], zkd.s) : 0; 
	} 

	static void _(unsigned long *m){ // *m = Anzahl Zeichen in cin
		char c;                             //local
        if(cin.get(c)&&c!='\n')(*m)++,_(m); //down
        cin.putback(c);                     //up
    }
};

ostream &operator<<(ostream &cout, zk &zkd){
	if(&zkd){
		char *s = zkd.get_s();
		size_t laenge = 0;
		if(s) laenge = strlen(s); else laenge=0;
		cout<<"\nLaenge(zkd) = "<<laenge<<'\n';
		cout<<"Inhalt(zkd) = "<<(s?s:"0")<<endl;
		delete [] s; s=0;
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
	char *z = strcpy(new char[strlen(zt)+1], zt);
	cout<<"        Adresse z = "<<(int *)z<<endl;
	
	//-------------------------------------------------
    zk *s1 = 0;
	zk *s2 = 0;
	s2 = new zk(*s1);		    //Kopierkonstruktor
	cout<<"&s2 = "<<&s2<<endl;
	char *s02 = s2->get_s();	//Rueckgabe Kopie s2->s
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 
    delete s2; s2 = 0;

	s1 = new zk(z);			    //Konstruktor
	s2 = new zk(*s1);		    //Kopierkonstruktor
	s02 = s2->get_s();			//Rueckgabe Kopie s2->s
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 

	s2 = new zk("TU");
	s2 = new zk(*s1);		    //Kopierkonstruktor
	s02 = s2->get_s();			//Rueckgabe Kopie s2->s
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 

	delete s1; s1 = 0;
	s2 = new zk(*s1);		    //Kopierkonstruktor
	s02 = s2->get_s();			//Rueckgabe Kopie s2->s
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 
    delete s2; s2 = 0;

	//-------------------------------------------------
	*s2 = *s1;					//Zuweisungsoperator
	s02 = s2->get_s();
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 

	delete s2; s2 = 0;
	s1 = new zk("HTW");
	*s2 = *s1;					//Zuweisungsoperator
	s02 = s2->get_s();			// s2 == 0, s02 == 0
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 

	delete s1; s1 =0;
	s2 = new zk("TU");
	*s2 = *s1;					//Zuweisungsoperator
	s02 = s2->get_s();			// OK
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 

	s1 = new zk("HTW");
	*s2 = *s1;					//Zuweisungsoperator
	s02 = s2->get_s();			// OK
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 

	s1->set_s("TU Dresden");
	char * s01 = s1->get_s(); 
	cout<<"s1->s = "<<(s01?s01:"0")<<endl;
	delete [] s01; s01 = 0;

	s2->set_zk(*s1);
	s02 = s2->get_s();
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	delete [] s02; s02 = 0; 
	
	*s2+=*s1;
	s02 = s2->get_s();
	cout<<"s2->s = "<<(s02?s02:"0")<<endl;
	
	cin>>*s2;         //Ueberladen operator>>()
	operator>>(cin, *s2);
	cout<<*s2<<endl;  //Ueberladen operator<<()
	operator<<(cout, *s2)<<endl;


	delete [] s02; s02 = 0; 

	delete s1; s1 = 0;
	delete s2; s2 = 0;

	cin.get();
}