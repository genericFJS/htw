// : C18  : Iofile.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Reading & writing one file
#include <iostream>
#include <fstream>
#include "require.h"
using namespace std;

void main() {
  ifstream in("Iofile.cpp");
  assure(in, "Iofile.cpp");
  ofstream out("Iofile.out");
  assure(out, "Iofile.out");
  out << in.rdbuf(); // Copy file
  in.close();
  out.close();
// Open for reading and writing:
  ifstream in2("Iofile.out", ios::in | ios::out);
  assure(in2, "Iofile.out");
//ostream mit darunterliegenden Puffer erzeugen:
  ostream out2(in2.rdbuf());
//cout << in2.rdbuf();  // Print whole file
//Ueberschreiben 23 Bytes am Ende
  out2 << "Where does this end up?";
  cout<<"out2.tellp()  "<<out2.tellp()<<'\n';
//put-Zeiger auf 0
  out2.seekp(0, ios::beg);
//Ueberschreiben der 23 Bytes
  out2 << "..And what about this ?";
//put-Zeiger auf 0
  in2.seekg(0, ios::beg);
  cout << in2.rdbuf();
} ///:~

/*
out2.tellp()  1067
..And what about this ?
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Reading & writing one file
#include <iostream>
#include <fstream>
#include "require.h"
using namespace std;

void main() {
  ifstream in("Iofile.cpp");
  assure(in, "Iofile.cpp");
  ofstream out("Iofile.out");
  assure(out, "Iofile.out");
  out << in.rdbuf(); // Copy file
  in.close();
  out.close();
// Open for reading and writing:
  ifstream in2("Iofile.out", ios::in | ios::out);
  assure(in2, "Iofile.out");
//ostream mit darunterliegenden Puffer erzeugen:
  ostream out2(in2.rdbuf());
  cout << in2.rdbuf();  // Print whole file
//Ueberschreiben 23 Bytes am Ende
  out2 << "Where does this end up?";
  cout<<"out2.tellp()  "<<out2.tellp()<<'\n';
//put-Zeiger auf 0
  out2.seekp(0, ios::beg);
//Ueberschreiben der 23 Bytes
  out2 << "..And what about this ?";
//put-Zeiger auf 0
  in2.seekg(0, ios::beg);
  cout << in2.rdbuf();
} ///:~
Where does this end up?
*/