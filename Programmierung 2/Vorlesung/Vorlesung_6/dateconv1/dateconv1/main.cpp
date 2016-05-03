#include"datum.h"
#include<iostream>
using namespace std;  //dateconv1 

int main() {
  Datum d;
  string s1 = d;                      // implizit
  cout <<"s1 = "<<s1<<endl;
  string s2 = (string)d;              // explizit
  cout<<"s2 = "<<s2<<endl;
  string s3 = static_cast<string>(d); // explizit
  cout<<"s3 = "<<s3<<endl;  
  cin.get();
}
