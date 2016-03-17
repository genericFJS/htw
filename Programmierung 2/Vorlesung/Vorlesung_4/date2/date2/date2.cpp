#include <iostream>

using namespace std;

class Date {                                   // date2.cpp
	  mutable int day, month, year;
  public:
	  Date(int dy=1, int mn = 1, int yr = 2017):day(dy), month(mn), year(yr){}

	  int get_month() const;                     // read-only const function

	  void set_month(int mn = 1) const { month = mn; }  // write function
};

int Date::get_month() const {  return month; }


int main(){
	Date const * const d = new Date(13,04,2017);

	d->set_month(5);  

	cout<<"d->month = "<<d->get_month()<<endl;  // doesn't modify anything

	cin.get();
}