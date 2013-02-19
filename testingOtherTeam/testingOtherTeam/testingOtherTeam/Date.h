#pragma once

#include <iostream>

class Date {

public:

	/// Empty constructor
	Date (void);

	/// Constructor
	Date (int year, int month, int day);

	/// Destructor
	~Date (void);
	
	/// Get the year from a date.
	int year (void) const;

	/// Get the month from a date.
	int month (void) const;
	
	/// Get the day from a date.
	int day (void) const;

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
