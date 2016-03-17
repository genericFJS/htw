// basic_string.cpp
// compile with: /EHsc
#include <string>
#include <iostream>

auto main( ) -> int {
   using namespace std;

   // Equivalent ways to declare an object 
   // of type basic_string <char>
   const basic_string <char> s1 ( "test" );
   string s2 ( "test" );   // Uses the typedef for string

   // comparison between two objects of type basic_string
   if ( s1 == s2 )
      cout << "The strings s1 & s2 are equal." << endl;
   else
      cout << "The strings s1 & s2are not equal." << endl;
   cin.get();
}