// string_op_ne.cpp
// compile with: /EHsc
#include <string>
#include <iostream>

auto main( ) -> int {
   using namespace std;

   // Declaring an objects of type basic_string<char>
   string s1 ( "HTW" );
   string s2 ( "Informatik" );
   cout << "The basic_string s1 = " << s1 << "." << endl;
   cout << "The basic_string s2 = " << s2 << "." << endl;

   // Declaring a C-style string
   char *s3 = "Dresden";
   cout << "The C-style string s3 = " << s3 << "." << endl;
   
   const char *s4 = s1.c_str(); // Umwandlung string --> char *
   cout<<"s4 = "<<s4<<endl;
   cout<<"s4 = "<<(void *)s4<<"  &s1 = "<<&s1<<endl;

   char *s5 = strcpy(new char[s1.length()+1],s1.data());
   cout<<"s5 = "<<s5<<endl;

   string s7; s7.clear(); s7+=s5; cout<<"s7 = "<<s7<<endl; 
	
   // First member function: comparison between left-side object
   // of type basic_string & right-side object of type basic_string
   if ( s1 != s2 )
      cout << "The strings s1 & s2 are not equal." << endl;
   else
      cout << "The strings s1 & s2 are equal." << endl;

   // Second member function: comparison between left-side object
   // of type basic_string & right-side object of C-syle string type
   if ( s1 != s3 )
      cout << "The strings s1 & s3 are not equal." << endl;
   else
      cout << "The strings s1 & s3 are equal." << endl;

   // Third member function: comparison between left-side object
   // of C-syle string type & right-side object of type basic_string
   if ( s3 != s2 )
      cout << "The strings s3 & s2 are not equal." << endl;
   else
      cout << "The strings s3 & s2 are equal." << endl;
   cin.get();
}