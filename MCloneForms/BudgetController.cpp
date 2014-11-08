// BudgetController.cpp

#include "stdafx.h"
#include "BudgetController.h"

// Constructors

BudgetController::BudgetController(std::string profileName) : 
	Controller(profileName, "Budget", "Profiles/" + profileName + "/Budget.txt", "Profiles/" + profileName + "/Budget-Backup.txt") {}

BudgetController::~BudgetController(){}

// Methods
std::vector<Budget*> BudgetController::getBudgets()
{
	std::vector<Budget*> budgets;
	for (unsigned int i = 0; i < controller.size(); i++)
	{		
		budgets.push_back((Budget*)controller[i]);
	}
	return budgets;
}

int BudgetController::add(time_t effectiveDate, std::string category, float amount)
{
	int id = generateID();	
	addData(new Budget(id, effectiveDate, category, amount));
	return id;
}


int BudgetController::add(tm effectiveDate, std::string category, float amount)
{
	int id = generateID();
	addData(new Budget(id, mktime(&effectiveDate), category, amount));
	return id;
}

void BudgetController::modifyEffectiveDate(int id, tm effectiveDate)
{
	bool success = false;
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Budget *budget = (Budget*) data;
			budget->effectiveDate = mktime(&effectiveDate);
			success = true;
			break;
		}
	}

	if (!success)
		throw std::invalid_argument("BudgetController::modifyEffectiveDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void BudgetController::modifyCategory(int id, std::string category)
{
	bool success = false;
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Budget *budget = (Budget*) data;
			budget->category = category;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("BudgetController::modifyCategory : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void BudgetController::modifyAmount(int id, float amount)
{
	bool success = false;
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Budget *budget = (Budget*) data;
			budget->amount = amount;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("BudgetController::modifyAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


time_t BudgetController::getEffectiveDate(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Budget *budget = (Budget*) data;
			return budget->effectiveDate;
		}
	}

	throw std::invalid_argument("BudgetController::getEffectiveDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
std::string BudgetController::getCategory(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Budget *budget = (Budget*) data;
			return budget->category;
		}
	}
	throw std::invalid_argument("BudgetController::getCategory : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
float BudgetController::getAmount(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Budget *budget = (Budget*) data;
			return budget->amount;
		}
	}
	throw std::invalid_argument("BudgetController::getAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


std::string BudgetController::getProfileName(){
	return profileName;
}


std::set<std::string> BudgetController::getDistinctCategories()
{
	std::set<std::string> categories = std::set<std::string>();
	for (auto budget : getBudgets())
	{
		categories.insert(budget->category);
	}
	return categories;
}

ControllerData* BudgetController::parseTokens(std::string str)
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
		throw std::runtime_error("BudgetController::parseTokens : Incorrect number of variables in entrys");
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

	return new Budget(id, effectiveDate, category, amount);
}