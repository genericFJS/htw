//: C18:Sbufget.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Get directly into a streambuf
#include <fstream>
#include <iostream>
#include "require.h"
using namespace std;

void main() {
  ifstream in("Sbufget.cpp");
  assure(in, "Sbufget.cpp");
  while(in.get(*cout.rdbuf())){
        in.ignore(); cout<<'\n';
  }
} ///:~

/*
//: C18:Sbufget.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Get directly into a streambuf
#include <fstream>
#include <iostream>
#include "require.h"
using namespace std;
Press any key to continue
*/