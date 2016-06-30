#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;
#include "str.h"

int main()
{
  myStr *s1=new myStr("Hans Huckebein");
  s1->display();
  cout<<endl;
  return 0;
}