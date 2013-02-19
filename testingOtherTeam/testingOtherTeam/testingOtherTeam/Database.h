#pragma once

/// @author Nicholas McHenry

#include "DBteam01.h"

typedef std::pair <std::string, Table> NamedTable;

class DBTEAM01_API Database {
//	std::vector <NamedTable> tables;
//	bool nameIsUnique(std::string name);
public:
	Database();

	/**
	* @brief Name and add a table to the database.
	* @param name any previously unused string
	* @param table A single table.
	* @exception Duplicate The name must not be the same as one provided previously.
	*/
	bool addTable(std::string name, Table table);

	/**
	* @brief Drop a table from the database.
	* @param name any previously stored name
	* @exception NotFound A table with the prvided name does not exist 
	*/
	bool dropTable(std::string name);

	/**
	* @brief Drop a table from the database.
	* @param name any previously stored name
	* @exception NotFound A table with the prvided name does not exist 
	*/
	std::vector<std::string> listTables();
	
	/**
	* @brief List the names associated with all stored tables.
	* @return A vector of strings representing table names.
	*/
	std::vector<Table> getTables();

	/// @brief perform a query
	/// @param select A vector of attribute names (can be a vector with a single "*" element).
	/// @param from A single table name.
	/// @param where An expression to be parsed (see assignment handout for details).
	/// @return A table that satisifies the constraints of the query.
	/// @throw NotFound Attribute names or table do not exist
	/// @throw InvalidType The where expression tries to compare incompatible types
	/// @throw InvalidQuery The where expression cannot be parsed (invalid syntax).
	Table query (std::vector<std::string> const& select,
		std::string const& from, std::string const& where);

	/// @brief delete records from a table
	/// @param select A vector of attribute names (can be a vector with a single "*" element).
	/// @param from A single table name.
	/// @param where An expression to be parsed (see assignment handout for details).
	/// @throw NotFound Attribute names or table do not exist
	/// @throw InvalidType The where expression tries to compare incompatible types
	/// @throw InvalidQuery The where expression cannot be parsed (invalid syntax).
	void deleteByQuery (std::vector<std::string> const& select,
		std::string const& from, std::string const& where);

	/**
	* @brief Get the number of tables.
	* @return An integer equal to the number of tables.
	*/
	int numTables();
};
