#include "DBteam01.h"
#include "Database.h"
#include <fstream>
#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

void printTable(Table table)
{ 
	cout << "RESULT TABLE: " << endl;
	for(int i=0; i<table.getSize(); i++)
	{
		Table::Iterator begin = table.begin();
		Table::Iterator end = table.end();
		for(Table::Iterator it = begin; it != end; it++)
		{
			for(int j=0; j<it->size(); j++)
			{
				cout << it->getString(j) << endl;
			}

			cout << endl;
		}
	}
}

// convert a csv string to a vector of strings
vector<string> csvToVector(string csv) {
	vector<string> res;
	string templine = "";
	
	for (int i = 0; i < csv.length(); i ++) {
		if (csv.substr(i,1).compare(",") != 0 && i != csv.length() - 1) {
			templine += csv.substr(i,1);
		} else {
			res.push_back(templine);
			templine.clear();
		}
	}
	return res;
}

// get type of string
int whatIsType(string str) {
	bool hasDecimal = false;
	bool hasDigit = false;
	bool hasLetter = false;
	
	for (int i = 0; i < str.size(); i ++) {
		if (str[i] == '?' && str.size() == 1) return STRING;
		if (str[i] == '.') hasDecimal = true;
		if (isdigit(str[i])) hasDigit = true;
		if (isalpha(str[i])) hasLetter = true;
	}
	
	if (hasDecimal && hasDigit && !hasLetter) return FLOAT;
	if (hasDigit && !hasDecimal && !hasLetter) return INT;
	
	return STRING;
}

// convert a csv string to a vector of strings
vector<Table::Attribute> csvGetAttrs(string csvAttrs, string csvRec1) {
	vector<Table::Attribute> res;
	string templine = "";
	
	vector<string> attrs = csvToVector(csvAttrs);
	vector<string> records = csvToVector(csvRec1);
	
	for (int i = 0; i < attrs.size(); i ++) {
		res.push_back(Table::Attribute(whatIsType(records[i]),attrs[i]));
		cout << "new attr(" << whatIsType(records[i]) << attrs[i] << ")" << endl;
	}
	
	return res;
}

// read in the files and return a database
Database populateDB(string fileListName) {
	// create the database to return
	Database db = Database();
	
	// read in the inputFileList
	vector<string> inputFiles;
	string line;
	ifstream inputFile(fileListName);
	if (inputFile.is_open()) {
		while (inputFile.good()) {
			getline(inputFile,line);
			inputFiles.push_back(line);
			cout << "INSTRUCTED TO READ IN " + line << endl;
		}
		
		inputFile.close();
	}
	
	// create a table for each inputFile
	Table newTable;
	vector<string>dataLines;
	Record newRecord;

	for (int i = 0; i < inputFiles.size(); i ++) {
		cout << "BEGINNING TO INPUT " + inputFiles[i] << endl;
		string line;
		string newTableName = inputFiles[i];
		
		system("PAUSE");

		dataLines.clear();
		
		// open the input file, read it in to dataLines
		ifstream inputFile(inputFiles[i]);
		if (inputFile.is_open()) {
			while (inputFile.good()) {
				getline(inputFile,line);
				dataLines.push_back(line);
			}
		}
		inputFile.close();
		
		// add the attributes to the table
		newTable = Table(csvGetAttrs(dataLines[0],dataLines[1]));

		system("PAUSE");
		
		// add the records to the table

		/*
		 * PROBLEM: after calling insertRecord(), the size does not increase
					something is wrong with their insertRecord.
					addl, something is wrong in their database that is causing
					cannot access memory errors and brings up free.c

					test files tested for all these things, so I can't figure
					out the problem.
		 */

		for (int j = 1; j < dataLines.size()-1; j ++) {
			newRecord = Record(csvToVector(dataLines[j]));
			cout << "VECTOR dataLines[j]: " << dataLines[j] << endl;
			newTable.insertRecord(newRecord);
			cout << "newrecord size " << newRecord.size() << endl;
		}

		cout << "newtable size " << newTable.getSize() << endl;

		printTable(newTable);

		system("PAUSE");

		db.addTable(inputFiles[i],newTable);
	}
	
	return db;
}

