#pragma once

#include <exception>

class NotFound : public std::exception
{
	//
};

class Duplicate : public std::exception
{
	//
};

class InvalidType : public std::exception
{
	//
};

class InvalidQuery : public std::exception
{
	//
};