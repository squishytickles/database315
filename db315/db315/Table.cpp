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
	int min = 0;

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
	int max = 0;

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

	// create a list of aTTs for the new table, philter out diplicates
	for (int i=0; i<otherATTs.size(); i++) {
		for (int j=0; j<myATTs.size(); j++) {
			if (newATTs[j].compare(otherATTs[i]) == 0) {
				newATTs.push_back(myATTs[j]);

				Record newRecord = Record();
				for (int k = 0; k < Table::getSize(); k ++) {
					newRecord.addValue(Table::records[j].getValue(j));
				}

				newRecords.push_back(newRecord);
			}
		}
		newATTs.push_back(otherATTs[i]);

		Record newRecord = Record();
		for (int k = 0; k < otherTable.getSize(); k ++) {
			newRecord.addValue(otherTable[k].getValue(i));
		}

		newRecords.push_back(newRecord);
	}

	// create table with the new attributes
	Table crossed = Table(newATTs);

	// add my table's records
	for (int i = 0; i < newRecords.size(); i ++)
		crossed.insert(newRecords[i]);

	return crossed;
}

Record Table::operator[](int i) const{
	return records[i];
}		

Record & Table::operator[](int i){
	return records[i];
}
