#include "Database.h"

int Date::compare(Date& other) {
	if (year < other.getYear()) {
		return -1;
	} 
	else if (year > other.getYear()) {
		return 1;
	}
	
	if (month < other.getMonth()) {
		return -1;
	}
	else if (month > other.getMonth()) {
		return 1;
	}
	
	if (day < other.getDay()) {
		return -1;
	}
	else if (day > other.getDay()) {
		return 1;
	}
	
	if (day == other.getDay() && month == other.getMonth() && year == other.getYear()) {
		return 0;
	}
}

int Date::getDay() {
	return day;
}

int Date::getMonth() {
	return month;
}

int Date::getYear() {
	return year;
}
	