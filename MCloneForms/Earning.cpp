// Earning.cpp

#include "stdafx.h"
#include "Earning.h"

// Operation Overload

std::ostream& operator<<(std::ostream& os, const Earning &earning)
{
	os << earning.date << "/" << std::fixed << std::setprecision(2) << earning.amount << "/";
	return os;
}


// Public Constructors and Destructors
Earning::Earning(time_t date, float amount)
{
	this -> date = date;
	this -> amount = amount;
}

Earning::~Earning(){}