// string_wstring.cpp
// compile with: /EHsc
#include <string>
#include <iostream>

auto main( ) -> int
{
   using namespace std;
   // Equivalent ways to declare an object of type
   // basic_string <wchar_t>
   const basic_string <wchar_t> s1 ( L"abc" );
   wstring s2 ( L"abc" );   // Uses the typedef for wstring

   // Comparison between two objects of type basic_string <wchar_t>
   if ( s1 == s2 )
      cout << "The strings s1 & s2 are equal." << endl;
   else
      cout << "The strings s1 & s2 are not equal." << endl;
   cin.get();
}