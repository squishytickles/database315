//! maintest.cpp

#define BOOST_TEST_MAIN

#include "Database.h"
#include <string>
#include <vector>
#include <boost/test/unit_test.hpp>

using namespace std;

BOOST_AUTO_TEST_CASE(AttributeTypeTuple_Create_Test1){
	AttributeTypeTuple testTuple = AttributeTypeTuple("id", "int");
	BOOST_CHECK(strcmp(testTuple.getAttribute().c_str(), "id") == 0 && strcmp(testTuple.getType().c_str(), "int") == 0);
}

BOOST_AUTO_TEST_CASE(Table_Create_Test1)
{
	vector<AttributeTypeTuple> attribs = vector<AttributeTypeTuple>();
	attribs.push_back(AttributeTypeTuple("id", "int"));
	attribs.push_back(AttributeTypeTuple("fname", "string"));
	attribs.push_back(AttributeTypeTuple("lname", "string"));
	attribs.push_back(AttributeTypeTuple("joined", "date"));
	Table testTable = Table(attribs);
	attribs = testTable.getAttributes();
	string name, type;
	for(int i = 0; i < attribs.size(); i++){
		name = attribs[i].getAttribute();
		type = attribs[i].getType();
		if(name.compare("id") == 0 && type.compare("int") != 0)
			BOOST_ERROR("Attribute Names and Types dont match");
		else if(name.compare("fname") == 0 && type.compare("string") != 0)
			BOOST_ERROR("Attribute Names and Types dont match");
		else if(name.compare("lname") == 0 && type.compare("string") != 0)
			BOOST_ERROR("Attribute Names and Types dont match");
		else if(name.compare("joined") == 0 && type.compare("date") != 0)
			BOOST_ERROR("Attribute Names and Types dont match");
	}
}

BOOST_AUTO_TEST_CASE(Table_Insert){
	Table testTable = Table::Table();
	testTable.add(AttributeTypeTuple("joined", "date"));
	vector<AttributeTypeTuple> attribs = testTable.getAttributes();
	if(attribs.size() < 1)
		BOOST_ERROR("Error adding AttributeTypeTuple to Table");
	string name, type;
	for(int i=0;i<attribs.size();i++){
		name = attribs[i].getAttribute();
		type = attribs[i].getType();
		if(name.compare("joined") == 0 && type.compare("date") != 0)
			BOOST_ERROR("Attribute Names and Types dont match after adding it to the table");
	}
}

BOOST_AUTO_TEST_CASE(Table_Insert_into){
	vector<AttributeTypeTuple> attribs = vector<AttributeTypeTuple>();
	attribs.push_back(AttributeTypeTuple("id", "int"));
	attribs.push_back(AttributeTypeTuple("fname", "string"));
	attribs.push_back(AttributeTypeTuple("lname", "string"));
	attribs.push_back(AttributeTypeTuple("joined", "date"));
	Table testTable = Table(attribs);
	vector<string> row = vector<string>();

	row.push_back("1");
	row.push_back("James");
	row.push_back("Smith");
	row.push_back("01/11/2012");
	testTable.insert(row);
	if(testTable.getSize() < 1)
		BOOST_ERROR("No Values were inserted into the table");
	for(int i=0;i<testTable.getSize();i++){
		Record test = testTable[i];
		if(test.getValue(0).compare("1") != 0)
			BOOST_ERROR("Invalid Record found in table");
		else if(test.getValue(1).compare("James") != 0)
			BOOST_ERROR("Invalid Record found in table");
		else if(test.getValue(1).compare("Smith") != 0)
			BOOST_ERROR("Invalid Record found in table");
		else if(test.getValue(1).compare("01/11/2012") != 0)
			BOOST_ERROR("Invalid Record found in table");
	}
}

BOOST_AUTO_TEST_CASE(Deleting_Table_Attributes){
	vector<AttributeTypeTuple> attribs = vector<AttributeTypeTuple>();
	attribs.push_back(AttributeTypeTuple("joined", "date"));
	Table testTable = Table(attribs);

	testTable.deleteATT("joined");
	attribs = testTable.getAttributes();
	for(int i=0;i<attribs.size();i++){
		if(attribs[i].getAttribute().compare("joined") == 0)
			BOOST_ERROR("Attribute was not deleted");
	}
}

