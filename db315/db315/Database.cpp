#include "Database.h"

using namespace std;


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

Table Database::query(string queryCmd) {
	// split the query into the three appropriate parts
	int i = 0, locSELECT = -1, locFROM = -1, locWHERE = -1;
	while (i < queryCmd.length()) {
        if (queryCmd.substr(i,6).compare("SELECT") == 0 && locSELECT == 0)
            locSELECT = i + 6;
		if (queryCmd.substr(i,4).compare("FROM") == 0 && locFROM == 0) 
			locFROM = i + 5;
		if (queryCmd.substr(i,5).compare("WHERE") == 0 && locWHERE == 0)
			locWHERE = i + 6;
        
        i++;
	}
    
    if (locWHERE == -1)
        throw Database_exception("QUERY lacking a SELECT clause");

	if (locFROM == -1)
		throw Database_exception("QUERY lacking a FROM clause");

	// no where clause, this is ok, let's just set it to the end of the query
	if (locWHERE == -1)
		locWHERE = queryCmd.length();

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
	Table table = Table();
	Record record = Record();

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
			table = getTables()[i];
	}

	// convert the where clause into a list of tokens
	string whereClause = queryCmd.substr(locWHERE, queryCmd.length());
	ss << whereClause;
	while(ss >> token) tokens.push_back(token);

	// convert the list of tokens into a postfix expressinon
	for(int i=0; i<tokens.size(); i++)
	{
		if(tokens[i].compare("("))
			operators.push(tokens[i]);
		else if(tokens[i].compare(")"))
		{
			while(operators.top() != "(")
			{
<<<<<<< HEAD
				output.enqueue(operators.pop());
=======
				output.push(operators.top());
				operators.pop();
>>>>>>> bug fixes
			}
			operators.pop();
		}
		else if(tokens[i].compare("="))
			operators.push(tokens[i]);
		else if(tokens[i].compare(">"))
			operators.push(tokens[i]);
		else if(tokens[i].compare("<"))
			operators.push(tokens[i]);
		else if(tokens[i].compare("!="))
			operators.push(tokens[i]);
		else if(tokens[i].compare(">="))
			operators.push(tokens[i]);
		else if(tokens[i].compare("<="))
			operators.push(tokens[i]);
		else if(tokens[i].compare("&&"))
			operators.push(tokens[i]);
		else if(tokens[i].compare("||"))
			operators.push(tokens[i]);
		else if(tokens[i].compare("!"))
			operators.push(tokens[i]);
		else
		{
<<<<<<< HEAD
			token[i] = operand;
			output.enqueue(operand);
		}

		expression.push(output.dequeue());
=======
			tokens[i] = operand;
			output.push(operand);
		}

		expression.push(output.front());
		output.pop();
