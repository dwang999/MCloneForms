// EntryController.cpp

#include "stdafx.h"
#include "EntryController.h"

// Constructors

EntryController::EntryController(std::string profileName) : 
	Controller(profileName, "Entries", "Profiles/" + profileName + "/Entries.txt", "Profiles/" + profileName + "/Entries-Backup.txt") {}

EntryController::~EntryController(){}
// Methods
std::vector<Entry*> EntryController::getEntries()
{
	std::vector<Entry*> entries;
	for (unsigned int i = 0; i < controller.size(); i++)
	{		
		entries.push_back((Entry*)controller[i]);
	}
	return entries;
}

int EntryController::add(time_t date, std::string category, std::string description, float amount)
{
	int id = generateID();
	addData(new Entry(id, date, category, description, amount));
	return id;
}


int EntryController::add(tm date, std::string category, std::string description, float amount)
{
	int id = generateID();
	addData(new Entry(id, mktime(&date), category, description, amount));
	return id;
}


void EntryController::modifyDate(int id, tm date)
{
	bool success = false;
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			entry-> date = mktime(&date);
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
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			entry->category = category;
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
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			entry->description = description;
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
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			entry->amount = amount;
			success = true;
			break;
		}
	}
	if (!success)
		throw std::invalid_argument("EntryController::modifyAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


time_t EntryController::getDate(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			return entry->date;
		}
	}

	throw std::invalid_argument("EntryController::getDate : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
std::string EntryController::getCategory(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			return entry->category;
		}
	}
	throw std::invalid_argument("EntryController::getCategory : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
std::string EntryController::getDescription(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			return entry->description;
		}
	}
	throw std::invalid_argument("EntryController::getDescription : id " + convertSystemToSTDString(id.ToString()) + " not found");
}
float EntryController::getAmount(int id){
	for (ControllerData* data : controller)
	{
		if (data->id == id)
		{
			Entry *entry = (Entry*) data;
			return entry->amount;
		}
	}
	throw std::invalid_argument("EntryController::getAmount : id " + convertSystemToSTDString(id.ToString()) + " not found");
}


std::string EntryController::getProfileName(){
	return profileName;
}

std::set<std::string> EntryController::getDistinctCategories()
{
	std::set<std::string> categories = std::set<std::string>();
	for (auto entry : getEntries())
	{
		categories.insert(entry->category);
	}
	return categories;
}

ControllerData* EntryController::parseTokens(std::string str)
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
		throw std::runtime_error("EntryController::parseTokens : Incorrect number of variables in entrys");
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

	return new Entry(id, date, category, description, amount);
}