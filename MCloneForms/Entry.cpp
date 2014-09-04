// Entry.cpp

#include "stdafx.h"
#include "Entry.h"

// Operation Overload

std::ostream& operator<<(std::ostream& os, const Entry &entry)
{
	os << entry.id << "/" << entry.date << "/" << entry.category << "/" 
		<< entry.description << "/" << std::fixed << std::setprecision(2) << entry.amount << "/";
	return os;
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

Entry Entry::parseTokens(std::string str)
{	
	std::string delim = "/";
	std::vector<std::string> tokens;
	tokens.reserve(Entry::NUMOFMEMBERVARIABLES);
	unsigned int delimPos = str.find(delim);
	int start = 0;
	while (delimPos != std::string::npos)
	{
		std::string token = str.substr(start, delimPos - start);
		start = delimPos + 1;
		delimPos = str.find(delim, start);
		tokens.push_back(token);
	}

	if (tokens.size() != Entry::NUMOFMEMBERVARIABLES)
	{
		throw std::runtime_error("Entry::parseTokens : Incorrect number of variables in entrys");
	}
	// Parse tokens 
	int id;
	std::time_t date;
	std::string category;
	std::string description;
	float amount;

	// Format: [ID]/[Date]/[Category]/[Description]/[Amount]

	for (int i = 0; i < Entry::NUMOFMEMBERVARIABLES; i++)
	{
		switch (i)
		{
		case 0: // id
			id = atoi(tokens[i].c_str());
			break;
		case 1: // date
			date = std::stoi(tokens[i]);
			break;
		case 2: // category
			category = tokens[i];
			break;
		case 3: // description
			description = tokens[i];
			break;
		case 4: // amount
			amount = std::stof(tokens[i]);

			break;
		}
	}

	return Entry(id, date, category, description, amount);
}