BOOST_AUTO_TEST_CASE(Table_Renaming_Attributes){
	vector<AttributeTypeTuple> attribs = vector<AttributeTypeTuple>();
	attribs.push_back(AttributeTypeTuple("joined", "date"));
	Table testTable = Table(attribs);
	testTable.rename("joined", "dateJoined");
	attribs = testTable.getAttributes();
	for(int i=0;i<attribs.size();i++){
		if(attribs[i].getAttribute().compare("joined") == 0)
			BOOST_ERROR("Attribute was not renamed");
	}
}

BOOST_AUTO_TEST_CASE(Table_Routine_Tests){
	Table testTable = Table();
	testTable.add(AttributeTypeTuple("nums", "int"));
	vector<string> row = vector<string>();
	row.push_back("1");
	testTable.insert(row);
	row.clear();
	row.push_back("5");
	testTable.insert(row);
	row.clear();
	row.push_back("3");
	testTable.insert(row);

	if(testTable.max("nums") != 5){
		BOOST_ERROR("Max Function does not return correct value");
	}
	if(testTable.sum("nums") != 9){
		BOOST_ERROR("Sum Function does not return correct value");
	}
	if(testTable.min("nums") != 1){
		BOOST_ERROR("Min Function does not return correct value");
	}
}

BOOST_AUTO_TEST_CASE(Table_Cross_Join){
	Table testTable1 = Table();
	testTable1.add(AttributeTypeTuple("id", "int"));
	vector<string> data = vector<string>();
	data.push_back("1");
	testTable1.insert(Record(data));
	
	Table testTable2 = Table();
	testTable2.add(AttributeTypeTuple("name", "string"));
	data.clear();
	data.push_back("James");
	testTable2.insert(Record(data));
	Table resultTable = testTable1.crossJoin(testTable2);

	vector<AttributeTypeTuple> attribs = resultTable.getAttributes();
	if(attribs.size() < 1)
		BOOST_ERROR("An Invalid table was returned.");
	for(int i=0;i<attribs.size();i++){
		if(attribs[i].getAttribute().compare("id") == 0 && attribs[i].getType().compare("int") != 0)
			BOOST_ERROR("Attribute names and types do not match");
		else if(attribs[i].getAttribute().compare("name") == 0 && attribs[i].getType().compare("string") != 0)
			BOOST_ERROR("Attribute names and types do not match");
	}

	if(resultTable.getSize() < 1)
		BOOST_ERROR("Data was not transfered to new table");
	for(int i=0;i<resultTable.getSize();i++){
		if(resultTable[i].getValue(i).compare("1") != 0 || resultTable[i].getValue(i).compare("James") != 0)
			BOOST_ERROR("Data was not transfered to merged table");
	}
}

BOOST_AUTO_TEST_CASE(Database_Add_Table){
	Database testDatabase = Database();

	vector<AttributeTypeTuple> attribs = vector<AttributeTypeTuple>();
	attribs.push_back(AttributeTypeTuple("id", "int"));
	attribs.push_back(AttributeTypeTuple("fname", "string"));
	attribs.push_back(AttributeTypeTuple("lname", "string"));
	attribs.push_back(AttributeTypeTuple("joined", "date"));
	Table testTable1 = Table(attribs);

	attribs.clear();
	attribs.push_back(AttributeTypeTuple("nums", "int"));
	Table testTable2 = Table(attribs);

	testDatabase.addTable(testTable1, "testTable1");
	testDatabase.addTable(testTable2, "testTable2");

	vector<string> listTables = testDatabase.listTables();
	if(listTables.size() < 1)
		BOOST_ERROR("No Tables found in Database");
	int count = 0;
	for(int i=0;i<listTables.size();i++){
		if(listTables[i].compare("testTable1") == 0 || listTables[i].compare("testTable2") == 0)
			count++;
	}

	if(count != 2)
		BOOST_ERROR("Not enought tables found in Database List");

	vector<Table> tables = testDatabase.getTables();
	if(count != 2)
	for(int i=0;i<tables.size();i++){
		vector<AttributeTypeTuple> attribs = tables[i].getAttributes();
		if(attribs.size() < 1)
			BOOST_ERROR("An Invalid table was returned.");
		for(int i=0;i<attribs.size();i++){
			if(attribs[i].getAttribute().compare("id") == 0 && attribs[i].getType().compare("int") != 0)
				BOOST_ERROR("Attribute names and types do not match");
			else if(attribs[i].getAttribute().compare("nums") == 0 && attribs[i].getType().compare("int") != 0)
				BOOST_ERROR("Attribute names and types do not match");
		}
	}
}

