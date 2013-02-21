#include "Database.h"

string AttributeTypeTuple::getAttribute(){
	return attribute;
}

void AttributeTypeTuple::setAttribute(string newName){
	attribute = newName;
}

string AttributeTypeTuple::getType(){
	return type;
}

int AttributeTypeTuple::getTypeInt(){
	/* 	
		for use by query fcns in database:
		0: "string"
		1: "float"
		2: "int"
		3: "date"
	*/
	if (type.compare("string") == 0) 	return 0;
	else if (type.compare("float") == 0)	return 1;
	else if (type.compare("int") == 0)	return 2;
	else if (type.compare("date") == 0)	return 3;
	
	// throw an exception if there is an invalid type stored
	throw Database_exception("Unknown type stored in AttributeTypeTuple!");
}
