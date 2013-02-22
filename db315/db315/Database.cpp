#include "Database.h"

using namespace std;


void Database::addTable(Table table, string tableName){
	table.setName(tableName);
	tables.push_back(table);
}

void Database::dropTable(string tableName){
	bool done = false;
	for(int i=0; i<tables.size(); ++i){
		if(tables[i].getName().compare(tableName) == 0) {
			tables.erase(tables.begin()+i);
			done = true;
		}
	}

	if (!done) throw Database_exception("No table to drop!");
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

vector<string> getOps() {
	vector<string> ops;
	ops.push_back("=");
	ops.push_back(">");
	ops.push_back("<");
	ops.push_back("!=");
	ops.push_back(">=");
	ops.push_back("<=");
	ops.push_back("&&");
	ops.push_back("||");
	ops.push_back("!");
	return ops;
}

void trimWS(string& str) {
	stringstream ss;
	ss << str;
	str.clear();
	ss >> str;
}

bool isOp(string token) {
	vector<string> ops = getOps();

	for (int i = 0; i < ops.size(); i ++) {
		if (ops[i].compare(token) == 0) return true;
	}

	return false;
}

bool isParens(string token) {
	if (token.compare("(") == 0 || token.compare(")") == 0) return true;
	else return false;
}

bool isBool(string token) {
	if (token.compare("true") == 0) return true;
	if (token.compare("false") == 0) return true;
	return false;
}

bool isSpecial(string token) {
	if (token.compare("&&") == 0 || token.compare("||") == 0) return true;
	else return false;
}

queue<string> expressionToPostfix(string exp) {
	vector<string> tokens;

	// first, put the exp into a vector of tokens
	stringstream ss;
	string token;
	ss << exp;
	while (ss >> token) {
		tokens.push_back(token);
		token.clear();
	}

	// read the tokens into postfix queue
	queue<string> output;
	stack<string> t_stack;

	for (int i = 0; i < tokens.size(); i ++) {
		token = tokens[i];

		if (!isOp(token) && !isParens(token)) {
			output.push(token);
		}
		else if (isOp(token) && !isParens(token)) {
			if (!t_stack.empty()) {
				if (t_stack.size() >= 2) {
					while (isOp(t_stack.top()) && !(isOp(token) && isSpecial(t_stack.top()))) {
							output.push(t_stack.top());
							t_stack.pop();
					}
				}
			}
			
			t_stack.push(token);
		}
		else if (isParens(token)) {
			if (token.compare("(") == 0) t_stack.push(token);
			else {
				while (t_stack.top().compare("(") != 0) {
					output.push(t_stack.top());
					t_stack.pop();
				}
				t_stack.pop();
			}
		}
	}

	while(!t_stack.empty()) {
		output.push(t_stack.top());
		t_stack.pop();
	}

	return output;
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

int lookupOp(string op, Table tableFrom) {
	for (int i = 0; i < tableFrom.getSize(); i ++) {
		if (tableFrom.getAttributes()[i].getAttribute().compare(op) == 0) return i;
	}

	throw Database_exception("Couldn't find a variable in the query [" + op + "]");
}

string evalE(string op1, string op2, Table tableFrom, Record record) {
	// lookup op1
	if (!isBool(op1)) {
		int i = lookupOp(op1, tableFrom);
		op1 = record.getValue(i);
	}
	// do operation
	if (op1.compare(op2) == 0) return "true";
	else return "false";
}
string evalG(string op1, string op2, Table tableFrom, Record record) {
	// lookup op1
	int i = lookupOp(op1, tableFrom);
	op1 = record.getValue(i);
	// do operation
	if (tableFrom.getAttributes()[i].getAttribute().compare("string") == 0) {
		if (op1.compare(op2) == 0) return "true";
		else return "false";
	}
	else {
		if (op1.compare(op2) > 0) return "true";
		else return "false";
	}
}
string evalL(string op1, string op2, Table tableFrom, Record record) {
	// lookup op1
	int i = lookupOp(op1, tableFrom);
	op1 = record.getValue(i);
	// do operation
	if (tableFrom.getAttributes()[i].getAttribute().compare("string") == 0) {
		if (op1.compare(op2) == 0) return "true";
		else return "false";
	}
	else {
		if (op1.compare(op2) < 0) return "true";
		else return "false";
	}
}
string evalNE(string op1, string op2, Table tableFrom, Record record) {
	// lookup op1
	if (!isBool(op1)) {
		int i = lookupOp(op1, tableFrom);
		op1 = record.getValue(i);
	}
	// do operation
	if (op1.compare(op2) != 0) return "true";
	else return "false";
}
string evalGE(string op1, string op2, Table tableFrom, Record record) {
	// lookup op1
	int i = lookupOp(op1, tableFrom);
	op1 = record.getValue(i);
	// do operation
	if (tableFrom.getAttributes()[i].getAttribute().compare("string") == 0) {
		if (op1.compare(op2) == 0) return "true";
		else return "false";
	}
	else {
		if (op1.compare(op2) > 0) return "true";
		if (op1.compare(op2) == 0) return "true";
		return "false";
	}
}
string evalLE(string op1, string op2, Table tableFrom, Record record) {
	// lookup op1
	int i = lookupOp(op1, tableFrom);
	op1 = record.getValue(i);
	// do operation
	if (tableFrom.getAttributes()[i].getAttribute().compare("string") == 0) {
		if (op1.compare(op2) == 0) return "true";
		else return "false";
	}
	else {
		if (op1.compare(op2) < 0) return "true";
		if (op1.compare(op2) == 0) return "true";
		return "false";
	}
}
string evalA(string op1, string op2, Table tableFrom, Record record) {
	if (op1.compare(op2) == 0 && op1.compare("true") == 0) return "true";
	else return "false";
}
string evalO(string op1, string op2, Table tableFrom, Record record) {
	if (op1.compare("true") == 0 || op2.compare("true") == 0) return "true";
	else return "false";
}

void printStack(stack<string> s) {
	cout << "CURRENT STACK" << endl;
	while(!s.empty()) {
		cout << s.top() << endl;
		s.pop();
	}
}

void printQueue(queue<string> d) {
	cout << "CURRENT QUEUE" << endl;
	while(!d.empty()) {
		cout << d.front() << endl;
		d.pop();
	}
	cout << endl;
}

Table Database::query(string queryCmd) {
	// create necessary tables
	Table returnTable = Table();
	Table tableFrom = Table();

	// get the indicies of the starting positions of the three parts of the query
	int select_i = -1, from_i = -1, where_i = -1;

	for (int i = 0; i < queryCmd.length(); i ++) {
		if (queryCmd.substr(i,6).compare("SELECT") == 0) select_i = i + 6;
		if (queryCmd.substr(i,4).compare("FROM") == 0) from_i = i + 4;
		if (queryCmd.substr(i,5).compare("WHERE") == 0) where_i = i + 5;
	}

	// build a string vector of the attributes to return
	string attrTemp = "";
	vector<string> attrStrings;
	for (int i = select_i; i < from_i - 4; i ++) {
		if (queryCmd.substr(i,1).compare(",") != 0) attrTemp += queryCmd.substr(i,1);
		if (queryCmd.substr(i,1).compare(",") == 0 || i == from_i - 4 - 1) {
			trimWS(attrTemp);
			attrStrings.push_back(attrTemp);
			attrTemp = "";
		}
	}

	// get the table to select from
	string tableFromName = queryCmd.substr(from_i + 1, where_i - 5 - from_i - 2);
	bool found = false;
	for (int i = 0; i < getTables().size(); i ++) {
		if (getTables()[i].getName().compare(tableFromName) == 0) {
			tableFrom = Table(getTables()[i]);
			found = true;
		}
	}
	if (!found) throw Database_exception("Couldn't find the table specified [" + tableFromName + "]");

	// put those attributes in returnTable
	for (int i = 0; i < tableFrom.getAttributes().size(); i ++) {
		returnTable.add(tableFrom.getAttributes()[i]);
	}

	// remove unessecary attributes
	for (int i = 0; i < returnTable.getAttributes().size(); i ++) {
		bool goodAttr = false;
		for (int j = 0; j < attrStrings.size(); j ++) {
			if (returnTable.getAttributes()[i].getAttribute().compare(attrStrings[j]) == 0 || attrStrings[0].compare("*") == 0) goodAttr = true;
		}

		if (!goodAttr) returnTable.deleteATT(returnTable.getAttributes()[i].getAttribute());
	}

	// at this point, returnTable has the correct aTTs, and fromTable is the table we're selecting from

	// convert the where clause into postfix
	string exp = queryCmd.substr(where_i + 1,queryCmd.length() - where_i);
	queue<string> postfix = expressionToPostfix(exp);

	// for each record, evaluate the postfix exp for it's values, then add it to the returnTable if it's true
	for (int i = 0; i < tableFrom.getSize(); i ++) {
		cout << "TESTING RECORD " << i << " _______________________________" <<  endl;

		Record testRecord = tableFrom[i];
		queue<string> testPostfix = postfix;
		stack<string> t_stack;



		cout << "RECORD " << endl;
		for (int j = 0; j < tableFrom.getAttributes().size(); j ++) {
			cout << "[" << testRecord.getValue(j) << "] ";
		} cout << endl;


		printQueue(testPostfix);

		while (!testPostfix.empty()) {
			printStack(t_stack);
			string token = testPostfix.front();
			testPostfix.pop();
			
			// if its a value, move it to the stack
			if (!isOp(token)) t_stack.push(token);

			// its an operator, pop off two values and evaluate them
			else {
				string op2 = t_stack.top();
				t_stack.pop();
				string op1 = t_stack.top();
				t_stack.pop();

				cout << "COMP " << op1 << " AND " << op2 << endl;

				// evaluate
				if (token.compare("=") == 0) {
					t_stack.push(evalE(op1,op2, tableFrom, testRecord)); cout << "=" << endl;
				} else if (token.compare(">") == 0) {
					t_stack.push(evalG(op1,op2, tableFrom, testRecord)); cout << ">" << endl;
				} else if (token.compare("<") == 0) {
					t_stack.push(evalL(op1,op2, tableFrom, testRecord)); cout << "<" << endl;
				} else if (token.compare("!=") == 0) {
					t_stack.push(evalNE(op1,op2, tableFrom, testRecord)); cout << "!=" << endl;
				} else if (token.compare(">=") == 0) {
					t_stack.push(evalGE(op1,op2, tableFrom, testRecord)); cout << ">=" << endl;
				} else if (token.compare("<=") == 0) {
					t_stack.push(evalLE(op1,op2, tableFrom, testRecord)); cout << "<=" << endl;
				} else if (token.compare("&&") == 0) {
					t_stack.push(evalA(op1,op2, tableFrom, testRecord)); cout << "&&" << endl;
				} else if (token.compare("||") == 0) {
					t_stack.push(evalO(op1,op2, tableFrom, testRecord)); cout << "||" << endl;
				} else throw Database_exception("OH NO NOT ENOUGH SKITTLES");
			}
		}

		// if true remains, then the record is true and can be added to the returnTable
		if (t_stack.top().compare("true") == 0) {
			returnTable.insert(testRecord);
		}

	}

	cout << "SIZE " << returnTable.getSize() << endl;
	return returnTable;

}