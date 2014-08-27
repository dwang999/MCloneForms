// EntryController.cpp

#include "stdafx.h"
#include "EntryController.h"

namespace{


	bool sortEntryByDateDesc(Entry i, Entry j) 
	{ 
		return difftime(i.date, j.date) > 0; 
	}
	bool sortEntryByDateAsc(Entry i, Entry j) 
	{ 
		return difftime(i.date, j.date) < 0; 
	}

	bool sortEntryByCategoryDesc(Entry i, Entry j) 
	{ 
		return i.category > j.category; 
	}
	bool sortEntryByCategoryAsc(Entry i, Entry j) 
	{ 
		return i.category < j.category; 
	}

	bool sortEntryBySubCategoryDesc(Entry i, Entry j) 
	{ 
		return i.subCategory > j.subCategory; 
	}
	bool sortEntryBySubCategoryAsc(Entry i, Entry j) 
	{ 
		return i.subCategory < j.subCategory; 
	}

	bool sortEntryByDescriptionDesc(Entry i, Entry j) 
	{ 
		return i.description > j.description; 
	}
	bool sortEntryByDescriptionAsc(Entry i, Entry j) 
	{ 
		return i.description < j.description; 
	}

	bool sortEntryByAmountDesc(Entry i, Entry j) 
	{ 
		return i.amount > j.amount; 
	}
	bool sortEntryByAmountAsc(Entry i, Entry j) 
	{ 
		return i.amount < j.amount; 
	}

	

	
	void parseTokens(Controller<Entry> *entry, std::string str)
	{	
		// Get Tokens
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
		std::time_t date;
		std::string category;
		std::string subCategory;
		std::string description;
		float amount;

		for (int i = 0; i < Entry::NUMOFMEMBERVARIABLES; i++)
		{
			switch (i)
			{
			case 0: // date
				date = std::stoi(tokens[i]);
				break;
			case 1: // category
				category = tokens[i];
				break;
			case 2: // sub-category
				subCategory = tokens[i];
				break;
			case 3: // description
				description = tokens[i];
				break;
			case 4: // amount
				amount = std::stof(tokens[i]);

				break;
			}
		}

		entry -> add(Entry(date, category, subCategory, description, amount));
	}

	void loadController(Controller<Entry> *controller, std::string fileName)
	{		
		std::fstream fs;
		std::string line;

		fs.open(fileName, std::fstream::in);


		if (fs.is_open())
		{
			while(!fs.eof())
			{
				std::getline(fs, line);
				if (!line.empty())
					parseTokens(controller , line);

			}
			fs.close();
		}
	}



}

// Constructors

EntryController::EntryController(std::string profileName) : 
	controller(profileName, "Entries", "Profiles/" + profileName + "/Entries.txt", "Profiles/" + profileName + "/Entries-Backup.txt") {}

// Methods
std::vector<Entry> EntryController::getEntries()
{
	return controller.vectorT;
}

void EntryController::add(time_t date, std::string category, std::string subCategory, 
						  std::string description, float amount)
{
	controller.add(Entry(date, category, subCategory, description, amount));
}


void EntryController::add(tm date, std::string category, std::string subCategory, 
						  std::string description, float amount)
{
	controller.add(Entry(mktime(&date), category, subCategory, description, amount));
}

void EntryController::remove(int indexToRemove){
	controller.remove(indexToRemove);
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

void EntryController::modifyDate(int index, tm date)
{
	controller.vectorT[index].date = mktime(&date);
}

void EntryController::modifyCategory(int index, std::string category)
{
	controller.vectorT[index].category = category;
}

void EntryController::modifySubCategory(int index, std::string subCategory)
{
	controller.vectorT[index].subCategory = subCategory;
}

void EntryController::modifyDescription(int index, std::string description)
{
	controller.vectorT[index].description = description;
}

void EntryController::modifyAmount(int index, float amount)
{
	controller.vectorT[index].amount = amount;
}


time_t EntryController::getDate(int index){
	return controller.vectorT[index].date;
}
std::string EntryController::getCategory(int index){
	return controller.vectorT[index].category;
}
std::string EntryController::getSubCategory(int index){
	return controller.vectorT[index].subCategory;
}
std::string EntryController::getDescription(int index){
	return controller.vectorT[index].description;
}
float EntryController::getAmount(int index){
	return controller.vectorT[index].amount;
}

void EntryController::load()
{
	loadController(&controller, controller.fileName);
}
void EntryController::loadBackup()
{
	loadController(&controller, controller.backupFileName);
}

void EntryController::sortByDate(bool descending)
{
	if (descending)
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByDateDesc);
	else
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByDateAsc);

}

void EntryController::sortByCategory(bool descending)
{
	if (descending)
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByCategoryDesc);
	else
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByCategoryAsc);
}

void EntryController::sortBySubCategory(bool descending)
{
	if (descending)
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryBySubCategoryDesc);
	else
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryBySubCategoryAsc);
}

void EntryController::sortByDescription(bool descending)
{
	if (descending)
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByDescriptionDesc);
	else
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByDescriptionAsc);
}

void EntryController::sortByAmount(bool descending)
{
	if (descending)
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByAmountDesc);
	else
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEntryByAmountAsc);

}

std::string EntryController::getProfileName(){
	return controller.profileName;
}