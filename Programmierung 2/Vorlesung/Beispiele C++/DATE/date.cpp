// A. Beck
// Beispiel zur Vorlesung PSP II


#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#include "date.h"


void date::display()const
{
  cout<<setw(2)<<setfill('0')<<this->Day<<'.'
      <<setw(2)<<setfill('0')<<this->Month<<'.'
      <<this->Year;
}

void date::setDate(int Day, int Month, int Year)
{
  int DaysPerMonth[]=
      {0,31,28,31,30,31,30,31,31,30,31,30,31};
  this->Year=max(1900,Year);
  this->Year=min(2099,this->Year);
  this->Month=max(1,Month);
  this->Month=min(12,this->Month);
  if(this->Month==2 && this->Year%4==0)DaysPerMonth[2]=29;
  this->Day=max(1,Day);
  this->Day=min(DaysPerMonth[this->Month],this->Day);
}

date::date()
{
  time_t mytime = time (NULL);
  struct tm * timeinfo;
  timeinfo = localtime ( &mytime );
  Day  =timeinfo->tm_mday; 
  Month=timeinfo->tm_mon+1; 
  Year =timeinfo->tm_year+1900;
}

/*
// Constructor
date::date()
{Day=0; Month=0; Year=0;}
*/
date::date(int d, int m, int y)
{
  int DaysPerMonth[]=
      {0,31,28,31,30,31,30,31,31,30,31,30,31};
  Year=max(1900,y);
  Year=min(2099,Year);
  Month=max(1,m);
  Month=min(12,Month);
  if(Month==2 && Year%4==0)DaysPerMonth[2]=29;
  Day=max(1,d);
  Day=min(DaysPerMonth[Month],Day);
}
