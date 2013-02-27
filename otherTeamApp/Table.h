#pragma once

class DBTEAM01_API Table {
public:
	typedef std::pair <int, std::string>	Attribute;	/// type/name pair
	typedef std::vector <Record>::iterator	Iterator;	/// table iterator

	/// @brief Empty constructor creates a table with no rows or columns.
	Table (void);

	/// @brief Construct a table from a list of attribute types and names.
	/// @param attrList The list of attribute types and names.
	Table (std::vector <Attribute> const& attrList);

	/// @brief Destructor.
	~Table (void);

	/// @brief Add a column to the end of table with the attribute type/name.
	/// @param attribute The type/name pair.
	/// @throw Duplicate Cannot add a duplicate attribute to a table.
	/// @throw InvalidType The attribute must have a valid type code.
	void addAttribute (Attribute const& attribute);

	/// @brief Remove a column from the table with the attribute type/name.
	/// @param attribute The type/name pair.
	/// @throw NotFound Cannot remove a nonexistent attribute from a table.
	void removeAttribute (Attribute const& attribute);

	/// @brief Get the number of records in the table.
	/// @return The number of record in the table.
	int getSize (void);
	
	/// @brief Add a record to the end of table
	/// @param record The record to be added
	/// @throw InvalidType The record must have a type that matches the table attribute list.
	void insertRecord (Record const& record);

	/// @brief Iterator to get individual records from a table.
	/// @return An iterator that points to the beginning of the table.
	Iterator begin (void);

	/// @brief Iterator to get individual records from a table.
	/// @return An iterator that points to the end of the table.
	Iterator end (void);

	/// @brief Rename an attribute in the table.
	/// @param newName The new name.
	/// @param oldName The name to be replaced.
	/// @throw Duplicate The newName must not be in the attribute list.
	/// @throw NotFound The oldName must be in the attribute list.
	void renameAttribute (std::string const& newName, std::string const& oldName);

	/// @brief Cross join two tables.
	/// @param first The first table.
	/// @param second The second table.
	/// @return The joined table.
	static Table crossJoin (Table const& first, Table const& second);

	/// @brief Get the sum of values for a column.
	/// @param attrName The name of the column attribute.
	/// @return The sum int.
	/// @throw NotFound The attrName must be in the attribute list.
	/// @throw InvalidType The column must be of type INT.
	int sumInt (std::string const& attrName);

	/// @brief Get the sum of values for a column.
	/// @param attrName The name of the column attribute.
	/// @return The sum float.
	/// @throw NotFound The attrName must be in the attribute list.
	/// @throw InvalidType The column must be of type FLOAT.
	float sumFloat (std::string const& attrName);

	/// @brief Get the minimum entry for a column.
	/// @param attrName The name of the column attribute.
	/// @return The minimum int.
	/// @throw NotFound The attrName must be in the attribute list.
	/// @throw InvalidType The column must be of type INT.
	float minInt (std::string const& attrName);

	/// @brief Get the minimum entry for a column.
	/// @param attrName The name of the column attribute.
	/// @return The minimum float.
	/// @throw NotFound The attrName must be in the attribute list.
	/// @throw InvalidType The column must be of type FLOAT.
	float minFloat (std::string const& attrName);

	/// @brief Get the maximum entry for a column.
	/// @param attrName The name of the column attribute.
	/// @return The maximum int.
	/// @throw NotFound The attrName must be in the attribute list.
	/// @throw InvalidType The column must be of type INT.
	float maxInt (std::string const& attrName);

	/// @brief Get the maximum entry for a column.
	/// @param attrName The name of the column attribute.
	/// @return The maximum float.
	/// @throw NotFound The attrName must be in the attribute list.
	/// @throw InvalidType The column must be of type FLOAT.
	float maxFloat (std::string const& attrName);

	/// @brief Get the count of non-null entries for a column.
	/// @param attrName The name of the column attribute.
	/// @return The count of non-null entries.
	/// @throw NotFound The attrName must be in the attribute list.
	int count (std::string const& attrName);

private:
	std::vector <Attribute> attributes;
	std::vector <Record> records;
};
