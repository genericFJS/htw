//: C18:Stype.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// 
// Programm öffnet Datei und schickt Inhalt zur 
// Standardausgabe: stype stype.cpp

#include <fstream>
#include <iostream>
#include "require.h"
using namespace std;

void main(int argc, char* argv[]) {
  requireArgs(argc,  2); // Must have a command line
  ifstream in(argv[1]);
  assure(in, argv[1]); // Ensure file exists
  cout << in.rdbuf(); // Outputs entire file
} ///:~

/*
//: C18:Stype.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Type a file to standard output
#include <fstream>
#include <iostream>
#include "require.h"
using namespace std;

void main(int argc, char* argv[]) {
  requireArgs(argc,  2); // Must have a command line
  ifstream in(argv[1]);
  assure(in, argv[1]); // Ensure file exists
  cout << in.rdbuf(); // Outputs entire file
} ///:~
*/