#include <cctype>

int main()
{
	// create the database
	Database db = populateDB("inputFileList");
	
	// now our menu and queries
	// ...
	
	return 0;
}

// read in the files and return a database
Database populateDB(string fileListName) {
	// create the database to return
	Database db = Database();
	
	// read in the inputFileList
	vector inputFiles;
	string line;
	ifstream inputFile(fileListName);
	if (inputFile.is_open()) {
		while (inputFile.good()) {
			getline(inputFile,line);
			inputFiles.push_back(line);
		}
		
		inputFile.close();
	}
	
	// create a table for each inputFile
	for (int i = 0; i < inputFiles.size(); i ++) {
		// create the table
		string newTableName = inputFiles[i];
		Table newTable = Table();
		
		// open the file specified by inputFiles file
		inputFile(inputFiles[i]);
		if (inputFile.is_open()) {
			// first line is all the attributes
			getline(inputFile,line);
			
			// get the attrs
			vector<string> attrs = csvToVector(line);
			
			// update the table with those attrs
			newTable = Table(attrs);		// FIX - need to figure out the types -- how to do?
				
			// now add the records
			while (inputFile.good()) {
				getline(inputFile,line);
				// get the values for the record
				vector<string> vals = csvToVector(line);
				
				// insert the new record
				Record newRecord = Record(vals);
				newTable.insertRecord(newRecord);
			}
		
			inputFile.close();
		}
	}
	
	return db;
}

// convert a csv string to a vector of strings
vector<string> csvToVector(string csv) {
	vector<string> res;
	string templine = "";
	
	for (int i = 0; i < csv.length(); i ++) {
		if (csv.substr(i,1).compare(",") != 0) {
			templine += csv.substr(i,1);
		} else {
			res.push_back(templine);
			templine.clear();
		}
	}
	
	return res;
}

// get type of string
string whatIsType(string str) {
	bool hasDecimal = false;
	bool hasDigit = false;
	bool hasLetter = false;
	
	for (int i = 0; i < str.size(); i ++) {
		if (str[i] == '?' && str.size() == 1) return "NULL";
		if (str[i] == '.') hasDecimal = true;
		if (isdigit(str[i])) hasDigit = true;
		if (isalpha(str[i])) hasLetter = true;
	}
	
	if (hasDecimal && hasDigit && !hasLetter) return "FLOAT";
	if (hasDigit && !hasDecimal && !hasLetter) return "INT";
	
	return "STRING";
}
		
		
	