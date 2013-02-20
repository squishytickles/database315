#include "Database.h"
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

string Record::getRawValue(int i){
	return values[i];
}

/* 	
	getting values:
	0: "string"
	1: "float"
	2: "int"
	3: "date"
*/
	
string Record::getStringValue(int i) {
	return values[i];
}

float Record::getFloatValue(int i) {
	stringstream ss;
	ss << record[i];
	float f;
	ss >> f;
	return f;
}

int Record::getIntValue(int i) {
	stringstream ss;
	ss << record[i];
	int iv;
	ss >> iv;
	return iv;
}

Date Record::getDateValue(int i) {
	stringstream ss;
	string date = record[i];
	replace(date.begin(), date.end(), '/', ' ');
	ss << date;
	int m, d, y;
	ss >> y >> m >> d;
	return Date(y,m,d);
}

string Record::operator[](int i) const{
	return values[i];
}

string & Record::operator[](int i){
	return values[i];
}