BOOST_AUTO_TEST_CASE(Database_Drop){
	Database testDatabase = Database();

	vector<AttributeTypeTuple> attribs = vector<AttributeTypeTuple>();
	attribs.push_back(AttributeTypeTuple("id", "int"));
	attribs.push_back(AttributeTypeTuple("fname", "string"));
	attribs.push_back(AttributeTypeTuple("lname", "string"));
	attribs.push_back(AttributeTypeTuple("joined", "date"));
	Table testTable = Table(attribs);
	testDatabase.addTable(testTable, "testTable1");
	attribs.clear();
	attribs.push_back(AttributeTypeTuple("nums", "int"));
	testTable = Table(attribs);
	testDatabase.addTable(testTable, "testTable2");
	if(testDatabase.getTables().size() != 2)
		BOOST_ERROR("There arn't the right number of tables in the database");
	testDatabase.dropTable("testTable1");
	if(testDatabase.getTables().size() != 1)
		BOOST_ERROR("After droping a table, the number of tables is off in the database");
}

BOOST_AUTO_TEST_CASE(Database_Query_Star){
	Database testDatabase = Database();

	vector<AttributeTypeTuple> attribs = vector<AttributeTypeTuple>();
	attribs.push_back(AttributeTypeTuple("id", "int"));
	attribs.push_back(AttributeTypeTuple("fname", "string"));
	attribs.push_back(AttributeTypeTuple("lname", "string"));
	attribs.push_back(AttributeTypeTuple("joined", "date"));
	Table testTable = Table(attribs);
	vector<string> row = vector<string>();
	row.push_back("1");
	row.push_back("James");
	row.push_back("Smith");
	row.push_back("2012/02/20");
	testTable.insert(row);
	row.clear();
	row.push_back("2");
	row.push_back("John");
	row.push_back("Smith");
	row.push_back("2012/03/20");
	testTable.insert(row);
	testDatabase.addTable(testTable, "testTable");
	try{
		Table queryTable = testDatabase.query("SELECT * FROM testTable WHERE (id = 1)");
		if(queryTable.getSize() != 1)
			BOOST_ERROR("Database returned invalid number of rows");
		for(int i=0;i<queryTable.getSize();i++){
			if(queryTable[i][0].compare("1") != 0 || queryTable[i][1].compare("James") != 0 || 
				queryTable[i][2].compare("Smith") != 0 || queryTable[i][3].compare("2012/02/20") != 0)
				BOOST_ERROR("Database Query returned invalid data");
		}
	} catch(exception& e){
		string error = string(e.what());
		BOOST_ERROR("An exception was thrown with error: " + error);
	}
}

BOOST_AUTO_TEST_CASE(Error_Invalid_Drop_Table){
	try{
		Database testDabase = Database();
		testDabase.dropTable("table");
		BOOST_ERROR("Drop Table didnt error out when trying to drop an invalid table");
	} catch(exception& e){

	}
}

BOOST_AUTO_TEST_CASE(ERROR_Invalid_Record_Entry){
	try {
		Record testRecord = Record();
		string temp = testRecord[0];
		BOOST_ERROR("Accessed an invalid entry in a Record");
	} catch(exception& e){

	}
}


BOOST_AUTO_TEST_CASE(AttributeTypeTuple_Create){
	AttributeTypeTuple testTuple = AttributeTypeTuple("name", "string");
	BOOST_CHECK(strcmp(testTuple.getAttribute().c_str(), "name") == 0
				&& strcmp(testTuple.getType().c_str(), "string") == 0);
}

