// refdem10 - Referenzen und Feldelemente

#include <iostream>
using namespace std;

auto main() -> void
{
  int feld[14], (&f)[14]=feld, &f10=f[10];
  
  for(int i=0;i<sizeof f/sizeof i;f[i]=i++);
  f10=100;
  for(int i=0; i<sizeof f/sizeof i; cout<<"f["<<i<<"]="<<f[i]<<endl, i++);
  cin.get();
}

/*
f[0]=0
f[1]=1
f[2]=2
f[3]=3
f[4]=4
f[5]=5
f[6]=6
f[7]=7
f[8]=8
f[9]=9
f[10]=100
f[11]=11
f[12]=12
f[13]=13
*/







