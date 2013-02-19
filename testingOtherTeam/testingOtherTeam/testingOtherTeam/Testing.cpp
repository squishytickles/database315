#pragma once

/// @author Graham Leslie

#define BOOST_TEST_MAIN

#include <string>;
#include <vector>;
#include "Database.h"
#include <boost/test/unit_test.hpp>

using namespace std;

// create table
BOOST_AUTO_TEST_CASE(CREATE_TABLE)
{
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	BOOST_REQUIRE(table.getSize() == 0);
}

// table rename attribute
BOOST_AUTO_TEST_CASE(RENAME_ATTRIBUTE)
{
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"numberOLD"));

	table.renameAttribute("number","numberOLD");
}

// table remove attribute
BOOST_AUTO_TEST_CASE(REMOVE_ATTRIBUTE)
{
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	table.removeAttribute(Table::Attribute(INT,"number"));
}

// record create
BOOST_AUTO_TEST_CASE(RECORD_CREATE)
{
	Record record = Record();

	BOOST_REQUIRE(record.size() == 0);
}

// record create w vector
BOOST_AUTO_TEST_CASE(RECORD_CREATE_WITH_VECTOR)
{
	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");

	Record record = Record(values);

	BOOST_REQUIRE(record.size() == 3);
}

// record remove value
BOOST_AUTO_TEST_CASE(REMOVE_RECORD_VALUE)
{
	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");

	Record record = Record(values);

	record.removeColumn(0);

	BOOST_REQUIRE(record.size() == 2);
}

// table add record
BOOST_AUTO_TEST_CASE(TABLE_ADD_RECORD)
{
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");

	Record record = Record(values);

	table.insertRecord(record);

	BOOST_REQUIRE(table.getSize() == 1);
}

// table iterator
BOOST_AUTO_TEST_CASE(TABLE_ITERATOR)
{
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");

	Record record = Record(values);

	BOOST_REQUIRE(table.begin()[0].getFloat(0) == record.getFloat(0));
}

// rountines on table
BOOST_AUTO_TEST_CASE(TABLE_ROUTINES)
{
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");
	Record recordA = Record(values);

	values.clear();
	values.push_back("1943.50");
	values.push_back("Sarah Vance");
	values.push_back("2");
	Record recordB = Record(values);
	
	table.insertRecord(recordA);
	table.insertRecord(recordB);

	BOOST_CHECK(table.sumFloat("price") == (float)(1342.5 + 1943.5));
	BOOST_CHECK(table.sumInt("number") == 1 + 2);
	BOOST_CHECK(table.minInt("number") == 1);
	BOOST_CHECK(table.maxInt("number") == 2);
	BOOST_CHECK(table.minFloat("price") == (float)1342.5);
	BOOST_CHECK(table.maxFloat("price") == (float)1943.5);
}

// cross join
BOOST_AUTO_TEST_CASE(CROSS_JOIN)
{
	Table tableA = Table();

	tableA.addAttribute(Table::Attribute(FLOAT,"price"));
	tableA.addAttribute(Table::Attribute(STRING,"name"));

	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	Record recordA = Record(values);

	Table tableB = Table();

	tableB.addAttribute(Table::Attribute(FLOAT,"price2"));
	tableB.addAttribute(Table::Attribute(STRING,"name2"));

	values.clear();
	values.push_back("1943.50");
	values.push_back("Sarah Vance");
	Record recordB = Record(values);
	
	tableA.insertRecord(recordA);
	tableB.insertRecord(recordB);

	values.clear();
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1943.50");
	values.push_back("Sarah Vance");

	Record recordC = Record(values);

	Table tableC = tableA.crossJoin(tableA,tableB);
	BOOST_CHECK(tableC.begin()[0].getFloat(0) == recordC.getFloat(0));
	BOOST_CHECK(tableC.begin()[0].getString(1) == recordC.getString(1));
	BOOST_CHECK(tableC.begin()[0].getFloat(2) == recordC.getFloat(2));
	BOOST_CHECK(tableC.begin()[0].getString(3) == recordC.getString(3));
}

// db create
BOOST_AUTO_TEST_CASE(DATABASE_CREATE)
{
	Database db = Database();
}

// db add table
BOOST_AUTO_TEST_CASE(DATABASE_ADD_RECORD)
{
	Database db = Database();
	
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	db.addTable("table",table);

	BOOST_REQUIRE(db.listTables()[0].compare("table"));
}

// db drop
BOOST_AUTO_TEST_CASE(DATABASE_DROP_TABLE)
{
	Database db = Database();
	
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	db.addTable("table",table);
	db.dropTable("table");

	BOOST_REQUIRE(db.numTables() == 0);
}

// db query star
BOOST_AUTO_TEST_CASE(DATABASE_QUERY_STAR)
{
	Database db = Database();
	
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");
	Record recordA = Record(values);

	values.clear();
	values.push_back("1943.50");
	values.push_back("Sarah Vance");
	values.push_back("2");
	Record recordB = Record(values);
	
	table.insertRecord(recordA);
	table.insertRecord(recordB);

	db.addTable("table",table);



	vector<string> attr;
	attr.push_back("*");

	Table result = db.query(attr,"table","WHERE (num = 2)");
	BOOST_REQUIRE(result.getSize() == 2);
	BOOST_CHECK(result.begin()[0].getFloat(0) == (float)1943.5);
}
// db query nostar
BOOST_AUTO_TEST_CASE(DATABASE_DELQUERY_STAR_A)
{
	Database db = Database();
	
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");
	Record recordA = Record(values);

	values.clear();
	values.push_back("1943.50");
	values.push_back("Sarah Vance");
	values.push_back("2");
	Record recordB = Record(values);
	
	table.insertRecord(recordA);
	table.insertRecord(recordB);

	db.addTable("table",table);



	vector<string> attr;
	attr.push_back("price");

	Table result = db.query(attr,"table","WHERE (price < 1500)");
	BOOST_REQUIRE(result.getSize() == 2);
	BOOST_CHECK(result.begin()[0].getFloat(0) == (float)1342.5);
}

// db deletequery
BOOST_AUTO_TEST_CASE(DATABASE_DELQUERY_STAR_B)
{
	Database db = Database();
	
	Table table = Table();

	table.addAttribute(Table::Attribute(FLOAT,"price"));
	table.addAttribute(Table::Attribute(STRING,"name"));
	table.addAttribute(Table::Attribute(INT,"number"));

	vector<string> values;
	values.push_back("1342.50");
	values.push_back("Graham Leslie");
	values.push_back("1");
	Record recordA = Record(values);

	values.clear();
	values.push_back("1943.50");
	values.push_back("Sarah Vance");
	values.push_back("2");
	Record recordB = Record(values);
	
	table.insertRecord(recordA);
	table.insertRecord(recordB);

	db.addTable("table",table);



	vector<string> attr;
	attr.push_back("*");

	Table result = db.query(attr,"table","WHERE (num = 2)");
	BOOST_REQUIRE(result.getSize() == 1);
}
