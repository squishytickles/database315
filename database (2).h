/*
 * Authors: 	Graham Leslie, Sarah Vance, Ryan Finke
 * Date:		1/31/2013
 * Desc:		Header file for the database project
 */
 
 using namespace std;
 
#ifndef _DATABASE_H
#define _DATABASE_H
 
 /** INCLUDES **/
 
#include <vector>
#include <exception>
#include <stdexcept>

  
/** MAIN CLASSES **/

class Record;
class AttributeTypeTuple;
class Table;

class Database
{
private:
	// members
	vector<Table> tables;
	
public:
	// constructor
	Database();
	~Database();
	
	// functions
	void addTable(Table table, string tableName);
	void dropTable(string tableName);
	vector<string> listTables();						// returns names of tables
	vector<Table> getTables();						// returns actual tables
	Table query(string queryCmd);
	void deleteQuery(string querycmd);					// opposite of query()
};

class Table
{
private:
	// members
	string name;
	vector<Record> records;								// has list of records
	vector<AttributeTypeTuple> attributesAndTypes;	// also has list of its aTTs for records
	
public:
	// constructor
	Table();
	Table(vector<AttributeTypeTuple> aTTs): attributesAndTypes(aTTs) { }
	~Table();
	
	// functions
	void getName();
	void add(AttributeTypeTuple aTT);
	void deleteATT(string attributeName);
	void insert(Record record);
	vector<AttributeTypeTuple> getAttributes();
	int getSize();
	void rename(string originalName, string newName);
	int sum(string attribute);
	int count(string attribute);
	int min(string attribute);
	int max(string attribute);
	Table crossJoin(Table& otherTable);
	
	Record operator[](int i) const;		// iterate through records
    Record & operator[](int i);			// iterate through records
	
};

class Record
{
private:
	// members
	vector<string> values;
	
public:
	// constructor
	Record();
	Record(vector<string> value);
	~Record();
	
	// functions
	void addValue(string t);
	void removeValue(int i);
	string getValue(int i);
	string operator[](int i) const;		// iterate through values
    string & operator[](int i);			// iterate through values
};
	
/** HELPER CLASSES **/

class AttributeTypeTuple				// attribute name and the type of the attribute, so tables can know what each column contains
{
private:
	// members
	string attribute;
	string type;
	
public:
	// constructor
	AttributeTypeTuple(string a, string t): attribute(a), type(t) { }
	~AttributeTypeTuple();
	
	// functions
	string getAttribute();
	string getType();
};

class TableIterator
{
private:
	// members
	
public:
	// constructor
	TableIterator(Table t);						// places iterator on first record
	~TableIterator();
	
	// functions
	void next();								// moves to next record
	Record get();								// returns current record
};

class runtime_error : public exception {
public:
	runtime_error(const string& message);
};

 #endif
