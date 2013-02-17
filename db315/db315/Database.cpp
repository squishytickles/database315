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
		if (queryCmd.substr(i,4).compare("FROM") == 0 && locFROM == 0) 
			locFROM = i + 5;
		if (queryCmd.substr(i,5).compare("WHERE") == 0 && locWHERE == 0) 
			locWHERE = i + 6;
	}

	if (locFROM = -1)
		throw Database_exception("QUERY lacking a FROM clause");
	
	// no where clause, this is ok, let's just set it to the end of the query
	if (locWHERE = -1)
		locWHERE = queryCmd.length;

	// contains all the tables to be selected from, or "*"
	vector<string> tablesFROM;

	string tableTemp = "";
	for (i = locFROM; i < locWHERE - 6; i ++) {
		if (queryCmd.substr(i,1).compare(",") != 0) {
			// add a letter
			tableTemp += queryCmd.substr(i,1);
		} else {
			// push it back and restart
			tablesFROM.push_back(tableTemp);
			tableTemp = "";
		}
	}

	// need to get the WHERE string and parse it
}