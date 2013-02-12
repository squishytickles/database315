#include "database.h"

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
		if(attributesAndTypes[i].getAttribute() == attributeName){
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
		if(attributesAndTypes[i].getAttribute() == originalName)
			attributesAndTypes[i].setAttribute(newName);
	}
}
