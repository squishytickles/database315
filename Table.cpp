#include "database.h"

Table::~Table(){

}

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

int Table::count(string attribute){
	int index, count;
	
	for(int i=0; i<attributesAndTypes.size(); ++i){
		if(attributesAndTypes[i].getAttribute() == attribute)
			index = i;
	}
	
	for(int i=0; i<records.size(); ++i){
		if(records[i][index] != "")
			++count;
	}
	
	return count;
}

/*
int sum(string attribute);
int count(string attribute);
int min(string attribute);
int max(string attribute);
*/

Record Table::operator[](int i) const{
	return records[i];
}		


Record & Table::operator[](int i){
	return records[i];
}
