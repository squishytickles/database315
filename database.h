/*
 * Authors: 	Graham Leslie, Sarah Vance, Ryan Finke
 * Date:		1/31/2013
 * Desc:		Header file for the database project
 */
 
#ifndef _DATABASE_H
#define _DATABASE_H
 
 /** INCLUDES **/
 
#include <vector>
 
/** CLASSES **/
 
// main classes
class Database
{
private:
	// members
	vector<Table> tables;
	
public:
	// constructor
	Database();
	
	// functions
	void addTable();
	void deleteTable();
	vector<String>[] listTables();						// returns names of tables
	vector<Table>[] getTables();						// returns actual tables
	Table query(string querycmd);
	void deleteQuery(string querycmd);					// opposite of query()
}

class Table
{
private:
	// members
	vector<Record> records;								// has list of records
	vector<AttributeTypeTuple>[] attributesAndTypes;	// also has list of its aTTs for records
	
public:
	// constructor
	Table();
	Table(vector<AttributeTypeTuple>[] aTTs): attributesAndTypes(aTTs) { }
	
	// functions
	void add(AttributeTypeTuple aTT);
	void deleteATT(AttributeTypeTuple aTT);
	void addRecord(Record record);
	vector<AttributeTypeTuple>[] getAttributes();
	int getSize();
	void rename(String originalName, String newName);
	int sum(String attribute);
	int count(String attribute);
	int min(String attribute);
	int max(String attribute);
	Table crossJoin(Table& otherTable);
	
	Record operator[](int i) const;		// iterate through records
    Record & operator[](int i);			// iterate through records
	
}
	
// helper classes
class AttributeTypeTuple
{
private:
	// members
	string attribute;
	Type type;
	
public:
	// constructor
	AttributeTypeTuple(string a, Type t): attribute(a), type(t) { }
	
	// functions
	string getAttribute();
	Type getType();
}

class Record
{
private:
	// members
	vector<Type> values;
	
public:
	// constructor
	Record();
	
	// functions
	void addValue(Type t);
	void removeValue(int i);
	void getValue(int i);
	Type operator[](int i) const;		// iterate through values
    Type & operator[](int i);			// iterate through values
}

class TableIterator
{
private:
	// members
	
public:
	// constructor
	TableIterator(Table t);						// places iterator on first record
	
	// functions
	void next();								// moves to next record
	Record get();								// returns current record
}

// classes for valid Types
class Type;
class Int : public Type;
class Float : public Type;
class String : public Type;
class Date : public Type;
 