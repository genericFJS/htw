/* strstream/zahlToString.cpp */
#include<sstream>
#include<iostream>
#include"zahlToString.h"

std::string zahlToString(double d, unsigned int weite,
                         unsigned int format,                    // 0: fix, 1: scientific, sonst: automatisch
                         unsigned int anzahlNachkommastellen ) { // nur Format 0/1
   std::ostringstream wandler;
   if(format == 0) {
      wandler.setf(std::ios::fixed, std::ios::floatfield);
      if(anzahlNachkommastellen > 0) {
         wandler.setf(std::ios::showpoint);
      }
   }
   else {
      if(format == 1) {
         wandler.setf(std::ios::scientific, std::ios::floatfield);
      }
   }
   if(format == 0 || format == 1) {
      wandler.precision(anzahlNachkommastellen);
   }
   if(weite > 0) {
      wandler.width(weite);
   }
   wandler << d << std::ends;   // Zahl und abschließendes Nullzeichen in den Strom einfügen
   return wandler.str();
}

std::string zahlToString(long i, unsigned int weite) {
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}
std::string zahlToString(int i, unsigned int weite) {
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}
std::string zahlToString(unsigned long i, unsigned int weite) {
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}
std::string zahlToString(unsigned int i, unsigned int weite) {
   return zahlToString(static_cast<double>(i), weite, 0, 0);
}

