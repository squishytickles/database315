#pragma once

#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>
using namespace std;

class Token
{
public:
//	Token(void);
//	~Token(void);

	Token (int k);
	Token (int k, float val);
	Token (int k, string n);
//	Token (int k, Date d);	// TODO: parse dates

	int kind;	// what kind of token
	float value;	// used for INT and FLOAT values
	string name;	// attribute names and string literals

	// Token kinds
	static const int NUMBER		= 0;	// integer or floating point literal
	static const int STRING		= 1;	// string literal
	static const int DATE		= 2;	// date literal
	static const int ATTRIBUTE	= 3;	// attribute name
	static const int LPAREN		= 4;	// (
	static const int RPAREN		= 5;	// )
	static const int AND		= 6;	// keyword AND
	static const int OR			= 7;	// keyword OR
	static const int EQ			= 8;	// =
	static const int NEQ		= 9;	// !=
	static const int LT			= 10;	// <
	static const int LTE		= 11;	// >
	static const int GT			= 12;	// <=
	static const int GTE		= 13;	// >=
};

queue <Token> getTokens (string const& str);
