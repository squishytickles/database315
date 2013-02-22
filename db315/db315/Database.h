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
#include <sstream>
#include <stack>
#include <queue>
#include <iostream>
  
/** MAIN CLASSES **/

class Record;
class AttributeTypeTuple;
class Table;
class Date;



using namespace std;

class Database
{
private:
	// members
	vector<Table> tables;

public:
	// constructor
	Database() { }
	~Database() { }

	// functions
	void addTable(Table table, string tableName);
	void dropTable(string tableName);
	vector<string> listTables();						// returns names of tables
	vector<Table> getTables();						// returns actual tables
	Table query(string queryCmd);
	void deleteQuery(string querycmd);				// opposite of query()
	float stringToFloat(string type);
	int stringToInt(string type);
	Date stringToDate(string type);
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
	Table() { }
	Table(vector<AttributeTypeTuple> aTTs): attributesAndTypes(aTTs) { }
	~Table() { }

	// functions
	string getName();
	void setName(string n);
	void add(AttributeTypeTuple aTT);
	void deleteATT(string attributeName);
	void insert(Record record);
	vector<AttributeTypeTuple> getAttributes();
	int getSize();
	void rename(string originalName, string newName);
	float sum(string attribute);
	int count(string attribute);
	float min(string attribute);
	float max(string attribute);
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
	Record() { }
	Record(vector<string> value);
	~Record() { }

	// functions
	void addValue(string t);
	void removeValue(int i);
	void nullValue(int i);
	string getStringValue(int i);
	float getFloatValue(int i);
	int getIntValue(int i);
	Date getDateValue(int i);
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
	~AttributeTypeTuple() { }

	// functions
	string getAttribute();
	void setAttribute(string newName);
	string getType();
	int getTypeInt();
	int AttributeTypeTuple::compare(AttributeTypeTuple& other);
};

class Date
{
private:
	// members
	int month;
	int day;
	int year;

public:
	// constructor 
	Date(int y, int m, int d): year(y), month(m), day(d) { }
	~Date() { }
	
	// functions
	int compare(Date& other);
	int getYear();
	int getMonth();
	int getDay();
};
	

class TableIterator
{
private:
	// members
	Table table;
	int i;

public:
	// constructor
	TableIterator(Table t): table(t), i(0) { }						// places iterator on first record
	~TableIterator() { }

	// functions
	void next();								// moves to next record
	Record get();								// returns current record
};

class Database_exception: public std::runtime_error{
  public:
   Database_exception():runtime_error("Fatal database exception encountered."){}
   Database_exception(std::string msg):runtime_error(msg.c_str()){}
 };

 #endif
