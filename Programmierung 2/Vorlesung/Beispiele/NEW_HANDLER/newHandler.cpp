// A. Beck
// Beispiel zur Vorlesung PSP II


#include <iostream>
#include <new>
#include <cstdlib>

using namespace std;

void MemError (void)
{
	cout << "Not enough memory\n";
	exit (1);
}

int main()
{
  int *p[10];
  int i;
  set_new_handler(MemError);
  for (i=0; i<10;i++)
  {
     p[i]=new int[1024*1024*512];
     cout<<"p: "<<(void*) p[i]<<endl<<"ok"<<endl;
  }
  for (i=0; i<10;i++) delete[] p[i];
  return 0;
}
