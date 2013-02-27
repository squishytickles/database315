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
		string line;
		string newTableName = inputFiles[i];
		
		vector<string> dataLines;
		
		// open the input file, read it in to dataLines
		inputFile(inputFiles[i]);
		if (inputFile.is_open()) {
			while (inputFile.good()) {
				getline(inputFile,line);
				dataLines.push_back(line);
			}
		}
		inputFile.close();
		
		// add the attributes to the table
		Table newTable = Table(csvGetAttrs(dataLines[0],dataLines[1]);
		
		// add the records to the table
		for (int j = 1; j < dataLines.size(); j ++) {
			newTable.push_back(Record(csvToVector(dataLines[j])));
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

// convert a csv string to a vector of strings
vector<Attribute> csvGetAttrs(string csvAttrs, string csvRec1) {
	vector<Attribute> res;
	string templine = "";
	
	vector<string> attrs = csvToVector(csvAttrs);
	vector<string> records = csvToVecotr(csvRec1);
	
	for (int i = 0; i < attrs.size(); i ++) {
		res.push_back(Attribute(whatIsType(records[i]),attrs[i]));
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
		
		
	