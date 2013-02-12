#include "database.h"
#include <iostream>

using namespace std;

int main(){
	vector<string> v;
	v.push_back("A");
	v.push_back("B");
	v.push_back("C");
	v.push_back("D");
	Record r(v);
	
	cout<<r[0]<<endl;
	
	r[0] = "ahahah";
	
	cout<<r[0];
}
