// Entry.cpp

#include "stdafx.h"
#include "Entry.h"

// Operation Overload

std::string Entry::toString() const
{
	std::stringstream ss;
	ss << id << "/" << date << "/" << category << "/" 
		<< description << "/" << std::fixed << std::setprecision(2) << amount << "/";
	return ss.str();
}


// Public Constructors and Destructors
Entry::Entry(int id, time_t date, std::string category, 
			 std::string description, float amount)
{
	this -> id = id;
	this -> date = date;
	this -> category = category;
	this -> description = description;
	this -> amount = amount;
}


Entry::~Entry(){}
