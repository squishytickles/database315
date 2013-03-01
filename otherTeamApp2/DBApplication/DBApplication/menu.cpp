#include "database.h"
#include <fstream>
#include <vector>
#include <cctype>
#include <iostream>

using namespace std;

void printTable(Table* table);
void printTable(Table table);
vector<string> csvToVector(string csv);
enum Table::RecordType whatIsType(string str);
Table::ColumnList csvGetAttrs(string csvAttrs, string csvRec1);
void populateDB(Database& db, string fileListName);
vector<pair<string,string>> assemblePairVector(vector<string> attrs, vector<string> values);

int main()
{
	// create the database
	Database db = Database();
	populateDB(db,"inputFileList");

	cout << "Read in files specified in inputFileList, database populated with " << db.table_names().size() << " tables." << endl;

	int mainAns = 0;
	int custAns = 0;
	int restAns = 0;
	string userID, restID, rating, alcohol, parking;
	string payment, food, selectClause, whereClause;

	string mainprompt = "What category do you want to search?\n(1)Customers\n(2)Resturants\nOR\n(3)Print a table\n(4)Exit";

	while (1==1) {
		mainAns = 0;
		custAns = 0;
		restAns = 0;
		cout << endl;
		cout << "PROMPT" << endl;
		cout << "-----------------------------" << endl;
		cout << "Would you like to search from a category?" << endl;
		cout << "\t(1) Customers" << endl;
		cout << "\t(2) Resturants" << endl;
		cout << "Or would you like to perform an action?" << endl;
		cout << "\t(3) Print a table" << endl;
		cout << "\t(4) Join two tables" << endl;
		cout << "\t(5) Exit the program" << endl;
		cin >> mainAns;

		switch(mainAns) {
			case 1:
				{
					cout << "Find customers based on: " << endl
						 << "\t(1) Type of payment available" << endl
						 << "\t(2) Preferred cuisine" << endl
						 << "\t(3) By customer ID" << endl
						 << "\t(4) Create a cutom query" << endl
						 << "\t(5) Go back to main menu" << endl;
					cin >> custAns;
					break;
				}
			case 2:
				{
					cout << "Find restaurants based on: " << endl
						 << "\t(1) Rating" << endl
						 << "\t(2) Alcohol served" << endl
						 << "\t(3) Parking available" << endl
						 << "\t(4) Type of cuisine offered" << endl
						 << "\t(5) Type of payment accepted" << endl
						 << "\t(6) By restaurant ID" << endl
						 << "\t(7) Create a custom query" << endl
						 << "\t(8) Go back to main menu" << endl; 
					cin >> restAns;
					break;
				}
			case 3: 
				{
					cout << "Table Names: " << endl;
					for (int i = 0; i < db.table_names().size(); i ++) {
						cout << i << ": " << db.table_names()[i] << endl;
					}

					string table;
					cout << "Which table do you want to print?" << endl;
					cin >> table;
					printTable(db.table_if_exists(table));
					break;
				}
			case 4:
				{	
					cout << "Table Names: " << endl;
					for (int i = 0; i < db.table_names().size(); i ++) {
						cout << i << ": " << db.table_names()[i] << endl;
					}

					Table* firstTable;
					Table* secondTable;
					Table joinedTable;

					string table1, table2;
					cout << endl << "Enter first table name" << endl;
					cin >> table1;
					cout << "Enter second table name" << endl;
					cin >> table2;

					cout << "Thinking... this might take some time..." <<endl;
					firstTable = db.table_if_exists(table1);
					secondTable = db.table_if_exists(table2);

					joinedTable = firstTable->cross_join(*secondTable);
					printTable(joinedTable);

					break;
				}
			case 5:
				{
					return 0;
				}
			default: 
				{
					cout << "Sure you typed that in right?" << endl;
				}
		}

		if (custAns != 0) {
			switch(custAns) {
				case 1:
					{
						cout << "Enter payment type: " << endl;
						cin >> payment;

						Table* result = db.query("userID", "userpayment.csv", "Upayment = '" + payment + "'");
						printTable(result);
						break;
					}
				case 2:
					{
						cout << "Enter cuisine type: " << endl;
						cin >> food;

						Table* result = db.query("userID", "usercuisine.csv", "Rcuisine = '" + food + "'");
						printTable(result);
						break;
					}
				case 3:
					{
						cout << "Enter customer ID: " << endl;
						cin >> userID;

						Table* result = db.query("*", "userprofile.csv", "userID = '" + userID + "'");
						printTable(result);
						break;
					}
				case 4:
					{
						cout << "Enter a select clause (comma separated list): " << endl;
						cin.ignore();
						getline(cin,selectClause);
						cout << "Enter a where clause: " << endl;
						getline(cin,whereClause);

						Table* result = db.query(selectClause, "userprofile.csv", whereClause);
						printTable(result);
						break;
					}
				default:
					{ }
			}
		}

		if (restAns != 0) {
			switch(restAns) {
				case 1:
					{
						cout << "Enter rating: " << endl;
						cin >> rating;

						Table* result = db.query("placeID", "rating_final.csv", "rating = '" + rating + "'");
						printTable(result);
						break;
					}
				case 2:
					{
						cout << "Enter alcohol type (No_Alcohol_Served, Wine-Beer, or Full_Bar): " << endl;
						cin >> alcohol;

						Table* result = db.query("placeID", "geoplaces2.csv", "alcohol = '" + alcohol + "'");
						printTable(result);
						break;
					}
				case 3:
					{
						cout << "Enter parking type (none, yes, public, valet parking, fee): " << endl;
						cin >> parking;

						Table* result = db.query("placeID", "chefmozparking.csv", "parking_lot = '" + parking + "'");
						printTable(result);
						break;
					}
				case 4:
					{
						cout << "Enter cuisine type: " << endl;
						cin >> food;

						Table* result = db.query("placeID", "chefmozcuisine.csv", "Rcuisine = '" + food + "'");
						printTable(result);
						break;
					}
				case 5:
					{
						cout << "Enter payment type: " << endl;
						cin >> payment;

						Table* result = db.query("placeID", "chefmozaccepts.csv", "Rpayment = '" + payment + "'");
						printTable(result);
						break;
					}
				case 6:
					{
						cout << "Enter restaurant ID: " << endl;
						cin >> restID;

						Table* result = db.query("*", "geoplaces2.csv", "placeID = '" + restID + "'");
						printTable(result);
						break;
					}
				case 7:
					{
						cout << "Enter a select clause (comma separated list): " << endl;
						cin.ignore();
						getline(cin,selectClause);
						cout << "Enter a where clause: " << endl;
						getline(cin,whereClause);

						Table* result = db.query(selectClause, "geoplaces2.csv", whereClause);
						printTable(result);
						break;
					}
				default:
					{ }
			}	  
		}
	}
}