>>>>>>> bug fixes
	}

	//evaluate postfix expression
	while(!expression.empty())
	{
		if(expression.top() == operand)
			operation.push(operand);
		else
		{
			operand2 = operation.top();	// value
			operation.pop();
			operand1 = operation.top(); // attribute
			operation.pop();

			vector<AttributeTypeTuple> attrsAndNames = table.getAttributes();
			int typeVal;
			int	index = -1; 
			
			if((operand2 != "true") && (operation.top() != "false"))
			{			
				for(int i = 0; i < attrsAndNames.size(); i++)
				{
					if(attrsAndNames[i].getAttribute() == operand2)
					{
						typeVal = attrsAndNames[i].getTypeInt();
						index = i;
						break;
					}
				}
			}
			
			if(index = -1)
				throw Database_exception("Attribute type not found!");
			
			for(int i=0; i<table.getSize(); i++)
			{
				if(operation.top().compare("="))
				{
					switch(typeVal)
					{
						case 0:
						{
							string val = record.getStringValue(index);
							if(val.compare(operand1) == 0)
								operation.push("true");
							else
								operation.push("false");
						}
						break;
						case 1:
						{
							float val = record.getFloatValue(index);
							if(val == stringToFloat(operand1))
								operation.push("true");
							else
								operation.push("false");
						}
						break;
						case 2:
						{
							int val = record.getIntValue(index);
							if(val == stringToInt(operand1))
								operation.push("true");
							else
								operation.push("false");
						}
						break;
						case 3:
						{
							Date val = record.getDateValue(index);
							if(val.compare(stringToDate(operand1)) == 0)
								operation.push("true");
							else
								operation.push("false");
						}
						break;
					}
				}
				
				else if(operation.top().compare(">"))
				{
					switch(typeVal)
					{
						case 0:
						{
							string val = record.getStringValue(index);
							if(val.compare(operand1) > 0)
								operation.push("true");
							else
								operation.push("false");
						}
						break;
						case 1:
						{
							float val = record.getFloatValue(index);
							if(val > stringToFloat(operand1))
								operation.push("true");
							else
								operation.push("false");
						}
						break;
						case 2:
						{
							int val = record.getIntValue(index);
							if(val > stringToInt(operand1))
								operation.push("true");
							else
								operation.push("false");
						}
						break;
						case 3:
						{
							Date val = record.getDateValue(index);
							if(val.compare(stringToDate(operand1)) > 0)
								operation.push("true");
							else
								operation.push("false");
						}
						break;
					}
				}
				else if(operation.top().compare("<"))
				{
					switch(typeVal)
					{
						case 0:
						{
							string val = record.getStringValue(index);
							if(val.compare(operand1) < 0)
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 1:
						{
							float val = record.getFloatValue(index);
							if(val < stringToFloat(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 2:
						{
							int val = record.getIntValue(index);
							if(val < stringToInt(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 3:
						{
							Date val = record.getDateValue(index);
							if(val.compare(stringToDate(operand1)) < 0)
								operation.push("true");
							else
								operation.push("false");
							break;
						}
					}
				}
				else if(operation.top().compare("!="))
				{
					switch(typeVal)
					{
						case 0:
						{
							string val = record.getStringValue(index);
							if(val.compare(operand1) != 0)
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 1:
						{
							float val = record.getFloatValue(index);
							if(val != stringToFloat(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 2:
						{
							int val = record.getIntValue(index);
							if(val != stringToInt(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 3:
						{
							Date val = record.getDateValue(index);
							if(val.compare(stringToDate(operand1)) != 0)
								operation.push("true");
							else
								operation.push("false");
							break;
						}
					}
				}
				else if(operation.top().compare(">="))
				{
					switch(typeVal)
					{
						case 0:
						{
							string val = record.getStringValue(index);
							if((val.compare(operand1) > 0) || (val.compare(operand1) == 0))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 1:
						{
							float val = record.getFloatValue(index);
							if(val > stringToFloat(operand1) || val == stringToFloat(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 2:
						{
							int val = record.getIntValue(index);
							if(val > stringToInt(operand1) || val == stringToInt(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 3:
						{
							Date val = record.getDateValue(index);
							if((val.compare(stringToDate(operand1)) > 0) || (val.compare(stringToDate(operand1)) == 0))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
					}
				}
				else if(operation.top().compare("<="))
				{
					switch(typeVal)
					{
						case 0:
						{
							string val = record.getStringValue(index);
							if((val.compare(operand1) < 0) || (val.compare(operand1) == 0))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 1:
						{
							float val = record.getFloatValue(index);
							if(val < stringToFloat(operand1) || val == stringToFloat(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 2:
						{
							int val = record.getIntValue(index);
							if(val < stringToInt(operand1) || val == stringToInt(operand1))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
						case 3:
						{
							Date val = record.getDateValue(index);
							if((val.compare(stringToDate(operand1)) < 0) || (val.compare(stringToDate(operand1)) == 0))
								operation.push("true");
							else
								operation.push("false");
							break;
						}
					}
				}
				else if(operation.top().compare("&&"))
				{
					string val = record.getStringValue(index);
					if((val.compare("true") == 0) && (operand.compare("true") == 0))
						operation.push("true");
					else
						operation.push("false");		
				}
				else if(operation.top().compare("||"))
				{
					string val = record.getStringValue(index);
					if((val.compare("true") == 0) || (operand.compare("true") == 0))
						operation.push("true");
					else
						operation.push("false");		
				}
				else if(operation.top().compare("!"))
				{
					string val = record.getStringValue(index);
					if(val.compare("true") == 0)
						operation.push("false");
					else
						operation.push("true");		
				}
				else
					throw Database_exception("Unknown operand (known operands include: =, !=, <, >, <=, >=, &&, ||, !)");
			}
		}
	}
}

float Database::stringToFloat(string type)
{
	float floatVal;
	stringstream ss;
	ss << type;
	ss >> floatVal;
	return floatVal;
}

int Database::stringToInt(string type)
{
	int intVal;
	stringstream ss;
	ss << type;
	ss >> intVal;
	return intVal;
}

Date Database::stringToDate(string type)
{
	int m, d, y;
	stringstream ss;
	ss << type;
	ss >> d >> m >> y;
	return Date(y,m,d);
}





