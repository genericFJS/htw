#include <iostream>

using namespace std;

class Date
{
public:
   Date(int mn=12,int dy=31,int yr=1999):month(mn),year(yr),day(dy){
         cout<<"Konstruktor Date"<<endl;
         cout<<"Tag  ="<<day<<endl;
		 cout<<"Monat="<<month<<endl;
         cout<<"Jahr ="<<year<<'\n'<<endl;
   };
   ~Date(){ cout<<"Destruktor Date"<<endl; }
   int getMonth() const;       // A read-only function
   void setMonth( int mn );    // A write function cannot be const
   int getYear() const;
   void setYear( int yr) const;// setYear(int): const write function                            
private:
   int day;
   int month;
   mutable int year; //mutable: assignment by const function allowed
};

int Date::getMonth() const  // const function
{
   return month;        // Doesn't modify anything
}

int Date::getYear()  const  // const function
{
   return year;			// Doesn't modify anything
}

void Date::setMonth( int mn )
{
   month = mn;          // Modifies data member
}

void Date::setYear(int yr) const // const memberfunction
{
   year = yr;           // OK: modifies a mutable data member
   cout<<"Monat="<<month<<endl;
   cout<<"Jahr ="<<year<<'\n'<<endl;
   // month=12; // Error: modifies a non-mutable data member
   // int i=setMonth(month); // Error                               
}

void main(){
     const Date t1;
	 t1.setYear(2000);
//	 t1.setMonth(1);     // Error
	 cout<<"Monat = "<<t1.getMonth()<<endl;
	 cout<<"Jahr  = "<<t1.getYear()<<endl;
	 cin.get();
}

