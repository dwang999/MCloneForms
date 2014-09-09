// Income.cpp

#include "stdafx.h"
#include "Income.h"

// Operation Overload

std::ostream& operator<<(std::ostream& os, const Income &income)
{
	os << income.id << "/" << income.effectiveDate << "/" << std::fixed << std::setprecision(2) << income.amount << "/";
	return os;
}


// Public Constructors and Destructors
Income::Income(int id, time_t effectiveDate, float amount)
{
	this -> id = id;
	this -> effectiveDate = effectiveDate;
	this -> amount = amount;
}

Income::~Income(){}




Income Income::parseTokens(std::string str)
{	
	// Get Tokens
	std::string delim = "/";
	std::vector<std::string> tokens;
	tokens.reserve(Income::NUMOFMEMBERVARIABLES);
	unsigned int delimPos = str.find(delim);
	int start = 0;
	while (delimPos != std::string::npos)
	{
		std::string token = str.substr(start, delimPos - start);
		start = delimPos + 1;
		delimPos = str.find(delim, start);
		tokens.push_back(token);
	}

	if (tokens.size() != Income::NUMOFMEMBERVARIABLES)
	{
		throw std::runtime_error("Income::parseTokens : Incorrect number of variables in earnings");
	}

	// Parse tokens 
	int id;
	std::time_t effectiveDate;
	float amount;


	// Format: [ID]/[effectiveDate]/[Amount]

	for (int i = 0; i < Income::NUMOFMEMBERVARIABLES; i++)
	{
		switch (i)
		{
		case 0: // id
			id = atoi(tokens[i].c_str());
			break;
		case 1: // effectiveDate
			effectiveDate = std::stoi(tokens[i]);
			break;
		case 2: // amount
			amount = std::stof(tokens[i]);
			break;
		}
	}

	return Income(id, effectiveDate, amount);
}