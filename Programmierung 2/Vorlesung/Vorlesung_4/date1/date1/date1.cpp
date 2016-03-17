#include <iostream>

using namespace std;                // Kommentare bei /* const */ entfernen

class Date {
	  mutable int day, month, year;
  public:
	  Date(int dy=1, int mn = 1, int yr = 2012):day(dy), month(mn), year(yr){}

	  int get_month() const; //Error ohne const, read-only const function

	  void set_month(int mn = 1) const { month = mn; }  // write function, not const
};

int Date::get_month() const {  return month; } // Error ohne const


int main(){
	Date const * const d = new Date(13,04,2012);

	cout<<"d->month = "<<d->get_month()<<endl;  // doesn't modify anything

	d->set_month(5);  // the object has type qualifiers that are not compatible
	                  // with the member function
	cin.get();
}