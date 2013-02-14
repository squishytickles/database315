#pragma once

/// @author Graham Leslie

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <string>;
#include <vector>;

using namespace std;

    // BOOST_REQUIRE(false);	-- fail on error
	// BOOST_CHECK(false);		-- continue on error
	// BOOST_ERROR(false);		-- fail on error, more descriptive

BOOST_AUTO_TEST_CASE(CreateATable)
{
	// create some attributes
	vector<Attribute> attributes;
	attributes.push_back(pair(FLOAT, "cost"));
	attributes.push_back(pair(STRING, "temporary"));
	
	// create a table
	Table table = Table(attributes);

	// add attributes to table
	table.addAttribute(pair(INT, "age"));
	table.addAttributes(pair(DATE, "date"));

	// rename temporary to name
	table.renameAttribute("temporary","name");
}

BOOST_AUTO_TEST_CASE(CreateSomeRecords)
{
	// create some values
	vector<string> values;
	values.push_back("12.24");
	values.push_back("Sarah");
	values.push_back("22");
	values.push_back(Date(1907,12,1));
	
	// add them a record
	Record recordA = Record(values);
	BOOST_CHECK(recordA.size() == 4);

	// create some more values
	values.clear();
	values.push_back("-2.32");
	values.push_back("Graham");
	
	// add them to a record
	Record recordB = Record(values);
	BOOST_CHECK(recordB.size() == 2);
	recordB.addColumn("19");
	recordB.addColumn(Date(2002,3,15));
	BOOST_CHECK(recordB.size() == 4);
}

BOOST_AUTO_TEST_CASE(AddRecordsToTable)
{
	table.insertRecord(recordA);
	BOOST_CHECK(table.getSize() == 1);
	table.insertRecord(recordB);
	BOOST_CHECK(table.getSize() == 2);
	BOOST_CHECK(table.count("cost") == 2);
	BOOST_CHECK(table.count("date") == 2);

BOOST_AUTO_TEST_CASE(CreateADatabase)
{
	Database db = Database();
	db.addTable("lunch", table);
	BOOST_REQUIRE(db.getTables[0] == "lunch");
	db.dropTable("lunch");
	BOOST_REQUIRE(db.numTables() == 0);
	db.addTable("lunch",table);
}

BOOST_AUTO_TEST_CASE(TestSimpleQueries)
{
	// create a * vector
	vector<string> attrStar;
	attrStar.push_back("*");

	// run a query
	Table result = db.query(attrStar,"lunch","name = Sarah");
	BOOST_CHECK(result == tableA);

	// run another query
	result = db.query(attrStar,"lunch","cost = -2.32");
	BOOST_CHECK(result == tableB);
}

BOOST_AUTO_TEST_CASE(TestCrazierQuery)
{
	// edit attr
	vector<strin> attr;
	attr.push_back("cost");
	attr.push_back("name");

	// run another query
	result = db.query(attr,"lunch","cost > 0");

	// what result should look like
	Table goodResult = Table();
	goodResult.addAttribute("cost");
	goodResult.addAttribute("name");
	Record recordC = Record();
	recordC.addColumn("12.24");
	recordC.addColumn("Sarah");
	goodResult.insertRecord(recordC);

	BOOST_CHECK(result == recordC);
}

BOOST_AUTO_TEST_CASE(TestCrossJoin)
{
	Table tB = db.query(attrStar,"lunch","cost > 0");
	Table tA = db.query(attrStar,"lunch","cost < 0");

	Table tC = crossJoin(tA,tB);
	BOOST_CHECK(tC == db.query(attrStar,"lunch","");
}

BOOST_AUTO_TEST_CASE(Routines)
{
	BOOST_CHECK(tC.sumFloat("cost") == 9.92f);
	BOOST_CHECK(tC.minFloat("cost") == -2.43f);
}