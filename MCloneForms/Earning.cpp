// Earning.cpp

#include "stdafx.h"
#include "Earning.h"

// Operation Overload

std::ostream& operator<<(std::ostream& os, const Earning &earning)
{
	os << earning.id << "/" << earning.date << "/" << std::fixed << std::setprecision(2) << earning.amount << "/";
	return os;
}


// Public Constructors and Destructors
Earning::Earning(int id, time_t date, float amount)
{
	this -> id = id;
	this -> date = date;
	this -> amount = amount;
}

Earning::~Earning(){}




Earning Earning::parseTokens(std::string str)
{	
	// Get Tokens
	std::string delim = "/";
	std::vector<std::string> tokens;
	tokens.reserve(Earning::NUMOFMEMBERVARIABLES);
	unsigned int delimPos = str.find(delim);
	int start = 0;
	while (delimPos != std::string::npos)
	{
		std::string token = str.substr(start, delimPos - start);
		start = delimPos + 1;
		delimPos = str.find(delim, start);
		tokens.push_back(token);
	}

	if (tokens.size() != Earning::NUMOFMEMBERVARIABLES)
	{
		throw std::runtime_error("Earning::parseTokens : Incorrect number of variables in earnings");
	}

	// Parse tokens 
	int id;
	std::time_t date;
	float amount;


	// Format: [ID]/[Date]/[Amount]

	for (int i = 0; i < Earning::NUMOFMEMBERVARIABLES; i++)
	{
		switch (i)
		{
		case 0: // id
			id = atoi(tokens[i].c_str());
			break;
		case 1: // date
			date = std::stoi(tokens[i]);
			break;
		case 2: // amount
			amount = std::stof(tokens[i]);
			break;
		}
	}

	return Earning(id, date, amount);
}