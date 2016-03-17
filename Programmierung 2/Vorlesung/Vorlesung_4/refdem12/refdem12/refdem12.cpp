#include <iostream>
using namespace std;

auto main() -> void {
	auto ivar = 2,
		&iref = ivar, 
		* const iptr = &iref; 
            
	cout<<"ivar = "
		<< (*iptr)++
		<<"\niref = "
		<<++iref
		<<endl;
 }
// ivar = 3 iref = 4