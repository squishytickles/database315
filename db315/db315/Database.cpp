#include "Database.h"


void Database::addTable(Table table, string tableName){
	table.setName(tableName);
	tables.push_back(table);
}

void Database::dropTable(string tableName){
	for(int i=0; i<tables.size(); ++i){
		if(tables[i].getName().compare(tableName) == 0)
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

Table query(string queryCmd) {
	// split the query into the three appropriate parts
	int i = 0, locFROM = -1, locWHERE = -1;
	while (i<queryCmd.length) {
		if (queryCmd.substr(i,4) == "FROM" && locFROM == 0) 
			locFROM = i;
		if (queryCmd.substr(i,5) == "WHERE" && locWHERE == 0) 
			locWHERE = i;
	}

	if (locFROM = -1)
		throw Database_exception("QUERY lacking a FROM clause");
