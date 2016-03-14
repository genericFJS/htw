#include <iostream>
#include <string>
using namespace std;
#include "person.h"

int main()
{
  Person p1(string("James Bond"), 1,2,1989);
  p1.display();
  return 0;
}