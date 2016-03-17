#include <iostream>
#include <vector>
using namespace std;

auto main() -> int {
	auto n=0U;
	cout<<"n = "; cin>>n; cin.clear(); cin.ignore(INT_MAX, '\n');
    vector<double> p(n);  //Dynamischer Vektor
	auto i=3U;
	(i<p.size())?p[i]=3.3:i;
	if(i>=p.size())
		cout<<"Index "<<i<<" unerlaubt\n";
	else
		cout<<"Index "<<i<<" erlaubt\n";
	cout<<"p["<<i<<"] = "<<((i<p.size())?p[i]:0.0)<<endl;
	cin.get();
}