void printTable(Table* table)
{ 
	printTable(*table);
}

void printTable(Table table) {
	cout << "RESULT TABLE: " << endl;
	cout << "-----------------------------" << endl;
	for(int i=0; i<table.size(); i++)
	{
		Record::RecordIterator begin = table.at(i).begin();
		Record::RecordIterator end = table.at(i).end();

		for(Record::RecordIterator it = begin; it != end; it++)
		{
			cout << it->first << ":\t\t" << it->second << endl;
		}

		cout << endl;
	}
	cout << "-----------------------------" << endl;
	cout << "END OF TABLE" << endl;
}

// convert a csv string to a vector of strings
vector<string> csvToVector(string csv) {
	vector<string> res;
	string templine = "";
	
	for (int i = 0; i <= csv.length(); i ++) {
		if (csv.substr(i,1).compare(",") != 0 && i != csv.length()) {
			templine += csv.substr(i,1);
		} else {
			res.push_back(templine);
			templine.clear();
		}
	}
	return res;
}

// get type of string
enum Table::RecordType whatIsType(string str) {
	bool hasDecimal = false;
	bool hasDigit = false;
	bool hasLetter = false;
	bool hasNonDigit = false;
	
	for (int i = 0; i < str.size(); i ++) {
		if (str[i] == '?' && str.size() == 1) return Table::RecordType::varchar;
		if (str[i] == '.') hasDecimal = true;
		if (isdigit(str[i])) hasDigit = true;
		if (isalpha(str[i])) hasLetter = true;
		if (!isdigit(str[i])) hasNonDigit = true;
	}
	
