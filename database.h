/*
 * Authors: 	Graham Leslie, Sarah Vance, Ryan Finke
 * Date:		1/31/2013
 * Desc:		Header file for the database project
 */
 
#ifndef _DATABASE_H
#define _DATABASE_H
 
 /** INCLUDES **/
 
#include <vector>
#include <exception>
#include <stdexcept>
  
/** MAIN CLASSES **/

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
	vector<string>[] listTables();						// returns names of tables
	vector<Table>[] getTables();						// returns actual tables
	Table query(string queryCmd);
	void deleteQuery(string querycmd);					// opposite of query()
}

class Table
{
private:
	// members
	string name;
	vector<Record> records;								// has list of records
	vector<AttributeTypeTuple>[] attributesAndTypes;	// also has list of its aTTs for records
	
public:
	// constructor
	Table();
	Table(vector<AttributeTypeTuple>[] aTTs): attributesAndTypes(aTTs) { }
	~Table();
	
	// functions
	void getName();
	void add(AttributeTypeTuple aTT);
	void deleteATT(string attributeName);
	void insert(Record record);
	vector<AttributeTypeTuple>[] getAttributes();
	int getSize();
	void rename(string originalName, string newName);
	int sum(string attribute);
	int count(string attribute);
	int min(string attribute);
	int max(string attribute);
	Table crossJoin(Table& otherTable);
	
	Record operator[](int i) const;		// iterate through records
    Record & operator[](int i);			// iterate through records
	
}

class Record
{
private:
	// members
	vector<Strings> values;
	
public:
	// constructor
	Record();
	~Record();
	
	// functions
	void addValue(string t);
	void removeValue(int i);
	string getValue(int i);
	string operator[](int i) const;		// iterate through values
    string & operator[](int i);			// iterate through values
}
	
/** HELPER CLASSES **/

class AttributeTypeTuple				// attribute name and the type of the attribute, so tables can know what each column contains
{
private:
	// members
	string attribute;
	Type type;
	
public:
	// constructor
	AttributeTypeTuple(string a, Type t): attribute(a), type(t) { }
	~AttributeTypeTuple();
	
	// functions
	string getAttribute();
	Type getType();
}

class TableIterator
{
private:
	// members
	
public:
	// constructor
	TableIterator(Table t);						// places iterator on first record
	~TableIterator(Table t);
	
	// functions
	void next();								// moves to next record
	Record get();								// returns current record
}

class DatabaseError : public runtime_error 
{
public:
	DatabaseError(const string& msg = "") : runtime_error(msg) { }
}

// classes for valid Types
class Type;
class Int : public Type;
class Float : public Type;
class string : public Type;
class Date : public Type;
 
