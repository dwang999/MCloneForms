// Income.cpp

#include "stdafx.h"
#include "Income.h"

// Operation Overload

std::string Income::toString() const
{
	std::stringstream ss;
	ss << id << "/" << effectiveDate << "/" << std::fixed << std::setprecision(2) << amount << "/";
	return ss.str();
}


// Public Constructors and Destructors
Income::Income(int id, time_t effectiveDate, float amount)
{
	this -> id = id;
	this -> effectiveDate = effectiveDate;
	this -> amount = amount;
}

Income::~Income(){}



