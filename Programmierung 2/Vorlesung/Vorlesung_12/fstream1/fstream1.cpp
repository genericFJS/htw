#include <iostream>
#include <fstream>

using namespace std;

void main()		//fstream1.cpp
{
    fstream FS;
    int i;

    // schreiben
    FS.open("fstream1.dat", ios::out);
	if(!FS){
		cout<<"fstream1.dat nicht geoeffnet\n"<<endl;
		exit(-1);
	}

    for(i = 0; i < 9; ++i)
      FS << i << endl;

	filebuf *fb = FS.rdbuf();
	cout<<"Adresse Filepuffer FS = "<<hex<<(unsigned long)(fb)<<endl;

    FS.close();

    // lesen
    FS.open("fstream1.dat", ios::in);

    while(FS && !FS.eof())
    {
       FS >> i;
       if(!FS.eof())
          cout << i << ' ';
    }
    cout << endl;
	cin.ignore();
}

//  0 1 2 3 4 5 6 7 8