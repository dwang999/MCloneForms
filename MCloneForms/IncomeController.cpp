// IncomeController.cpp

#include "stdafx.h"
#include "IncomeController.h"

// Constructors

IncomeController::IncomeController(std::string profileName) : 
	controller(profileName, "Incomes", "Profiles/" + profileName + "/Incomes.txt", "Profiles/" + profileName + "/Incomes-Backup.txt") {}

// Methods
std::vector<Income> IncomeController::getIncomes()
{
	return controller.vectorT;
}

int IncomeController::add(time_t effectiveDate, float amount)
{
	int id = controller.generateID();
	controller.add(Income(id, effectiveDate, amount));
	return id;
}


int IncomeController::add(tm effectiveDate, float amount)
{
	int id = controller.generateID();
	controller.add(Income(id, mktime(&effectiveDate), amount));
	return id;
}

void IncomeController::remove(int id){
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
		throw std::invalid_argument("IncomeController::remove : id " + convertSystemToSTDString(id.ToString()) + " not found");

}
void IncomeController::save(){
	controller.save();
}
void IncomeController::autoSave(){
	controller.autoSave();

}
bool IncomeController::backupExists(){
	return controller.backupExists();

}
bool IncomeController::deleteBackup(){
	return controller.deleteBackup();
}

void IncomeController::modifyEffectiveDate(int id, tm effectiveDate)
{
	bool success = false;
	for (Income &income : controller.vectorT)
	{
		if (income.id == id)
		{
			income.effectiveDate = mktime(&effectiveDate);
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
	for (Income &income : controller.vectorT)
	{
		if (income.id == id)
		{
			income.amount = amount;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("IncomeController::modifyAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


time_t IncomeController::getEffectiveDate(int id){
	for (Income income : controller.vectorT)
	{
		if (income.id == id)
			return income.effectiveDate;
	}

	throw std::invalid_argument("IncomeController::geteffectiveDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
float IncomeController::getAmount(int id){
	for (Income income : controller.vectorT)
	{
		if (income.id == id)
			return income.amount;
	}
	throw std::invalid_argument("IncomeController::getAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void IncomeController::load()
{
	controller.loadController(controller.fileName);
}
void IncomeController::loadBackup()
{
	controller.loadController(controller.backupFileName);
}

std::string IncomeController::getProfileName(){
	return controller.profileName;
}
