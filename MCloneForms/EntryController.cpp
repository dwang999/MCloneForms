// EntryController.cpp

#include "stdafx.h"
#include "EntryController.h"

// Constructors

EntryController::EntryController(std::string profileName) : 
	controller(profileName, "Entries", "Profiles/" + profileName + "/Entries.txt", "Profiles/" + profileName + "/Entries-Backup.txt") {}

// Methods
std::vector<Entry> EntryController::getEntries()
{
	return controller.vectorT;
}

int EntryController::add(time_t date, std::string category, std::string description, float amount)
{
	int id = controller.generateID();
	controller.add(Entry(id, date, category, description, amount));
	return id;
}


int EntryController::add(tm date, std::string category, std::string description, float amount)
{
	int id = controller.generateID();
	controller.add(Entry(id, mktime(&date), category, description, amount));
	return id;
}

void EntryController::remove(int id){
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
		throw std::invalid_argument("EntryController::remove : id " + convertSystemToSTDString(id.ToString()) + " not found");

}
void EntryController::save(){
	controller.save();
}
void EntryController::autoSave(){
	controller.autoSave();

}
bool EntryController::backupExists(){
	return controller.backupExists();

}
bool EntryController::deleteBackup(){
	return controller.deleteBackup();
}

void EntryController::modifyDate(int id, tm date)
{
	bool success = false;
	for (Entry &entry : controller.vectorT)
	{
		if (entry.id == id)
		{
			entry.date = mktime(&date);
			success = true;
			break;
		}
	}

	if (!success)
		throw std::invalid_argument("EntryController::modifyDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void EntryController::modifyCategory(int id, std::string category)
{
	bool success = false;
	for (Entry &entry : controller.vectorT)
	{
		if (entry.id == id)
		{
			entry.category = category;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("EntryController::modifyCategory : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void EntryController::modifyDescription(int id, std::string description)
{
	bool success = false;
	for (Entry &entry : controller.vectorT)
	{
		if (entry.id == id)
		{
			entry.description = description;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("EntryController::modifyDescription : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void EntryController::modifyAmount(int id, float amount)
{
	bool success = false;
	for (Entry &entry : controller.vectorT)
	{
		if (entry.id == id)
		{
			entry.amount = amount;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("EntryController::modifyAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


time_t EntryController::getDate(int id){
	for (Entry entry : controller.vectorT)
	{
		if (entry.id == id)
			return entry.date;
	}

	throw std::invalid_argument("EntryController::getDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
std::string EntryController::getCategory(int id){
	for (Entry entry : controller.vectorT)
	{
		if (entry.id == id)
			return entry.category;
	}
	throw std::invalid_argument("EntryController::getCategory : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
std::string EntryController::getDescription(int id){
	for (Entry entry : controller.vectorT)
	{
		if (entry.id == id)
			return entry.description;
	}
	throw std::invalid_argument("EntryController::getDescription : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
float EntryController::getAmount(int id){
	for (Entry entry : controller.vectorT)
	{
		if (entry.id == id)
			return entry.amount;
	}
	throw std::invalid_argument("EntryController::getAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}

void EntryController::load()
{
	controller.loadController(controller.fileName);
}
void EntryController::loadBackup()
{
	controller.loadController(controller.backupFileName);
}

std::string EntryController::getProfileName(){
	return controller.profileName;
}
