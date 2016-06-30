#include <iostream>
#include <cstring>
using namespace std;

class Date{
		  static int count;     //Anzahl der Objekte
	      int month, day, year;     //Datum
  public: static int givec(); //liefert Anzahl der Objekte
	      Date(int mn, int dy=1, int yr=2016); //Konstruktor
	      ~Date();              //Destruktor
	      int getMonth() const; //liefert Month
	      int getYear() const;  //liefert Year
	      int getDay() const;   //liefert Day
	      void setMonth(int mn=1);  //setzt Month
	      void setYear(int yr=1);   //setzt Year
	      void setDay(int dy=1);    //setzt Day
	      void display() const; //Anzeige Datumswerte
};

class PersonInfo {
	   char *name;
       char *address;
	   Date birthday; //Objekt als Datenelement
   public: 
	   int getMonth() const { return birthday.getMonth();}
	   int getYear() const { return birthday.getYear();} 
	   int getDay() const { return birthday.getDay();}   
	   PersonInfo(char *nm,char *adr,int mn,int dy,int yr);
	   PersonInfo(char *nm, char *adr, Date d);
	   PersonInfo(char *nm=0, char *adr=0);
	   ~PersonInfo();
	   void setname(char *); //einlesen eines Namens nach name
	   char const * const getname() const { return name; } 
	   void setaddress(char *); //einlesen einer Adressse nach adress
       char const * const getaddress() const { return address; } 
       void show(); //anzeigen aller Daten zum Objekt
};

ostream &operator<<(ostream &, const Date &);
ostream &operator<<(ostream &, const PersonInfo &);

int main()
{ PersonInfo ich((char *)"htw4711",(char *)"F-List-Platz 1",4,12,2016);
 // ich.show();
  cout<<ich;
  PersonInfo du;
 // du.show();
  cout<<du;
  PersonInfo es((char *)"Mueller",(char *)"Europa");
//  es.show();
  cout<<es;
  PersonInfo er(0,0);
//  er.show();
  cout<<er;
  cin.ignore();
  return 0;
}

int Date::count=0; //Definition und Initialisierung

int Date::givec(){ return Date::count; }

Date::Date(int mn, int dy, int yr):month(mn),day(dy),year(yr){
	                count++;
				    cout<<"Konstruktor Date"<<endl;
				    cout<<"Anzahl Objekte = "<<Date::givec()<<endl;
}

Date::~Date(){ count--; cout<<"Destruktor Date"<<endl;
		   cout<<"Anzahl Objekte = "<<Date::givec()<<endl;
}

int Date::getMonth() const { return month; }

int Date::getDay() const { return day; }

int Date::getYear() const { return year; }

void Date::setMonth(int mn) { 
				  if(mn>0 && mn<13) month=mn;
			      else cerr<<"Monat m="<<mn<<" unzulaessig"<<endl;
}

void Date::setYear(int yr) { year=yr; }

void Date::setDay(int dy) { day=dy; }

void Date::display(void) const { 
	             cout<<"Tag   = "<<day<<endl;
				 cout<<"Monat = "<<month<<endl;
				 cout<<"Jahr  = "<<year<<endl;
}

ostream &operator<<(ostream &cout, const Date &d){
	             cout<<"Tag   = "<<d.getDay()<<endl;
				 cout<<"Monat = "<<d.getMonth()<<endl;
		  return cout<<"Jahr  = "<<d.getYear()<<endl;
}

PersonInfo::PersonInfo(char *nm,char *adr,int mn,int dy,int yr):birthday(mn,dy,yr),
			       name(nm?strcpy(new char[strlen(nm)+1], nm):0),
			       address(adr?strcpy(new char[strlen(adr)+1],adr):0){}

PersonInfo::PersonInfo(char *nm, char *adr, Date d) :birthday(d), 
					name(nm ? strcpy(new char[strlen(nm) + 1], nm) : 0),
					address(adr ? strcpy(new char[strlen(adr) + 1], adr) : 0) {}

PersonInfo::PersonInfo(char *nm,char *adr):birthday(1), 
					name(nm ? strcpy(new char[strlen(nm) + 1], nm) : 0),
					address(adr ? strcpy(new char[strlen(adr) + 1], adr) : 0) {}

PersonInfo::~PersonInfo(){ delete [] name; name=0; delete [] address; address=0;}

void PersonInfo::setname(char *nm)
{ delete [] name; name=0; 
  if(nm)
	  strcpy(new char[strlen(nm)+1], name);
}

void PersonInfo::setaddress(char *adr)
{ delete [] address; address=0;
  if(adr)
	  strcpy(address=new char[strlen(adr)+1], adr);     
}

void PersonInfo::show() //anzeigen aller Daten zum Objekt
{   cout<<"Name:    "<<(name?name:"")<<endl;
    cout<<"Adresse: "<<(address?address:"")<<endl;
    birthday.display();
    cout<<endl;
}

ostream &operator<<(ostream &cout, const PersonInfo &p){
		cout<<"Name:    "<<(p.getname()?p.getname():"")<<endl;
        cout<<"Adresse: "<<(p.getaddress()?p.getaddress():"")<<endl;
        cout<<"Tag   = "<<p.getDay()<<endl;
		cout<<"Monat = "<<p.getMonth()<<endl;
		cout<<"Jahr  = "<<p.getYear()<<endl;
        return cout<<endl;
}

/*
Konstruktor Date
Anzahl Objekte = 1
Name:    htw4711
Adresse: F-List-Platz 1
Tag   = 12
Monat = 4
Jahr  = 2016

Konstruktor Date
Anzahl Objekte = 2
Name:
Adresse:
Tag   = 1
Monat = 1
Jahr  = 2016

Konstruktor Date
Anzahl Objekte = 3
Name:    Mueller
Adresse: Europa
Tag   = 1
Monat = 1
Jahr  = 2016

Konstruktor Date
Anzahl Objekte = 4
Name:
Adresse:
Tag   = 1
Monat = 1
Jahr  = 2016


Destruktor Date
Anzahl Objekte = 3
Destruktor Date
Anzahl Objekte = 2
Destruktor Date
Anzahl Objekte = 1
Destruktor Date
Anzahl Objekte = 0
*/