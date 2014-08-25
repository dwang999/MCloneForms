// Entry.cpp

#include "stdafx.h"
#include "Entry.h"

// Operation Overload

std::ostream& operator<<(std::ostream& os, const Entry &entry)
{
	os << entry.date << "/" << entry.category << "/" << entry.subCategory << "/" 
		<< entry.description << "/" << std::fixed << std::setprecision(2) << entry.amount << "/";
	return os;
}


// Public Constructors and Destructors
Entry::Entry(time_t date, std::string category, std::string subCategory, 
			 std::string description, float amount)
{
	this -> date = date;
	this -> category = category;
	this -> subCategory = subCategory;
	this -> description = description;
	this -> amount = amount;
}

Entry::~Entry(){}