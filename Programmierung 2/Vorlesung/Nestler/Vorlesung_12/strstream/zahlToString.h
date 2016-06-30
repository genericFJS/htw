/* strstream/zahlToString.h */
#ifndef ZAHLTOSTRING_H
#define ZAHLTOSTRING_H
#include<string>

std::string zahlToString(double d,
     unsigned int weite = 0,
     unsigned int format = 2,  // 0: fix, 1: scientific
                                  // sonst: automatisch
     unsigned int anzahlNachkommastellen = 4); // nur format 0/1

// ganze Zahlen:
std::string zahlToString(long i,          unsigned int weite = 0);
std::string zahlToString(int i,           unsigned int weite = 0);
std::string zahlToString(unsigned long i, unsigned int weite = 0);
std::string zahlToString(unsigned int i,  unsigned int weite = 0);

#endif
