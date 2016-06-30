/* strstream/strstrea.cpp */
#include<iostream>
#include"zahlToString.h"

using namespace std;

int main() {
  double xd = 73.1635435363;               // Ausgabe:
  cout << zahlToString(xd) << endl;        //73.1635
  cout << zahlToString(xd,12) << endl;     //     73.1635
  cout << zahlToString(xd,12,1) << endl;   //  7.3164e+01
  cout << zahlToString(xd,12,1,3) << endl; //   7.316e+01
  cout << zahlToString(xd,12,0,3) << endl; //      73.164

  int xi = 1234567;
  cout << zahlToString(xi) << endl;        //1234567
  cout << zahlToString(xi,14) << endl;     //       1234567

  float xf = 1234.567;
  cout << zahlToString(xf) << endl;        //1234.57
  unsigned long xl = 123456789L;
  cout << zahlToString(xl) << endl;        //123456789
}

