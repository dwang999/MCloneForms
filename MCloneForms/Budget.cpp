// Budget.cpp

#include "stdafx.h"
#include "Budget.h"

// Operation Overload

std::string Budget::toString() const
{
	std::stringstream ss;
	ss << id << "/" << effectiveDate << "/" << category << "/" << std::fixed << std::setprecision(2) << amount << "/";
	return ss.str();
}


// Public Constructors and Destructors
Budget::Budget(int id, time_t effectiveDate, std::string category, float amount)
{
	this -> id = id;
	this -> effectiveDate = effectiveDate;
	this -> category = category;
	this -> amount = amount;
}


Budget::~Budget(){}
