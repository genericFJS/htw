#include <ctime>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;

class Datum {
  public:
    Datum();                         // Default-Konstruktor
	Datum(int t, int m, int j);      // tag, monat, jahr
	Datum(const Datum &d);           // Kopierkonstruktor
	~Datum();					     // Destruktor
	void set(int t, int m, int j);   // Datum setzen
    void aktuell();                  // Systemdatum setzen
	bool istGueltigesDatum() const;  // Datum gueltig ?
	bool istSchaltjahr() const;		 // Schaltjahr ?
	Datum& operator++();             // Tag hochzählen, präfix
    Datum operator++(int);           // Tag hochzählen, postfix
    int tag() const;                 // Tag als int
	int monat() const;				 // Monat als int
	int jahr() const;                // Jahr als int
	static int givec();				 // liefert Anzahl der Objekte
    operator std::string() const;    // Typumwandlungsoperator
  private:
    int tag_, monat_, jahr_;         // private Member
	static int count;                // Anzahl der Objekte
};

int Datum::count = 0;

Datum::Datum(){ aktuell(); count++;
                cout<<"Konstruktor Datum: count = "
					<<count<<endl;
}

Datum::Datum(int tag, int monat, int jahr):tag_(tag), monat_(monat), 
jahr_(jahr){
	set(tag, monat, jahr);
	count++;
    cout<<"Konstruktor Datum: count = "
		<<count<<endl;
}

Datum::Datum(const Datum &d):tag_(d.tag_),monat_(d.monat_),
jahr_(d.jahr_){
	count++;
    cout<<"Konstruktor Datum: count = "
		<<count<<endl;
}

Datum::~Datum(){ count--; 
				 cout<<"Destruktor Datum: count = "
					 <<count<<endl;
}

int Datum::tag() const { return tag_; }
int Datum::monat() const { return monat_; }
int Datum::jahr() const { return jahr_; }
int Datum::givec() { return count; }

void Datum::aktuell() {          // Systemdatum eintragen
    time_t now = time(NULL);
    tm *z = localtime(&now);     // Zeiger auf struct tm
    jahr_  = z->tm_year + 1900;
    monat_ = z->tm_mon+1;        // localtime liefert 0..11
    tag_   = z->tm_mday;
}

// besser: durch Methode string toString() ersetzen!
// 
Datum::operator std::string() const {
    std::string temp("tt.mm.jjjj");                
    temp[0] = tag_/10 +'0';		  // implizite Umwandlung in char
    temp[1] = tag_%10 +'0';
    temp[3] = monat_/10 +'0';
    temp[4] = monat_%10 +'0';
    int pos = 9;                  // letzte Jahresziffer
    int j = jahr_;
    while(j > 0) {
       temp[pos] = j % 10 + '0';  // letzte Ziffer
       j = j/10;                  // letzte Ziffer abtrennen
       --pos;
    }
    return temp;
}

bool istGueltigesDatum(int t, int m, int j);

Datum& Datum::operator++() {     // Datum um 1 Tag erhöhen
   ++tag_;
   // Monatsende erreicht?
   if(!istGueltigesDatum()) {
     tag_ = 1;
     if (++monat_ > 12) {
        monat_ = 1;
        ++jahr_;
     }
   }
   return *this;
}

Datum Datum::operator++(int) {        // Datum um 1 Tag erhöhen
   Datum temp = *this;
   ++*this;                           // Präfix ++ aufrufen
   return temp;
}

bool istSchaltjahr(int jahr);

inline bool Datum::istSchaltjahr() const {
  return ::istSchaltjahr(jahr_); 
}

void Datum::set(int t, int m, int j) {
	if(!istGueltigesDatum()){
		cout<<"set: tag = "<<t
			<<" oder monat = "<<m
			<<" oder jahr = "<<j<<" falsch\n";
		aktuell();
		return;
	}
    tag_ = t;
    monat_ = m;
    jahr_ = j;
}

// globale Funktionen
ostream &operator<<(ostream &cout, const Datum &d){
		cout<<"Datum d      = "<<(string)d<<endl;
		cout<<"Datum::count = "<<Datum::givec()<<endl; 
		return cout;
}

inline bool istSchaltjahr(int jahr) {
   return  (jahr % 4 == 0 && jahr % 100) || jahr % 400 == 0;
}

bool istGueltigesDatum(int t, int m, int j) {
     // Tage pro Monat(static vermeidet Neuinitialisierung):
     static int tmp[]={31,28,31,30,31,30,31,31,30,31,30,31};

     tmp[1] = istSchaltjahr(j) ? 29 : 28;

     return     m >= 1    && m <= 12
            && j  >= 1583 && j  <= 2399  // oder mehr
            && t  >= 1    && t   <= tmp[m-1];
}

inline bool Datum::istGueltigesDatum() const {
	return ::istGueltigesDatum(tag_, monat_, jahr_);
}

class PersonInfo {
	string name_;
	string address_;
	Datum birthday_;
public:
	PersonInfo(string nm, string adr, int t, int m, int j):
	  name_(nm),address_(adr),
		birthday_(t, m, j){}
	
	PersonInfo(string nm, string adr, const Datum &d):
	  name_(nm),address_(adr),
		birthday_(d){}

	PersonInfo(string nm="", string adr=""):
	  name_(nm),address_(adr), birthday_(){}
    
	string name(){ return name_; }
	string address(){ return address_; }
	Datum birthday(){ return birthday_; }
};

ostream &operator<<(ostream &cout, PersonInfo &p){
	    cout<<"name_        = "<<p.name()<<endl;
		cout<<"address_     = "<<p.address()<<endl;
		cout<<"Datum d      = "<<p.birthday();
		return cout;
}

int main(){
	PersonInfo ich((char *)"htw4711",(char *)"F-List-Platz 1");
	cout<<ich;
	PersonInfo du;
	cout<<du;
	PersonInfo es((char *)"Mueller",(char *)"Europa",13,4,2016);
	cout<<es;
	Datum d1(29,2,2016);
	PersonInfo er((char *)"",(char *)"",d1);
	cout<<er;
	cin.ignore();
	return 0;
}

/*
Konstruktor Datum: count = 1
name_        = htw4711
address_     = F-List-Platz 1
Konstruktor Datum: count = 2
Datum d      = Datum d      = 11.04.2016
Datum::count = 2
Destruktor Datum: count = 1
Konstruktor Datum: count = 2
name_        =
address_     =
Konstruktor Datum: count = 3
Datum d      = Datum d      = 11.04.2016
Datum::count = 3
Destruktor Datum: count = 2
Konstruktor Datum: count = 3
name_        = Mueller
address_     = Europa
Konstruktor Datum: count = 4
Datum d      = Datum d      = 29.02.2012
Datum::count = 4
Destruktor Datum: count = 3
Konstruktor Datum: count = 4
Konstruktor Datum: count = 5
name_        =
address_     =
Konstruktor Datum: count = 6
Datum d      = Datum d      = 29.02.2016
Datum::count = 6
Destruktor Datum: count = 5

Destruktor Datum: count = 4
Destruktor Datum: count = 3
Destruktor Datum: count = 2
Destruktor Datum: count = 1
Destruktor Datum: count = 0
*/