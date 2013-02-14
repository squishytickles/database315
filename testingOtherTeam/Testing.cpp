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

BOOST_AUTO_TEST_CASE(Date)
{
	Date d = Date(1970,12,2);
	BOOST_CHECK(d.year() == 1970);
	BOOST_CHECK(d.month() == 12);
	BOOST_CHECK(d.day() == 2);
}

BOOST_AUTO_TEST_CASE(CreateATable)
{
	// create some attributes
	vector<Attribute> attributes;
	attributes.push_back(Attribute(FLOAT, "cost"));
	attributes.push_back(Attribute(STRING, "temporary"));
	
	// create a table
	Table table = Table(attributes);

	// add attributes to table
	table.addAttribute(Attribute(INT, "age"));
	table.addAttributes(Attribute(DATE, "date"));

	// rename temporary to name
	table.renameAttribute("temporary","name");

	// test empty
	BOOST_CHECK(table.sumFloat("cost") == 0);
	BOOST_CHECK(table.sumInt("age") == 0);
	BOOST_CHECK(table.count("age") == 0);
	BOOST_CHECK(table.count("cost") == 0);
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
	// add record A
	table.insertRecord(recordA);
	BOOST_CHECK(table.getSize() == 1);

	// also add record B
	table.insertRecord(recordB);
	BOOST_CHECK(table.getSize() == 2);
	BOOST_CHECK(table.count("cost") == 2);
	BOOST_CHECK(table.count("date") == 2);

BOOST_AUTO_TEST_CASE(CreateADatabase)
{
	// create a database
	Database db = Database();

	// add table as "lunch"
	BOOST_REQUIRE(db.addTable("lunch", table) == true);
	BOOST_REQUIRE(db.getTables[0] == "lunch");

	// drop it
	BOOST_REQUIRE(db.dropTable("lunch") == true);

	// double check
	BOOST_REQUIRE(db.numTables() == 0);
	
	// add it again
	BOOST_REQUIRE(db.addTable("lunch",table), == true);
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
	attr.push_back(Attribute(FLOAT,"cost"));
	attr.push_back(Attribute(STRING,"name"));

	// run another query
	result = db.query(attr,"lunch","cost > 0");

	// what result should look like
	Table goodResult = Table();
	goodResult.addAttribute(Attribute(FLOAT,"cost"));
	goodResult.addAttribute(Attribute(FLOAT,"name"));
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

BOOST_AUTO_TEST_CASE(AddlTableSetup)
{
	// add an additional table in db
	Table newTable = Table();

	// give it some attributes
	newTable.addAttribute(Attribute(FLOAT,"grade"));
	newTable.addAttribute(Attribute(INT,"studentid"));
	newTable.addAttribute(Attribute(STRING,"professor"));
	newTable.addAttribute(Attribute(STRING,"class"));
}

BOOST_AUTO_TEST_CASE(AddlTableAddRecords)
{
	// add records
	values.clear();
	values.push_back("85.7");
	values.push_back("111");
	values.push_back("Keyser");
	values.push_back("315");

	Record aNew1 = Record(values);
	BOOST_CHECK(aNew1.getFloat(0) == 85.7f);
	BOOST_CHECK(aNew1.size() == 4);
	BOOST_CHECK(aNew1.getString(2) == "Keyser");
	BOOST_CHECK(aNew1.getInt(3) == 315);

	values.clear();
	values.push_back("82.7");
	values.push_back("112");
	values.push_back("Keyser");
	values.push_back("315");
	BOOST_CHECK(aNew2.getFloat(0) == 82.7f);
	BOOST_CHECK(aNew2.size() == 4);
	BOOST_CHECK(aNew2.getString(2) == "Keyser");
	BOOST_CHECK(aNew2.getInt(3) == 315);

	Record aNew2 = Record(values);

	values.clear();
	values.push_back("25.7");
	values.push_back("113");
	values.push_back("Keyser");
	values.push_back("315");
	BOOST_CHECK(aNew3.getFloat(0) == 25.7f);
	BOOST_CHECK(aNew3.size() == 4);
	BOOST_CHECK(aNew3.getString(2) == "Keyser");
	BOOST_CHECK(aNew3.getInt(3) == 315);

	Record aNew3 = Record(values);

	// check reassignments
	aNew3.setString(2, "Bettati");
	BOOST_CHECK(aNew3.getString(2) == Bettati);
	
	aNew2.setFloat(0,1.3);
	BOOST_CHECK(aNew2.getFloat(0) == 1.3);

	aNew1.setInt(3, 221);
	BOOST_CHECK(aNew1.getInt(3) == 221);

	// add them to the table
	newTable.insertRecord(aNew1);
	newTable.insertRecord(aNew2);
	newTable.insertRecord(nNew3);
}

BOOST_AUTO_TEST_CASE(TableIterator)
{
	Iterator itB = newTable.begin();
	Iterator itE = newTable.end();

	// not exactly sure of the syntax of the iterator, not included
	BOOST_CHECK(itB == aNew1);
	BOOST_CHECK(itB.next() == aNew2);
	BOOST_CHECK(itE == aNew3);
	BOOST_CHECK(it.prev() == aNew2);

}

BOOST_AUTO_TEST_CASE(AddNewTable)
{
	// add the new table
	db.addTable("newTable",newTable);
	BOOST_REQUIRE(db.numTables() == 2);
	BOOST_REQUIRE(db.getTables[1] == "newTable");
	BOOST_REQUIRE(db.getTables[0] == "lunch");							
}

BOOST_AUTO_TEST_CASE(MoreQuery)
{
	attr.clear();
	attr.push_back(Attribute(FLOAT,"grade"));
	attr.push_back(Attribute(STRING,"professor"));
	attr.push_back(Attribute(STRING,"class"));
	
	result = db.query(attr,"newTable","WHERE professor != 'Lee'");

	BOOST_CHECK(result.count("grade") == 4);
	BOOST_CHECK(result.maxFloat(0) == 85.7);
	BOOST_CHECK(result.maxInt(3) == 315);
	BOOST_CHECK(result.minFloat(0) == 1.3);
	BOOST_CHECK(result.minInt(3) == 221);
	BOOST_CHECK(result.sumFloat(0) == 85.7 + 1.4 + 25.7);
	BOOST_CHECK(reusult.sumInt(3) == 315 + 221 + 315);					

	result = db.query(attr,"newTable","WHERE professor = 'Lee'");

	BOOST_CHECK(result.count("grade") == 0);
}

BOOST_AUTO_TEST_CASE(DeletingQuery)
{
	db.deleteByQuery(attrStar,"newTable","WHERE grade < 50 OR professor = 'Bettati'");
	result = db.query(attrStar,"newTable","");

	BOOST_CHECK(result.count("grade") == 1);
	BOOST_CHECK(result.maxFloat("grade") == 85.7);
	BOOST_CHECK(result.maxInt("class") == 221);
}

BOOST_AUTO_TEST_CASE(MoreDBTests)
{
	vector<String> goodListTables;
	goodListTables.push_back("lunch");
	goodListTables.push_back("newTable");
	
	BOOST_CHECK(db.listTables() == goodListTables);

	BOOST_REQUIRE(db.numTables() == 2);
	BOOST_REQUIRE(db.drop("lunch") == true);

	goodListTables.erase(goodListTables.begin());
	BOOST_CHECK(db.listTables() == goodListTables);

	BOOST_REQUIRE(db.numTables() == 1);
	BOOST_REQUIRE(db.drop("newTable") == true);

	goodListTables.erase(goodListTables.begin());
	BOOST_CHECK(db.listTables() == goodListTables);

	BOOST_REQUIRE(db.numTables() == 0);
}
