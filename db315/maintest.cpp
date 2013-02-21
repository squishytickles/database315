//! maintest.cpp

#define BOOST_TEST_MAIN

#include "Database.h"
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(Test_Query)
{
	AttributeTypeTuple testTuple1("name", "string");
	AttributeTypeTuple testTuple2("age", "int");
	vector<AttributeTypeTuple> testTupleVector;
	testTupleVector.push_back(testTuple1);
	testTupleVector.push_back(testTuple2);
	Table testTable(testTupleVector);

	vector<string> values;
	values.push_back("Bob");
	values.push_back("37");
	testTable.insert(Record(values));
	values.clear();
	values.push_back("Sally");
	values.push_back("25");
	testTable.insert(Record(values));
	values.clear();
	values.push_back("Joe");
	values.push_back("37");
	testTable.insert(Record(values));

	Database database;
	database.addTable(testTable, "People");

	string query = "SELECT name ";
	query += "FROM People ";
	query += "WHERE age = 25";
	Table youngPeople = database.query(query);

	if (youngPeople.getSize() != 1)
		BOOST_ERROR("Incorrect number of Records returned from first query");
	else if (youngPeople[0][0].compare("Sally") != 0)
		BOOST_ERROR("Wrong person returned in first query");

	query = "SELECT name ";
	query += "FROM People WHERE age = 37";
	Table oldPeople = database.query(query);

	if (oldPeople.getSize() != 2)
		BOOST_ERROR("Incorrect number of Records returned from second query");
	else
	{
		bool found1 = false;
		bool found2 = false;
		for (int i=0; i < 2; i++)
		{
			if (oldPeople[i][0].compare("Bob") == 0)
				found1 = true;
			if (oldPeople[i][0].compare("Joe") == 0)
				found2 = true;
		}
		if (!found1)
			BOOST_ERROR("Bob should be in the second query");
		if (!found2)
			BOOST_ERROR("Joe should be in the second query");
	}
}