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
	int i = 0, loc SELECT = -1, locFROM = -1, locWHERE = -1;
	while (i<queryCmd.length) {
        if (queryCmd.substr(i,6).compare("SELECT") == 0 && locSELECT == 0)
            locSELECT = i + 6;
		if (queryCmd.substr(i,4).compare("FROM") == 0 && locFROM == 0) 
			locFROM = i + 5;
		if (queryCmd.substr(i,5).compare("WHERE") == 0 && locWHERE == 0)
			locWHERE = i + 6;
        
        i++;
	}
    
    if (locWHERE = -1)
        throw Database_exception("QUERY lacking a SELECT clause");

	if (locFROM = -1)
		throw Database_exception("QUERY lacking a FROM clause");
	
	// no where clause, this is ok, let's just set it to the end of the query
	if (locWHERE = -1)
		locWHERE = queryCmd.length;

	// contains all the attributes to be selected from, or "*"
	vector<string> attrsSELECT;

	string attrTemp = "";
	for (i = locSELECT; i < locFROM - 6; i ++) {
		if (queryCmd.substr(i,1).compare(",") != 0) {
			// add a letter
			attrTemp += queryCmd.substr(i,1);
		} else {
			// push it back and restart
			attrsSELECT.push_back(attrTemp);
			attrTemp = "";
		}
	}

	// need to get the table to select FROM
    string tableFROM = "";
    
    for (i = locFROM; i < locWHERE; i ++) {
        if (queryCmd.substr(i,1).compare(",") != 0)
            break;
        else
            tableFROM += string(queryCmd.substr(i,1));
    }
    
    // need to parse WHERE clause, using a stack and a mini lang evalulator like last year
    //REMEBER TO INCLUDE <stack.h> IN MAIN!
	vector<Table> tables = getTables();
	Table table;
	Record record;

	stringstream ss;
	string token;
	string operand, operand1, operand2;
	vector<string> tokens;
	queue<string> output;
	stack<string> operators;
	stack<string> expression;
	stack<string> operation;

	// find the correct table that we'll be querying
	for(int i = 0; i < tables.size(); i++)
	{
		if(tables[i].getName().compare(tableFROM))
			table = getTables[i];
	}

	// convert the where clause into a list of tokens
	string whereClause = queryCmd.substr(locWHERE, strlen(queryCmd));
	ss << whereClause;
	while(ss >> token) tokens.push_back(token);

	// convert the list of tokens into a postfix expressinon
	for(int i=0; i<tokens.size(); i++)
	{
		if(token[i].compare("("))
	
		else if(token[i].comapre(")"))
		{
			while(operators.top() != "(")
			{
				output.push(operators.pop());
			}
			operators.pop();
		}
		else if(token[i].compare("="))
			operators.push(token[i]);
		else if(token[i].compare(">"))
			operators.push(token[i]);
		else if(token[i].compare("<"))
			operators.push(token[i]);
		else if(token[i].compare("!="))
			operators.push(token[i]);
		else if(token[i].compare(">="))
			operators.push(token[i]);
		else if(token[i].compare("<="))
			operators.push(token[i]);
		else if(token[i].compare("&&"))
			operators.push(token[i]);
		else if(token[i].compare("||"))
			operators.push(token[i]);
		else if(token[i].compare("!"))
			operators.push(token[i]);
		else
		{
			token[i] = operand;
			output.push(operand);
		}

		expression.push(output.pop());
	}

	//evaluate postfix expression
	while(!expression.empty())
	{
		if(expression.top() = operand)
			operation.push(operand);
		else
		{
			operand2 = operation.top();
			operation.pop();
			operand1 = operation.top();
			operation.pop();
			
			vector<AttributeTypeTuple> typeandvalue = table.getAttributes;

			if(operation.top().compare("=")
			{

			}
		}
	}

}
