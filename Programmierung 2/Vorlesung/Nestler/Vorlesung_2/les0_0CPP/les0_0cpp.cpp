#include <iostream>

using namespace std;

auto main() -> int {
  auto x=1.5;
  cout<<"double x="<<x<<'\n';
  cout<<"int    x="<<int(x)<<endl;  // cast: x=1
  cin.get();
  return 0;
}