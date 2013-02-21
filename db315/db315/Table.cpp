#include "Database.h"

string Table::getName(){
	return name;
}

void Table::setName(string n){
	name = n;
}

void Table::add(AttributeTypeTuple aTT){
	attributesAndTypes.push_back(aTT);
}

void Table::deleteATT(string attributeName){

	for(int i=0; i<attributesAndTypes.size(); ++i){
		if(attributesAndTypes[i].getAttribute().compare(attributeName) == 0){
			attributesAndTypes.erase(attributesAndTypes.begin() + i);
		}
	}
}

void Table::insert(Record record){
	records.push_back(record);
}

vector<AttributeTypeTuple> Table::getAttributes(){
	return attributesAndTypes;
}

int Table::getSize(){
	return records.size();
}

void Table::rename(string originalName, string newName){
	for(int i=0; i<attributesAndTypes.size(); ++i){
		if(attributesAndTypes[i].getAttribute().compare(originalName))
			attributesAndTypes[i].setAttribute(newName);
	}
}

float Table::sum(string attribute) {
	int i, valueAt = -1;
	float sum = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0)
			valueAt = -1;
	}

	if (valueAt == -1)
		throw Database_exception("Could not find attribute to sum!");

	for (i = 0; i < records.size(); i ++) {
		stringstream ss;
		float toSum;

		if (records[i].getValue(valueAt).compare("") != 0) {
			ss << records[i].getValue(valueAt);
			ss >> toSum;
			sum += toSum;
		}
	}
	return sum;
}

int Table::count(string attribute) {
	int i, valueAt = -1;
	int sum = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0)
			valueAt = -1;
	}

	if (valueAt == -1)
		throw Database_exception("Could not find attribute to sum!");

	for (i = 0; i < records.size(); i ++) {
		stringstream ss;
		float toSum;

		if (records[i].getValue(valueAt).compare("") != 0) {
			ss << records[i].getValue(valueAt);
			ss >> toSum;
			sum += toSum;
		}
	}

	return sum;

}

float Table::min(string attribute) {
	int i, valueAt = -1;
	int min = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0)
			valueAt = -1;
	}

	if (valueAt == -1)
		throw Database_exception("Could not find attribute to min!");

	for (i = 0; i < records.size(); i ++) {
		stringstream ss;
		float toMin;

		if (records[i].getValue(valueAt).compare("") != 0) {
			ss << records[i].getValue(valueAt);
			ss >> toMin;

			if (toMin < min)
				min = toMin;
		}
	}

	return min;

}

float Table::max(string attribute) {
	int i, valueAt = -1;
	int max = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0)
			valueAt = -1;
	}

	if (valueAt == -1)
		throw Database_exception("Could not find attribute to max!");

	for (i = 0; i < records.size(); i ++) {
		stringstream ss;
		float toMax;

		if (records[i].getValue(valueAt).compare("") != 0) {
			ss << records[i].getValue(valueAt);
			ss >> toMax;

			if (toMax > max)
				max = toMax;
		}
	}

	return max;

}

Table Table::crossJoin(Table& otherTable) {
	// create table with half the attributes
	Table crossed = Table(Table::getAttributes());
	
	// get the other tables attributes
	vector <AttributeTypeTuple> otherATTs = otherTable.getAttributes();
	vector <AttributeTypeTuple> myATTs = Table::getAttributes();
	vector <AttributeTypeTuple> newATTs;

	for(int i=0; i<otherATTs.size(); i++) {
		for(int j=0; j<myATTs.size(); j++) {
			if (otherATTs[i].compare(myATTs[i]) == 0) {
				newATTs.push_back(myATTs[j]);
			else
			{
				newATTs.push_back(myATTs[j]);
				newATTs.push_back(otherATTs[i]);
			}
		}
	}

	// add all the other tables attributes
	for (int i = 0; i < otherATTs.size(); i ++) {
		crossed.add(otherATTs[i]);
	}

	// add the new records
	for (int i = 0; i < otherTable.getSize(); i ++) {
		crossed.insert(otherTable[i]);
	}

	return crossed;
}

Record Table::operator[](int i) const{
	return records[i];
}		

Record & Table::operator[](int i){
	return records[i];
}