	if (hasDecimal && hasDigit && !hasLetter) return Table::RecordType::floating;
	if (hasDigit && !hasDecimal && !hasLetter && !hasNonDigit) return Table::RecordType::integer;
	
	return Table::RecordType::varchar;
}

// convert a csv string to a vector of strings
Table::ColumnList csvGetAttrs(string csvAttrs, string csvRec1) {
	Table::ColumnList res;
	string templine = "";
	
	vector<string> attrs = csvToVector(csvAttrs);
	vector<string> records = csvToVector(csvRec1);
	
	for (int i = 0; i < attrs.size(); i ++) {
		res.push_back(make_pair(attrs[i],whatIsType(records[i])));
	}
	
	return res;
}

// read in the files and return a database
void populateDB(Database& db, string fileListName) {
	cout << "Loading files specified in inputFileList, gimmie a minute..." << endl;
	// create the database to return
	
	// read in the inputFileList
	vector<string> inputFiles;
	string line;
	ifstream inputFile(fileListName);
	if (inputFile.is_open()) {
		while (inputFile.good()) {
			getline(inputFile,line);
			inputFiles.push_back(line);
			//cout << "INSTRUCTED TO READ IN " + line << endl;
		}
		
		inputFile.close();
	}
	
	// create a table for each inputFile
	for (int i = 0; i < inputFiles.size(); i ++) {
		string newTableName = inputFiles[i];
		//cout << "BEGINNING TO INPUT " + newTableName << endl;
				
		// open the input file, read it in to dataLines
		string line;
		vector<string> dataLines;
		ifstream inputFile(inputFiles[i]);
		if (inputFile.is_open()) {
			while (inputFile.good()) {
				getline(inputFile,line);
				dataLines.push_back(line);
			}
		}
		inputFile.close();
		
		// add the attributes to the table
		Table::ColumnList tableColumns = csvGetAttrs(dataLines[0],dataLines[1]);
		vector<string> attrs = csvToVector(dataLines[0]);

		Table* newTable = new Table(tableColumns);
		
		/*cout << "table cols: " << endl;
		for (int j = 0; j < tableColumns.size(); j ++) {
			cout << tableColumns.at(j).first << " " << tableColumns.at(j).second << endl;
		}*/

		//system("PAUSE");

		// add the records to the table
		for (int j = 1; j < dataLines.size()-1; j ++) {
			vector<string> values = csvToVector(dataLines[j]);
			Record* newRecord = new Record(assemblePairVector(attrs,values));
			/*cout << "record: " << endl;
			for (int k = 0; k < attrs.size(); k ++) {
				cout << newRecord->get<string>(attrs[k]) << endl;
			}*/

			newTable->insert(*newRecord);
		}
	
		//cout << newTableName << " has finished size " << newTable->size() << endl;

		//system("PAUSE");
		db.add_table(inputFiles[i],newTable);
	}
}

vector<pair<string,string>> assemblePairVector(vector<string> attrs, vector<string> values) {
	if (attrs.size() != values.size()) {
		throw exception("Can't assemble Pair Vector!");
	}

	vector<pair<string,string>> ret;
	for (int i = 0; i < attrs.size(); i ++) {
		ret.push_back(make_pair(attrs[i],(string)values[i]));
	}

	return ret;
}
