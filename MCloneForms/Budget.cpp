// Budget.cpp

#include "stdafx.h"
#include "Budget.h"

// Operation Overload

std::ostream& operator<<(std::ostream& os, const Budget &budget)
{
	os << budget.id << "/" << budget.effectiveDate << "/" << budget.category << "/" 
		<< std::fixed << std::setprecision(2) << budget.amount << "/";
	return os;
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

Budget Budget::parseTokens(std::string str)
{	
	std::string delim = "/";
	std::vector<std::string> tokens;
	tokens.reserve(Budget::NUMOFMEMBERVARIABLES);
	unsigned int delimPos = str.find(delim);
	int start = 0;
	while (delimPos != std::string::npos)
	{
		std::string token = str.substr(start, delimPos - start);
		start = delimPos + 1;
		delimPos = str.find(delim, start);
		tokens.push_back(token);
	}

	if (tokens.size() != Budget::NUMOFMEMBERVARIABLES)
	{
		throw std::runtime_error("Budget::parseTokens : Incorrect number of variables in entrys");
	}
	// Parse tokens 
	int id;
	std::time_t effectiveDate;
	std::string category;
	float amount;

	// Format: [ID]/[EffectiveDate]/[Category]/[Amount]

	for (int i = 0; i < Budget::NUMOFMEMBERVARIABLES; i++)
	{
		switch (i)
		{
		case 0: // id
			id = atoi(tokens[i].c_str());
			break;
		case 1: // effective date
			effectiveDate = std::stoi(tokens[i]);
			break;
		case 2: // category
			category = tokens[i];
			break;
		case 3: // amount
			amount = std::stof(tokens[i]);

			break;
		}
	}

	return Budget(id, effectiveDate, category, amount);
}