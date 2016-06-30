#include <iostream>
#include <string>
using namespace std;
auto main() -> void {
	string *ps = new string();
	*ps = "HTW_Dresden_2016";
	cout<<"*ps = "<<*ps<<endl;
	string s;
	cout<<"s.length = "<<s.length()<<'\n';
	s+="HTW";
	cout<<"s = "<<s<<'\n';
	s.append(" Dresden");

	//char u[10]; s.copy(u, 2,4); u[2]='\0'; //veraltet
	//cout<<"u = "<<u<<endl;

	string v=s.substr(2,4); cout<<"v = "<<v<<endl; //OK
	cout<<"s.size = "<<s.size()<<'\n';
	cout<<"s.capacity() = "<<s.capacity()<<endl;
	cout<<"s = "<<s<<'\n';
    cout<<"s.length = "<<s.length()<<'\n';
	
	s.erase(s.begin()+1, s.end()-2); cout<<"s = "<<s<<'\n';
	s.insert(1,"TW Dresd"); cout<<"s = "<<s<<'\n';

	s.push_back('2'); s.append("016"); cout<<"s = "<<s<<'\n';
	size_t st = s.find("2016");

	if(st != string::npos)
	      cout<<"s.find(""2016"") = "<<s.find("2016")<<endl;

    s.replace(s.find("2016"),4,"1999"); 
	cout<<"s = "<<s<<'\n';

	s.erase(11,4);
	cout<<"s.substr(0,3) = "<<s.substr(0,3)<<endl;

	s[0]='_'; s.at(0)='H';
	cout<<"s = "<<s<<'\n';
	const char *sc = s.c_str(); 
	cout<<"sc = "<<sc<<"  strlen(sc) = "<<strlen(sc)<<endl;
	const char *tc = s.data();
	cout<<"tc = "<<tc<<endl;
	s.assign("TU"); //s="TU";
	string t = "TU";
	cout<<"s.compare(t) = "<<s.compare(t)<<endl;
	s.swap(t);
	s.clear();
	if(s.empty()) cout<<"s leer\n";	
	cout<<"s = "<<s<<'\n';
	string s1="s1", s2="s2";
	s1.swap(s2);
	cout<<"s1 = "<<s1<<"   s2 = "<<s2<<endl;
	cin.ignore();
}

/*
*ps = HTW_Dresden_2016
s.length = 0
s = HTW
v = W Dr
s.size = 11
s.capacity() = 15
s = HTW Dresden
s.length = 11
s = Hen
s = HTW Dresden
s = HTW Dresden2016
s.find(2016) = 11
s = HTW Dresden1999
s.substr(0,3) = HTW
s = HTW Dresden
sc = HTW Dresden  strlen(sc) = 11
tc = HTW Dresden
s.compare(t) = 0
s leer
s =
s1 = s2   s2 = s1
*/