BOOST_AUTO_TEST_CASE(Record_Create){
	Record record;
	record.addValue("Bob");
	record.addValue("25");
	record.addValue("Australia");

	if (record.getValue(0).compare(record[0]) != 0 || record[1].compare("25") != 0
		|| record[2].compare("Australia") != 0)
		BOOST_ERROR("Values not added correctly to Record");
}

BOOST_AUTO_TEST_CASE(Record_Create_With_Vector)
{
	vector<string> data = vector<string>();
	data.push_back("Bob");
	data.push_back("25");
	data.push_back("Australia");
	
	Record record(data);

	if (record[0].compare("Bob") != 0 || record.getValue(1).compare("25") != 0
		|| record.getValue(2).compare("Australia") != 0)
		BOOST_ERROR("Record not initialized correctly");
}

BOOST_AUTO_TEST_CASE(Record_Remove_Value_From)
{
	vector<string> values;
	values.push_back("Bob");
	values.push_back("25");
	values.push_back("Australia");
	Record record(values);
	record.removeValue(1);

	if (record.getValue(1).compare("25") == 0)
		BOOST_ERROR("Value not removed from record");
	
}

BOOST_AUTO_TEST_CASE(Table_Create)
{
	Table testTable;
	testTable.add(AttributeTypeTuple("name", "string"));
	vector<AttributeTypeTuple> returnedTuples = testTable.getAttributes();

	if (returnedTuples.size() < 1)
		BOOST_ERROR("AttributeTypeTuple not added to table");
	else if (returnedTuples[0].getAttribute().compare("name") == 0 &&
			 returnedTuples[0].getType().compare("string") != 0)
		BOOST_ERROR("Attribute Names and Types don't match");
}

BOOST_AUTO_TEST_CASE(Table_Create_With_AttributeTypeTuples){
	AttributeTypeTuple testTuple1("name", "string");
	AttributeTypeTuple testTuple2("age", "int");
	vector<AttributeTypeTuple> testTupleVector;
	testTupleVector.push_back(testTuple1);
	testTupleVector.push_back(testTuple2);

	Table testTable(testTupleVector);
	vector<AttributeTypeTuple> returnedTuples = testTable.getAttributes();

	if (returnedTuples.size() < 1)
		BOOST_ERROR("AtributeTypeTuples not added to Table");
	else
	{
		if (returnedTuples[0].getAttribute().compare("name") == 0 &&
		   returnedTuples[0].getType().compare("string") != 0)
			BOOST_ERROR("Attribute Names and Types don't match");
		if (returnedTuples[1].getAttribute().compare("age") == 0 &&
		   returnedTuples[1].getType().compare("int") != 0)
			BOOST_ERROR("Attribute Names and Types don't match");
	}
}

BOOST_AUTO_TEST_CASE(Table_Rename_Attribute_In)
{
	vector<AttributeTypeTuple> testTuple;
	testTuple.push_back(AttributeTypeTuple("name", "string"));
	Table testTable(testTuple);
	testTable.rename("name", "occupation");

	if (testTable.getAttributes()[0].getAttribute().compare("occupation") != 0)
		BOOST_ERROR("New Attribute name not set");
}

BOOST_AUTO_TEST_CASE(Table_Delete_Attribute_From)
{
	AttributeTypeTuple testTuple1("name", "string");
	AttributeTypeTuple testTuple2("age", "int");
	vector<AttributeTypeTuple> testTupleVector;
	testTupleVector.push_back(testTuple1);
	testTupleVector.push_back(testTuple2);
	Table testTable(testTupleVector);

	testTable.deleteATT("age");
	vector<AttributeTypeTuple> returnedTuples = testTable.getAttributes();

	if (returnedTuples.size() > 1)
		BOOST_ERROR("Attributes not deleted from table");

	if (returnedTuples[0].getAttribute().compare("age") != 0)
		BOOST_ERROR("Wrong attribute deleted from table");
	else if (returnedTuples[0].getType().compare("string") != 0)
		BOOST_ERROR("Attribute Name and Type no longer match");
}

