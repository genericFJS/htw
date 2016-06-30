#ifndef _PERSON_H_
#define _PERSON_H_

#include "date.h"

#include <iostream>
#include <string>
using namespace std;

class Person
{
  string name;
  date GebDat;
  public:
  Person(string name, int d, int m, int y)
  {
    this->name=name;
    GebDat=date(d,m,y);
  }
  void display()
  {
    cout<<name<<": ";
    GebDat.display();
    cout<<endl;
  }

};

#endif