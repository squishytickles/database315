#pragma once

#ifdef DBTEAM01_EXPORTS
#define DBTEAM01_API __declspec(dllexport)
#else
#define DBTEAM01_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

/// attribute type codes
#define	INT	1
#define FLOAT	2
#define STRING	3
#define DATE	4

#include "Date.h"
#include "Exception.h"
#include "Record.h"
#include "Table.h"
