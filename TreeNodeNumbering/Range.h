#ifndef _RANGE_H
#define _RANGE_H 1
using namespace std;
#include "stdafx.h"
#include <time.h>
#include <stdlib.h>
#include <sstream>

class Range
{
private:
	UInt32 lo;
	UInt32 hi;

public:
	Range(UInt32 _lo, UInt32 _hi)
	{
		this->lo = _lo;
		this->hi = _hi;
	}

	UInt32 GetDistance()
	{
		return (this->hi - this->lo + 1);
	}

	std::string PrintRange()
	{
		std::ostringstream ss;
		ss << "( " << this->lo << " To " << this->hi << " )";
		return ss.str();
	}

	void GenerateRange(UInt32 level, UInt32 index)
	{
		srand(static_cast<UInt32>(time(NULL)));
		this->lo = GenerateID(level, index, 1);
		this->hi = GenerateID(level, index, 1 + rand() % (MAX_CHILDREN_PER_NODE-1));  //Minimum one child range per node is assumed	
	}

	void UpdateRange(UInt32 increment)
	{
		this->hi += increment;
	}

	bool IsInRange(UInt32 val)
	{
		return ((val >= this->lo) && (val <= this->hi)) ? true : false;
	}

	static UInt32 GenerateID(UInt32 level, UInt32 index, UInt32 id)
	{
		UInt32 temp = ((level * 10000) + index) * 1000 + id;
		return temp;
	}
};

#endif