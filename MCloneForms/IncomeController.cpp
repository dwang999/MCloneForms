// IncomeController.cpp

#include "stdafx.h"
#include "IncomeController.h"

// Constructors

IncomeController::IncomeController(std::string profileName) : 
	Controller(profileName, "Incomes", "Profiles/" + profileName + "/Incomes.txt", "Profiles/" + profileName + "/Incomes-Backup.txt") {}

IncomeController::~IncomeController(){}

// Methods
std::vector<Income*> IncomeController::getIncomes()
{
	std::vector<Income*> incomes;
	for (unsigned int i = 0; i < controller.size(); i++)
	{		
		incomes.push_back((Income*)controller[i]);
	}
	return incomes;
}

int IncomeController::add(time_t effectiveDate, float amount)
{
	int id = generateID();
	addData(new Income(id, effectiveDate, amount));
	return id;
}


int IncomeController::add(tm effectiveDate, float amount)
{
	int id = generateID();
	addData(new Income(id, mktime(&effectiveDate), amount));
	return id;
}

void IncomeController::modifyEffectiveDate(int id, tm effectiveDate)
{
	bool success = false;
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Income *income = (Income*) data;
			income->effectiveDate = mktime(&effectiveDate);
			success = true;
			break;
		}
	}

	if (!success)
		throw std::invalid_argument("IncomeController::modifyeffectiveDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


void IncomeController::modifyAmount(int id, float amount)
{
	bool success = false;
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Income *income = (Income*) data;
			income->amount = amount;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("IncomeController::modifyAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


time_t IncomeController::getEffectiveDate(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Income *income = (Income*) data;
			return income->effectiveDate;
		}
	}

	throw std::invalid_argument("IncomeController::geteffectiveDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
float IncomeController::getAmount(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Income *income = (Income*) data;
			return income->amount;
		}
	}
	throw std::invalid_argument("IncomeController::getAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


std::string IncomeController::getProfileName(){
	return profileName;
}

ControllerData* IncomeController::parseTokens(std::string str)
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
		throw std::runtime_error("IncomeController::parseTokens : Incorrect number of variables in earnings");
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

	return new Income(id, effectiveDate, amount);
}