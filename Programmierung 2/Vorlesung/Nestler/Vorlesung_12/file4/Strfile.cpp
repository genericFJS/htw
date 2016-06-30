//: C18:Strfile.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Stream I/O with files
// The difference between get() & getline()
#include <fstream>  
#include <iostream>
#include "require.h"
using namespace std;

void main() {
  const int sz = 100; // Buffer size;
  char buf[sz];
  {
    ifstream in("Strfile.cpp"); // Read
    assure(in, "Strfile.cpp"); // Verify open
    ofstream out("Strfile.out"); // Write
    assure(out, "Strfile.out");
    int i = 1; // Line counter

    // A less-convenient approach for line input:
    while(in.get(buf, sz)) { // Leaves \n in input
      in.get(); // Throw away next character (\n)
      cout << buf << endl; // Must add \n
      // File output just like standard I/O:
      out << i++ << ": " << buf << endl;
    }
  } // Destructors close in & out

  ifstream in("Strfile.out");
  assure(in, "Strfile.out");
  // More convenient line input:
  while(in.getline(buf, sz)) { // Removes \n
    char* cp = buf;
    while(*cp != ':')
      cp++;
    cp += 2; // Past ": "
    cout << cp << endl; // Must still add \n
  }
} ///:~

/*
//: C18:Strfile.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Stream I/O with files
// The difference between get() & getline()
#include <fstream>
#include <iostream>
#include "require.h"
using namespace std;
//: C18:Strfile.cpp
// From Thinking in C++, 2nd Edition
// Available at http://www.BruceEckel.com
// (c) Bruce Eckel 1999
// Copyright notice in Copyright.txt
// Stream I/O with files
// The difference between get() & getline()
#include <fstream>
#include <iostream>
#include "require.h"
using namespace std;
Press any key to continue
*/