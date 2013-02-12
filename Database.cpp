#include "database.h"


void Database::addTable(Table table, string tableName){
	table.setName(tableName);
	tables.push_back(table);
}

void Database::dropTable(string tableName){
	for(int i=0; i<tables.size(); ++i){
		if(tables[i].getName() == tableName)
			tables.erase(tables.begin()+i);
	}
}

vector<string> Database::listTables(){
	vector<string> names;
	
	for(int i=0; i<tables.size(); ++i){
		names.push_back(tables[i].getName());
	}
	
	return names;
}

vector<Table> Database::getTables(){
	return tables;
}
