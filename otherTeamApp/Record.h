/// @author Hayden Wood

#pragma once

#include "DBteam01.h"

/// A record/tuple where all values are stored as a vector of C++ strings.
class DBTEAM01_API Record {
public:

	/// @brief Empty constructor.
	Record (void);

	/// @brief Construct a record with n elements initialized to "".
	/// @param n The number of elements to initially create.
	explicit Record (int n);

	/// @brief Create a record from a vector of values.
	/// @param v The vector of values.
	explicit Record (std::vector <std::string> const& v);

	/// @brief Destructor.
	~Record (void);

	/// @brief Return the number of elements in the record.
	/// @return The number of elements in the record.
	int size (void) const;

	/// @brief Add column to the end of the vector.
	/// @param value The value to be inserted in the new column.
	void addColumn (std::string value);

	/// @brief Remove a column from the vector.
	/// @param index The index of the column to be removed.
	void removeColumn (int index);

	/// @brief Get an integer value from a column.
	/// @param index The index of the column containing the value.
	/// @return An integer value.
	int getInt (int index) const;

	/// @brief Get an float value from a column.
	/// @param index The index of the column containing the value.
	/// @return A float value.
	float getFloat (int index) const;

	/// @brief Get a string value from a column.
	/// @param index The index of the column containing the value.
	/// @return A string value.
	std::string getString (int index) const;

	/// @brief Get a date value from a column.
	/// @param index The index of the column containing the value.
	/// @return A date value.
	Date getDate (int index) const;

	/// @brief Set a column element to NULL/empty string.
	/// @param index The index of the column.
	void setNull (int index);

	/// @brief Set a column element to an integer value.
	/// @param index The index of the column.
	/// @param value The integer value.
	void setInt (int index, int value);

	/// @brief Set a column element to  a float value.
	/// @param index The index of the column.
	/// @param value The float value.
	void setFloat (int index, float value);

	/// @brief Set a column element to a string value
	/// @param index The index of the column.
	/// @param value The string value.
	void setString (int index, std::string const& value);
	
	/// @brief Set a column element to a date value.
	/// @param index The index of the column.
	/// @param value The date value.
	void setDate (int index, Date const& value);

private:

	std::vector <std::string> vec;
};