BOOST_AUTO_TEST_CASE(Table_Add_Records_To)
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

	if (testTable.getSize() < 2)
		BOOST_ERROR("Records not added to table at all, or incorrect size returned");

	if(testTable[0][0].compare("Bob") != 0 || testTable[0][1].compare("37") != 0)
		BOOST_ERROR("Record not added to table correctly");
	if(testTable[1][0].compare("Sally") != 0 || testTable[1][1].compare("25") != 0)
		BOOST_ERROR("Record not added to table correctly");
}

BOOST_AUTO_TEST_CASE(Table_SumMinMax)
{
	AttributeTypeTuple testTuple1("name", "string");
	AttributeTypeTuple testTuple2("age", "int");
	AttributeTypeTuple testTuple3("wage", "float");
	vector<AttributeTypeTuple> testTuples;
	testTuples.push_back(testTuple1);
	testTuples.push_back(testTuple2);
	testTuples.push_back(testTuple3);
	Table testTable(testTuples);

	vector<string> values;
	values.push_back("Bob");
	values.push_back("37");
	values.push_back("8.25");
	testTable.insert(Record(values));
	values.clear();
	values.push_back("Sally");
	values.push_back("25");
	values.push_back("10.50");
	testTable.insert(Record(values));
	values.clear();
	values.push_back("Mary");
	values.push_back("33");
	values.push_back("27.35");
	testTable.insert(Record(values));
	values.clear();
	values.push_back("Bill");
	values.push_back("48");
	values.push_back("13.75");
	testTable.insert(Record(values));

	int sum = testTable.sum("age");
	if (sum != 143)
		BOOST_ERROR("Table did not sum integers correctly");

	float sum2 = testTable.sum("wage");
	if (sum2 != 59.95)
		BOOST_ERROR("Table did not sum floats correctly");

	float maxWage = testTable.max("wage");
	if (maxWage != 27.35)
		BOOST_ERROR("Table did not find the maximum correctly");

	float minWage = testTable.min("wage");
	if (minWage != 8.25)
		BOOST_ERROR("Table did not find the minimum correctly");
}

BOOST_AUTO_TEST_CASE(TableIterator_Create)
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

	TableIterator iter(testTable);

	Record record = iter.get();
	if (record[0].compare("Bob") != 0)
		BOOST_ERROR("Iterator didn't return a Record");
	iter.next();
	record = iter.get();
	if (record[1].compare("25") != 0)
		BOOST_ERROR("Iterator did not move to the next record in Table");
}

BOOST_AUTO_TEST_CASE(Database_Create)
{
	Database database;
	vector<AttributeTypeTuple> testTupleVector;
	testTupleVector.push_back(AttributeTypeTuple("name", "string"));
	testTupleVector.push_back(AttributeTypeTuple("born", "date"));
	Table testTable1(testTupleVector);

	testTupleVector.clear();
	testTupleVector.push_back(AttributeTypeTuple("age", "int"));
	testTupleVector.push_back(AttributeTypeTuple("city", "string"));
	Table testTable2(testTupleVector);

	database.addTable(testTable1, "People");
	database.addTable(testTable2, "Numbers");
	vector<Table> tables = database.getTables();
	vector<string> tableNames = database.listTables();
	
	if (tables.size() < 2)
		BOOST_ERROR("Error adding Tables to Database");
	else if (tableNames.size() < 2)
		BOOST_ERROR("Error adding Table names to Database");
	else if (tableNames[0].compare("People") != 0 || tableNames[1].compare("Numbers") != 0)
		BOOST_ERROR("Tables do not match Table names");
}

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


