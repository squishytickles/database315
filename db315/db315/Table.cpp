#include "Database.h"

using namespace std;

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
		if(attributesAndTypes[i].getAttribute().compare(originalName) == 0)
			attributesAndTypes[i].setAttribute(newName);
	}
}

float Table::sum(string attribute) {
	int i, valueAt = -1;
	float sum = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0) {
			valueAt = i;
			break;
		}
	}

	if (valueAt == -1)
		throw Database_exception("Could not find attribute to sum!");

	for (i = 0; i < records.size(); i ++) {

		if (records[i].getValue(valueAt).compare("") != 0) {
			sum += records[i].getFloatValue(valueAt);
		}
	}
	return sum;
}

int Table::count(string attribute) {
	int i, valueAt = -1;
	int sum = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0) {
			valueAt = i;
			break;
		}
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
	float min = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0) {
			valueAt = i;
			break;
		}
	}

	if (valueAt == -1)
		throw Database_exception("Could not find attribute to min!");

	// get first non-null initial min
	for (int j = 0; j < records.size(); j ++) {
		if (records[j].getFloatValue(valueAt) != 0) {
			min = records[j].getFloatValue(valueAt);
			break;
		}
	}

	// get the min
	for (i = 0; i < records.size(); i ++) {
		if (records[i].getFloatValue(valueAt) != 0) {
			if (records[i].getFloatValue(valueAt) < min)
				min = records[i].getFloatValue(valueAt);
		}
	}

	return min;

}

float Table::max(string attribute) {
	int i, valueAt = -1;
	float max = 0;

	for (i = 0; i < attributesAndTypes.size(); i ++) {
		if (attributesAndTypes[i].getAttribute().compare(attribute) == 0) {
			valueAt = i;
			break;
		}
	}

	if (valueAt == -1)
		throw Database_exception("Could not find attribute to min!");

	// get first non-null initial max
	for (int j = 0; j < records.size(); j ++) {
		if (records[j].getFloatValue(valueAt) != 0) {
			max = records[j].getFloatValue(valueAt);
			break;
		}
	}

	// get the max
	for (i = 0; i < records.size(); i ++) {
		if (records[i].getFloatValue(valueAt) != 0) {
			if (records[i].getFloatValue(valueAt) > max)
				max = records[i].getFloatValue(valueAt);
		}
	}

	return max;

}

Table Table::crossJoin(Table& otherTable) {
	// get the other tables attributes
	vector<AttributeTypeTuple> otherATTs = otherTable.getAttributes();
	vector<AttributeTypeTuple> myATTs = Table::getAttributes();
	vector<AttributeTypeTuple> newATTs;
	vector<Record> newRecords;

	for (int i = 0; i < myATTs.size(); i ++)
		newATTs.push_back(myATTs[i]);

	for (int j = 0; j < otherATTs.size(); j ++)
		newATTs.push_back(otherATTs[j]);

	for (int i = 0; i < Table::records.size(); i ++) {
		for(int j = 0; j < otherTable.getSize(); j ++) {
			vector<string> values;
			for (int k = 0; k < myATTs.size(); k ++)
				values.push_back(Table::records[i].getValue(k));
			for (int l = 0; l < otherTable.getSize(); l ++)
				values.push_back(otherTable[j].getValue(l));
			
			newRecords.push_back(Record(values));
		}
	}

	// create table with the new attributes
	Table crossed = Table(newATTs);

	// add my table's records
	for (int i = 0; i < newRecords.size(); i ++) {
		crossed.insert(newRecords[i]);
	}

	return crossed;
}

Record Table::operator[](int i) const{
	if (i < records.size())
		return records[i];
	else throw Database_exception("Table out of bounds!");
}		

Record & Table::operator[](int i){
	if (i < records.size())
		return records[i];
	else throw Database_exception("Table out of bounds!");
}
