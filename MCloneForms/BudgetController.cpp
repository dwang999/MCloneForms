// BudgetController.cpp

#include "stdafx.h"
#include "BudgetController.h"

// Constructors

BudgetController::BudgetController(std::string profileName) : 
	controller(profileName, "Budget", "Profiles/" + profileName + "/Budget.txt", "Profiles/" + profileName + "/Budget-Backup.txt") {}

// Methods
std::vector<Budget> BudgetController::getBudgets()
{
	return controller.vectorT;
}

int BudgetController::add(time_t effectiveDate, std::string category, float amount)
{
	int id = controller.generateID();
	controller.add(Budget(id, effectiveDate, category, amount));
	return id;
}


int BudgetController::add(tm effectiveDate, std::string category, float amount)
{
	int id = controller.generateID();
	controller.add(Budget(id, mktime(&effectiveDate), category, amount));
	return id;
}

void BudgetController::remove(int id){
	bool success = false;
	for (size_t i = 0; i < controller.vectorT.size(); i++)
	{
		if (controller.vectorT[i].id == id)
		{
			controller.remove(i);
			success = true;
			break;
		}
	}

	if (!success)
		throw std::invalid_argument("BudgetController::remove : id " + convertSystemToSTDString(id.ToString()) + " not found");

}
void BudgetController::save(){
	controller.save();
}
void BudgetController::autoSave(){
	controller.autoSave();

}
bool BudgetController::backupExists(){
	return controller.backupExists();

}
bool BudgetController::deleteBackup(){
	return controller.deleteBackup();
}

void BudgetController::modifyEffectiveDate(int id, tm effectiveDate)
{
	bool success = false;
	for (Budget &budget : controller.vectorT)
	{
		if (budget.id == id)
		{
			budget.effectiveDate = mktime(&effectiveDate);
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
	for (Budget &budget : controller.vectorT)
	{
		if (budget.id == id)
		{
			budget.category = category;
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
	for (Budget &budget : controller.vectorT)
	{
		if (budget.id == id)
		{
			budget.amount = amount;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("BudgetController::modifyAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


time_t BudgetController::getEffectiveDate(int id){
	for (Budget budget : controller.vectorT)
	{
		if (budget.id == id)
			return budget.effectiveDate;
	}

	throw std::invalid_argument("BudgetController::getEffectiveDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
std::string BudgetController::getCategory(int id){
	for (Budget budget : controller.vectorT)
	{
		if (budget.id == id)
			return budget.category;
	}
	throw std::invalid_argument("BudgetController::getCategory : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
float BudgetController::getAmount(int id){
	for (Budget budget : controller.vectorT)
	{
		if (budget.id == id)
			return budget.amount;
	}
	throw std::invalid_argument("BudgetController::getAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void BudgetController::load()
{
	controller.loadController(controller.fileName);
}
void BudgetController::loadBackup()
{
	controller.loadController(controller.backupFileName);
}

std::string BudgetController::getProfileName(){
	return controller.profileName;
}
