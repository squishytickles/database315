/// @author Hayden Wood

#pragma once

#include "DBteam01.h"

/// A record/tuple where all values are stored as a vector of C++ strings.
class Record {
public:

	/// @brief Empty constructor.
	DBTEAM01_API Record (void);

	/// @brief Construct a record with n elements initialized to "".
	/// @param n The number of elements to initially create.
	DBTEAM01_API explicit Record (int n);

	/// @brief Create a record from a vector of values.
	/// @param v The vector of values.
	DBTEAM01_API explicit Record (std::vector <std::string> const& v);

	/// @brief Destructor.
	DBTEAM01_API ~Record (void);

	/// @brief Return the number of elements in the record.
	/// @return The number of elements in the record.
	DBTEAM01_API int size (void) const;

	/// @brief Add column to the end of the vector.
	/// @param value The value to be inserted in the new column.
	DBTEAM01_API void addColumn (std::string value = "");

	/// @brief Remove a column from the vector.
	/// @param index The index of the column to be removed.
	DBTEAM01_API void removeColumn (int index);

	/// @brief Get an integer value from a column.
	/// @param index The index of the column containing the value.
	/// @return An integer value.
	DBTEAM01_API int getInt (int index) const;

	/// @brief Get an float value from a column.
	/// @param index The index of the column containing the value.
	/// @return A float value.
	DBTEAM01_API float getFloat (int index) const;

	/// @brief Get a string value from a column.
	/// @param index The index of the column containing the value.
	/// @return A string value.
	DBTEAM01_API std::string const& getString (int index) const;

	/// @brief Get a date value from a column.
	/// @param index The index of the column containing the value.
	/// @return A date value.
	DBTEAM01_API Date const& getDate (int index) const;

	/// @brief Set a column element to NULL/empty string.
	/// @param index The index of the column.
	DBTEAM01_API void setNull (int index);

	/// @brief Set a column element to an integer value.
	/// @param index The index of the column.
	/// @param value The integer value.
	DBTEAM01_API void setInt (int index, int value);

	/// @brief Set a column element to  a float value.
	/// @param index The index of the column.
	/// @param value The float value.
	DBTEAM01_API void setFloat (int index, float value);

	/// @brief Set a column element to a string value
	/// @param index The index of the column.
	/// @param value The string value.
	DBTEAM01_API void setString (int index, std::string const& value);
	
	/// @brief Set a column element to a date value.
	/// @param index The index of the column.
	/// @param value The date value.
	DBTEAM01_API void setDate (int index, Date const& value);

private:

	std::vector <std::string> vec;
};