BOOST_AUTO_TEST_CASE(Test_Database_Functions)
{
	Database database;
	vector<AttributeTypeTuple> testTupleVector;
	testTupleVector.push_back(AttributeTypeTuple("name", "string"));
	testTupleVector.push_back(AttributeTypeTuple("born", "date"));
	Table testTable1(testTupleVector);

	vector<string> values;
	values.push_back("Bob");
	values.push_back("1975/06/21");
	testTable1.insert(Record(values));
	values.clear();
	values.push_back("Sally");
	values.push_back("1988/01/05");
	testTable1.insert(Record(values));
	database.addTable(testTable1, "People and Birthdays");

	testTupleVector.clear();
	testTupleVector.push_back(AttributeTypeTuple("age", "int"));
	testTupleVector.push_back(AttributeTypeTuple("city", "string"));
	Table testTable2(testTupleVector);

	values.clear();
	values.push_back("37");
	values.push_back("Liverpool");
	testTable1.insert(Record(values));
	values.clear();
	values.push_back("25");
	values.push_back("London");
	testTable1.insert(Record(values));
	database.addTable(testTable2, "Age and Location");

	Table crossedTable = testTable1.crossJoin(testTable2);
	database.addTable(crossedTable, "Crossed Table");

	vector<AttributeTypeTuple> crossedTuples = crossedTable.getAttributes();

	if (crossedTable.getSize() != 4)
		BOOST_ERROR("Incorrect number of Records after CrossJoin");
	if (crossedTuples.size() != 4)
		BOOST_ERROR("Incorrect number of Attributes after CrossJoin");
	else
	{
		if (crossedTuples[0].getAttribute().compare("name") != 0)
			BOOST_ERROR("First Attribute is incorrect");
		if (crossedTuples[1].getAttribute().compare("born") != 0)
			BOOST_ERROR("Second Attribute is incorrect");
		if (crossedTuples[2].getAttribute().compare("age") != 0)
			BOOST_ERROR("Third Attribute is incorrect");
		if (crossedTuples[3].getAttribute().compare("city") != 0)
			BOOST_ERROR("Fourth Attribute is incorrect");
	}

	string query = "SELECT * ";
	query += "Crossed Table ";
	query += "(name == Bob && age != 25) || (name == Sally && city != London)";
	Table wrongInfo = database.query(query);

	if (wrongInfo.getSize() != 2)
		BOOST_ERROR("Query did not return the correct number of Records in table");

}

BOOST_AUTO_TEST_CASE(AttributeTypeTuple_constructor)
{
	AttributeTypeTuple test = AttributeTypeTuple("one","two");
	BOOST_CHECK((test.getAttribute() == "one") && (test.getType() == "two"));
}

BOOST_AUTO_TEST_CASE(AttributTypeTuple_empty)
{
	AttributeTypeTuple test = AttributeTypeTuple("","");
	BOOST_CHECK((test.getAttribute() == "") && (test.getType() == ""));
}

BOOST_AUTO_TEST_CASE(Record_constructor)
{
	vector<string> newvec;
	newvec.push_back("one");
	newvec.push_back("two");
	newvec.push_back("three");
	Record test = Record(newvec);
	string one = test.getValue(0);
	string two = test.getValue(1);
	string three = test.getValue(2);
	//Check get.value
	BOOST_CHECK(one.compare("one") && two.compare("two") && three.compare("three"));
	one = test[0];
	two = test[1];
	three = test[2];
	//Check operator []
	BOOST_CHECK(one.compare("one") && two.compare("two") && three.compare("three"));
}

BOOST_AUTO_TEST_CASE(Record_empty)
{
	vector<string> newvec;
	Record test = Record(newvec);
	string testout = test.getValue(0);
	testout = test.getValue(1);
	testout = test[0];
	testout = test[1];
}

BOOST_AUTO_TEST_CASE(Record_addval_removeval)
{
	vector<string> newvec;
	Record test = Record(newvec);
	test.addValue("string");
	string checkstring = test.getValue(0);
	BOOST_CHECK(checkstring == "string");
	test.removeValue(0);
	checkstring = test.getValue(0);
	BOOST_CHECK(checkstring.compare("string") == 0);
	test.removeValue(1);
}

BOOST_AUTO_TEST_CASE(Table_constructor)
{
	Table testtable = Table();
	vector<AttributeTypeTuple> newvec;
	newvec.push_back(AttributeTypeTuple("test1","int"));
	newvec.push_back(AttributeTypeTuple("test2","int"));
	newvec.push_back(AttributeTypeTuple("test3","int"));
	Table test2table = Table(newvec);
	testtable.add(AttributeTypeTuple("test1","int"));
}
