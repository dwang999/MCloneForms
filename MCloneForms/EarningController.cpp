// EarningController.cpp

#include "stdafx.h"
#include "EarningController.h"

// Constructors

EarningController::EarningController(std::string profileName) : 
	controller(profileName, "Earnings", "Profiles/" + profileName + "/Earnings.txt", "Profiles/" + profileName + "/Earnings-Backup.txt") {}


// Methods

std::vector<Earning> EarningController::getEarnings()
{
	return controller.vectorT;
}

int EarningController::add(time_t date, float amount)
{
	int id = controller.generateID();
	controller.vectorT.push_back(Earning(id, date, amount));
	return id;
}


int EarningController::add(tm date, float amount)
{
	int id = controller.generateID();
	controller.vectorT.push_back(Earning(id, mktime(&date), amount));
	return id;
}



void EarningController::load()
{
	controller.loadController(controller.fileName);
}
void EarningController::loadBackup()
{
	controller.loadController(controller.backupFileName);
}


void EarningController::remove(int id){
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
		throw std::invalid_argument("EarningController::remove : id " + convertSystemToSTDString(id.ToString()) + " not found");

}

void EarningController::save(){
	controller.save();
}
void EarningController::autoSave(){
	controller.autoSave();

}
bool EarningController::backupExists(){
	return controller.backupExists();

}
bool EarningController::deleteBackup(){
	return controller.deleteBackup();
}

void EarningController::modifyDate(int id, tm date)
{
	bool success = false;
	for (Earning &earning : controller.vectorT)
	{
		if (earning.id == id)
		{
			earning.date = mktime(&date);
			success = true;
			break;
		}
	}

	if (!success)
		throw std::invalid_argument("EarningController::modifyDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void EarningController::modifyAmount(int id, float amount)
{
	bool success = false;
	for (Earning &earning : controller.vectorT)
	{
		if (earning.id == id)
		{
			earning.amount = amount;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("EarningController::modifyAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


time_t EarningController::getDate(int id){
	for (Earning earning : controller.vectorT)
	{
		if (earning.id == id)
			return earning.date;
	}

	throw std::invalid_argument("EarningController::getDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

float EarningController::getAmount(int id){
	for (Earning earning : controller.vectorT)
	{
		if (earning.id == id)
			return earning.amount;
	}
	throw std::invalid_argument("EarningController::getAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

std::string EarningController::getProfileName()
{
	return controller.profileName;
}