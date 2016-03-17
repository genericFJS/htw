#include <iostream>
using namespace std;

class zk {		// Beispiel fuer Klasse mit Zeichenkette und was ein
				// Anfaenger alles falsch machen kann !!!

	char *s;	// Zeiger auf Zeichen (Zeichenkette), OK
public:
	zk(char *z = 0):s(z){ //unbedingt vermeiden !!!!
						  //s und externes z zeigen auf den gleichen 
		                  //Speicher, falls dieser
		                  //freigegeben wird, dann erzeugt
                          //der Zugriff seitens der anderen Zeiger-
		                  //variablen einen Speicherzugriffschutzfehler
		cout<<"Konstruktor zk, s = "<<(this->s ? this->s : "0")<<endl;
		cout<<"        Adresse s = "<<(int *)s<<endl;
	}

 // Destruktor: delete [] s; falsch, falls s nicht mit new angelegt wurde,
 // z.B.: zk *s1 = new zk("HTW Dresden");
 // falls s auf dynamisch mit new angelegten Speicher zeigt, dann wird
 // delete [] s; benötigt, sonst memorylack
	~zk(){ cout<<"Destruktor zk,  s = "<<s<<endl; delete [] s; s=0; }

    char * get_s(){ return s; }	//vermeiden, Zeichenkette s (Adresse)
 // wird zurückgegeben, ohne const, s kann damit von ausserhalb des 
 // Objektes veraendert und mit delete [] freigegeben werden

 // Ausweg mit const:
 // char const * const get_s(){ return s; }  // OK

 // vermeiden, s und ext. z mit gleichem Speicher, hier entsteht das
 // gleiche Probleme wie oben beim Konstruktor beschrieben
	void set_s(char *z = 0){this->s = z; } 
}; 

void main(){
	char *z = strcpy(new char[strlen("HTW Dresden")+1], "HTW Dresden");
	cout<<"        Adresse z = "<<(int *)z<<endl;
	zk *s1 = new zk(z); // ab hier: s1->s == z
    
 // erste Fehlermoeglichkeit:
  delete [] z; z=0;   // z freigeben, worauf zeigt s1->s ???
  cout<<"s1->s = "<<s1->get_s()<<endl; // Abbruch !!
 // s1->s existiert danach nicht mehr !

 // zweite Fehlermoeglichkeit: 
 // Rueckgabe des Zeigers s des Objektes *s1 an den Zeiger t, damit 
 // zeigt t ausserhalb des Objektes auf den gleichen Speicher, auf den 
 // auch s von *s1 zeigt. Hier wird t einfach mit delete [] t freigegeben, 
 // damit wird s von *s1 ungueltig und s1->get_s() erzeugt einen Fehler:

 //	char * t = s1->get_s();	
 //	delete [] t; t=0;  // Zugriff auf s1->s
 // cout<<"s1->s = "<<s1->get_s()<<endl;      // Abbruch

 // Ausweg:
 //	char const * const t = s1->get_s(); 
 //	delete [] t; t=0;  // nicht moeglich
 // t = "HTW";         // nicht moeglich

 // dritte Fehlermoeglichkeit:
 // kein explizit formulierter Kopierkonstruktor 
 // s2->s und s1->s zeigen auf identischen heap - Speicher !!
	zk *s2 = new zk(*s1);
	
	try {	//selbst try / catch helfen nicht !
		    delete s1; s1 = 0;
			cout<<"s2->s = "<<s2->get_s()<<endl;      // Abbruch
	}
	catch(...){
			cout<<"Fehler s2->s\n";
	}

	delete s1; s1=0;
	cin.get();
}
/*
        Adresse z = 00333090
Konstruktor zk, s = HTW Dresden
        Adresse s = 00333090
s1->s = ¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■

Destruktor zk,  s = ¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■¯■
*/