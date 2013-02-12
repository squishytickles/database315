#include "database.h"
#include <iostream>

Record::Record(vector<string> value){
	values = value;
}

Record::~Record(){
	
}

void Record::addValue(string t){
	values.push_back(t);
}

void Record::removeValue(int i){
	values.erase(values.begin()+i);
}

string Record::getValue(int i){
	return values[i];
}

string Record::operator[](int i) const{
	return values[i];
}

string & Record::operator[](int i){
	return values[i];
}
