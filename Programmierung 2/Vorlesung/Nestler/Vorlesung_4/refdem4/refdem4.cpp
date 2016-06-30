// refdem4.cpp - Konstante als Referenz
#include <iostream>
using namespace std;

void main()
{
 int intvar=123;                           // read and write
 const int& aliasint = intvar;             // only read
 cout<<"intvar="<<(++intvar)++<<"    aliasint="<<aliasint<<endl;
 //                  124                            125
 intvar++;              // Can modify the object
 // aliasint++;         // Cannot modify a const object

 cout<<"intvar="<<(++intvar)++<<"    aliasint="<<aliasint<<endl;
 //                  127                            128
 cout<<aliasint<<endl;
 //     128
 cin.get();
}

/*
intvar=124    aliasint=125
intvar=127    aliasint=128
128
*/