#include "Database.h"

Record TableIterator::get() {
	return TableIterator::table[i];
}

void TableIterator::next() {
	i++;
	
	if (i > TableIterator::table.getSize())
		i = 0;
}