int main()
{
	// create the database
	Database db = populateDB("inputFileList");

	cout << "Read in files specified in inputFileList, database populated with " << db.listTables().size() << " tables." << endl;

	int mainAns = 0;
	int custAns = 0;
	int restAns = 0;
	string userID, restID, rating, alcohol, parking;
	string payment, food, selectClause, whereClause;

	cout << "What category would you like to search in?" << endl
		 << "(1) Customers" << endl
		 << "(2) Restaurants" << endl
		 << "(3) Exit" << endl;
	cin >> mainAns;

	switch(mainAns) {
		case 1:
			{
				cout << "Find customers based on: " << endl
					 << "(1) Type of payment available" << endl
					 << "(2) Preferred cuisine" << endl
					 << "(3) By customer ID" << endl
					 << "(4) Create a cutom query" << endl
					 << "(5) Go back to main menu" << endl;
				cin >> custAns;
				break;
			}
		case 2:
			{
				cout << "Find restaurants based on: " << endl
					 << "(1) Rating" << endl
					 << "(2) Alcohol served" << endl
					 << "(3) Parking available" << endl
					 << "(4) Type of cuisine offered" << endl
					 << "(5) Type of payment accepted" << endl
					 << "(6) By restaurant ID" << endl
					 << "(7) Create a custom query" << endl
					 << "(8) Go back to main menu" << endl; 
				cin >> restAns;
				break;
			}
		case 3:
			{
				return 0;
			}
	}

	switch(custAns) {
		case 1:
			{
				cout << "Enter payment type: " << endl;
				cin >> payment;

				vector<string> select; 
				select.push_back("userID");

				Table result = db.query(select, "userpayment.csv", "Upayment = " + payment);
				printTable(result);
				break;
			}
		case 2:
			{
				cout << "Enter cuisine type: " << endl;
				cin >> food;

				vector<string> select; 
				select.push_back("userID");

				Table result = db.query(select, "usercuisine.csv", "Rcuisine = " + food);
				printTable(result);
				break;
			}
		case 3:
			{
				cout << "Enter customer ID: " << endl;
				cin >> userID;

				vector<string> select; 
				select.push_back("*");

				Table result = db.query(select, "userprofile.csv", "userID = " + userID);
				printTable(result);
				break;
			}
		case 4:
			{
				cout << "Enter a select clause (comma separated list): " << endl;
				cin >> selectClause;
				cout << "Enter a where clause: " << endl;
				cin >> whereClause;

				Table result = db.query(csvToVector(selectClause), "userprofile.csv", whereClause);
				printTable(result);
				break;
			}
		case 5:
			{
				cout << "What category would you like to search in?" << endl
						<< "(1) Customers" << endl
						<< "(2) Restaurants" << endl
						<< "(3) Exit" << endl;
				cin >> mainAns;
				break;
			}
	}

	switch(restAns) {
		case 1:
			{
				cout << "Enter rating: " << endl;
				cin >> rating;

				vector<string> select; 
				select.push_back("placeID");

				Table result = db.query(select, "rating_final.csv", "rating = " + rating);
				printTable(result);
				break;
			}
		case 2:
			{
				cout << "Enter alcohol type (No_Alcohol_Served, Wine-Beer, or Full_Bar): " << endl;
				cin >> alcohol;

				vector<string> select; 
				select.push_back("placeID");

				Table result = db.query(select, "geoplaces2.csv", "alcohol = " + alcohol);
				printTable(result);
				break;
			}
		case 3:
			{
				cout << "Enter parking type (none, yes, public, valet parking, fee): " << endl;
				cin >> parking;

				vector<string> select; 
				select.push_back("placeID");

				Table result = db.query(select, "chefmozparking.csv", "parking_lot = " + parking);
				printTable(result);
				break;
			}
		case 4:
			{
				cout << "Enter cuisine type: " << endl;
				cin >> food;

				vector<string> select; 
				select.push_back("placeID");

				Table result = db.query(select, "chefmozcuisine.csv", "Rcuisine = " + food);
				printTable(result);
				break;
			}
		case 5:
			{
				cout << "Enter payment type: " << endl;
				cin >> payment;

				vector<string> select; 
				select.push_back("placeID");

				Table result = db.query(select, "chefmozaccepts.csv", "Rpayment = " + payment);
				printTable(result);
				break;
			}
		case 6:
			{
				cout << "Enter restaurant ID: " << endl;
				cin >> restID;

				vector<string> select; 
				select.push_back("*");

				Table result = db.query(select, "geoplaces2.csv", "placeID = " + restID);
				printTable(result);
				break;
			}
		case 7:
			{
				cout << "Enter a select clause (comma separated list): " << endl;
				cin >> selectClause;
				cout << "Enter a where clause: " << endl;
				cin >> whereClause;

				Table result = db.query(csvToVector(selectClause), "geoplaces2.csv", whereClause);
				printTable(result);
				break;
			}
		case 8:
			{
				cout << "What category would you like to search in?" << endl
						<< "(1) Customers" << endl
						<< "(2) Restaurants" << endl
						<< "(3) Exit" << endl;
				cin >> mainAns;
				break;
			}
	}	  
	
	system("PAUSE");
	return 0;
}