// EntryController.cpp

#include "stdafx.h"
#include "EntryController.h"

namespace{

	static const std::string EntryFileName = "Entries";

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


	void parseTokens(EntryController *entry, std::string str)
	{	
		// Get Tokens
		std::string delim = "/";
		std::vector<std::string> tokens;
		tokens.reserve(NUMOFVARIABLESINENTRY);
		unsigned int delimPos = str.find(delim);
		int start = 0;
		while (delimPos != std::string::npos)
		{
			std::string token = str.substr(start, delimPos - start);
			start = delimPos + 1;
			delimPos = str.find(delim, start);
			tokens.push_back(token);
		}

		if (tokens.size() != NUMOFVARIABLESINENTRY)
		{
			throw std::runtime_error("EntryController::parseTokens : Incorrect number of variables in entrys");
		}

		// Parse tokens 
		std::time_t date;
		std::string category;
		std::string subCategory;
		std::string description;
		float amount;

		for (int i = 0; i < NUMOFVARIABLESINENTRY; i++)
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

		entry -> add(date, category, subCategory, description, amount);
	}


	bool saveEntryController(const std::string fileName, const std::vector<Entry> entries)
	{
		std::fstream fs;
		fs.open(fileName, std::fstream::out | std::fstream::trunc);

		if (fs.is_open())
		{
			for(Entry entry : entries)
			{
				fs << entry << std::endl;
			} 

			fs.close();
			return true;
		}
		else
			return false;

	}
}

// Constructors

EntryController::EntryController(std::string profileName) : Controller(profileName) {}


// Methods
std::vector<Entry> EntryController::getEntries()
{
	return entries;
}

void EntryController::add(time_t date, std::string category, std::string subCategory, 
						  std::string description, float amount)
{
	entries.push_back(Entry(date, category, subCategory, description, amount));
}


void EntryController::add(tm date, std::string category, std::string subCategory, 
						  std::string description, float amount)
{
	entries.push_back(Entry(mktime(&date), category, subCategory, description, amount));
}

void EntryController::remove(int indexToRemove)
{

	entries.erase(entries.begin() + indexToRemove);
}

// Save Entry Controller and delete the backup
void EntryController::save()
{
	std::string filename = "Profiles/" + this -> profileName + "/" + EntryFileName + ".txt";
	if(saveEntryController(filename, entries))
	{
		if (backupExists())
		{
			if(!deleteBackup())
				throw std::runtime_error("EntryController::save : Entries backup was not deleted");
		}
	}
	else
		throw std::runtime_error("EntryController::save : Entries save file could not be opened");
}

void EntryController::autoSave()
{
	std::string backupFilename = "Profiles/" + this -> profileName + "/" + EntryFileName + "-Backup.txt";
	if(!saveEntryController(backupFilename, entries))
		throw std::runtime_error("EntryController::save : Entries save file could not be opened");
}

bool EntryController::backupExists()
{
	std::string backupFilename = "Profiles/" + this -> profileName + "/" + EntryFileName + "-Backup.txt";
	std::ifstream ifile(backupFilename.c_str());
	if(ifile.good())
	{
		ifile.close();
		return true;
	}
	else
		return false;
}

bool EntryController::deleteBackup(){
	std::string backupFilename = "Profiles/" + this -> profileName + "/" + EntryFileName + "-Backup.txt";
	if(std::remove(backupFilename.c_str()) != 0)
		return false;
	else
		return true;
}



void EntryController::modifyDate(int index, tm date)
{
	entries[index].date = mktime(&date);
}

void EntryController::modifyCategory(int index, std::string category)
{
	entries[index].category = category;
}

void EntryController::modifySubCategory(int index, std::string subCategory)
{
	entries[index].subCategory = subCategory;
}

void EntryController::modifyDescription(int index, std::string description)
{
	entries[index].description = description;
}

void EntryController::modifyAmount(int index, float amount)
{
	entries[index].amount = amount;
}


time_t EntryController::getDate(int index){
	return entries[index].date;
}
std::string EntryController::getCategory(int index){
	return entries[index].category;
}
std::string EntryController::getSubCategory(int index){
	return entries[index].subCategory;
}
std::string EntryController::getDescription(int index){
	return entries[index].description;
}
float EntryController::getAmount(int index){
	return entries[index].amount;
}

void EntryController::load()
{
	std::string filename = "Profiles/" + this -> profileName + "/" + EntryFileName + ".txt";
	std::fstream fs;
	std::string line;

	fs.open(filename, std::fstream::in);


	if (fs.is_open())
	{
		while(!fs.eof())
		{
			std::getline(fs, line);
			if (!line.empty())
				parseTokens(this , line);

		}
		fs.close();
	}

}
void EntryController::loadBackup()
{
	std::string backupFilename = "Profiles/" + this -> profileName + "/" + EntryFileName + "-Backup.txt";
	std::fstream fs;
	std::string line;

	fs.open(backupFilename, std::fstream::in);


	if (fs.is_open())
	{
		while(!fs.eof())
		{
			std::getline(fs, line);
			if (!line.empty())
				parseTokens(this , line);

		}
		fs.close();
	}

}

void EntryController::sortByDate(bool descending)
{
	if (descending)
		std::sort(entries.begin(), entries.end(), sortEntryByDateDesc);
	else
		std::sort(entries.begin(), entries.end(), sortEntryByDateAsc);

}

void EntryController::sortByCategory(bool descending)
{
	if (descending)
		std::sort(entries.begin(), entries.end(), sortEntryByCategoryDesc);
	else
		std::sort(entries.begin(), entries.end(), sortEntryByCategoryAsc);
}

void EntryController::sortBySubCategory(bool descending)
{
	if (descending)
		std::sort(entries.begin(), entries.end(), sortEntryBySubCategoryDesc);
	else
		std::sort(entries.begin(), entries.end(), sortEntryBySubCategoryAsc);
}

void EntryController::sortByDescription(bool descending)
{
	if (descending)
		std::sort(entries.begin(), entries.end(), sortEntryByDescriptionDesc);
	else
		std::sort(entries.begin(), entries.end(), sortEntryByDescriptionAsc);
}

void EntryController::sortByAmount(bool descending)
{
	if (descending)
		std::sort(entries.begin(), entries.end(), sortEntryByAmountDesc);
	else
		std::sort(entries.begin(), entries.end(), sortEntryByAmountAsc);

}