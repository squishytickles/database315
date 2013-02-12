#pragma once

#include <iostream>

class Date {

public:

	/// Empty constructor
	DBTEAM01_API Date (void);

	/// Constructor
	DBTEAM01_API Date (int year, int month, int day);

	/// Destructor
	DBTEAM01_API ~Date (void);
	
	/// Get the year from a date.
	DBTEAM01_API int year (void) const;

	/// Get the month from a date.
	DBTEAM01_API int month (void) const;
	
	/// Get the day from a date.
	DBTEAM01_API int day (void) const;

private:

	int arr [3];
};

/// Use dates for istreams.
std::istream& operator >> (std::istream& in, Date& date);

/// Use dates for ostreams.
std::ostream& operator << (std::ostream& out, Date const& date);

/// Equals operator for dates.
bool operator == (Date const& a, Date const& b);

/// Less-than operator for dates.
bool operator < (Date const& a, Date const& b);
