#include "database.h"

string AttributeTypeTuple::getAttribute(){
	return attribute;
}

void AttributeTypeTuple::setAttribute(string newName){
	attribute = newName;
}

string AttributeTypeTuple::getType(){
	return type;
}
