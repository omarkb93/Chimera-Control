﻿#pragma once
#include <string>
#include "afxwin.h"
#include <vector>
#include "range.h"

struct variationRangeInfo
{
	double initialValue;
	double finalValue;
	unsigned int variations;
	bool leftInclusive;
	bool rightInclusive;
	bool operator==( const variationRangeInfo& v )
	{
		return (initialValue == v.initialValue && 
				 finalValue == v.finalValue && 
				 variations == v.variations &&
				 leftInclusive == v.leftInclusive &&
				 rightInclusive == v.rightInclusive);
	}
};


struct variableType
{
	std::string name;
	// whether this variable is constant or varies.
	bool constant;
	double constantValue = 0;
	bool active = false;
	bool overwritten = false;

	// records which scan dimension the variable is in.
	USHORT scanDimension=1;
	std::vector<variationRangeInfo> ranges;
	/// this stuff used to be in the keyHandler system.
	std::vector<double> keyValues;
	// this might just be redundant with constant above.
	bool valuesVary=false;
	bool operator==( const variableType& v )
	{
		bool rangeResult=true;
		if ( ranges.size( ) != v.ranges.size( ) )
		{
			rangeResult = false;
		}
		else
		{
			for ( auto rangeInc : range(ranges.size()) )
			{
				if ( !(ranges[rangeInc] == v.ranges[rangeInc] ))
				{
					rangeResult = false;
					break;
				}
			}
		}
		return ( name == v.name &&
				 constant == v.constant &&
				 constantValue == v.constantValue &&
				 active == v.active &&
				 overwritten == v.overwritten &&
				 scanDimension == v.scanDimension &&
				 rangeResult &&
				 keyValues == v.keyValues &&
				 valuesVary == v.valuesVary);
	}
};


