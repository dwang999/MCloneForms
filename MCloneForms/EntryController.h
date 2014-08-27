// EntryController.h

#ifndef ENTRYCONTROLLER_H_INCLUDED
#define ENTRYCONTROLLER_H_INCLUDED

// INCLUDES
#include <stdio.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>

// MY CLASS INCLUDES
#include "Entry.h"
#include "Controller.h"


class EntryController
{
	public:
		EntryController(std::string profileName);
		void add(time_t date, std::string category, std::string subCategory, 
			std::string description, float amount);
		void add(tm date, std::string category, std::string subCategory, 
			std::string description, float amount);
		void remove(int indexToRemove);
		void save();
		void autoSave();
		void load();
		void loadBackup();
		void modifyDate(int index, tm date);
		void modifyCategory(int index, std::string category);
		void modifySubCategory(int index, std::string subCategory);
		void modifyDescription(int index, std::string description);
		void modifyAmount(int index, float amount);
		time_t getDate(int index);
		std::string getCategory(int index);
		std::string getSubCategory(int index);
		std::string getDescription(int index);
		float getAmount(int index);
		void sortByDate(bool descending);
		void sortByCategory(bool descending);
		void sortBySubCategory(bool descending);
		void sortByDescription(bool descending);
		void sortByAmount(bool descending);
		bool backupExists();
		bool deleteBackup();
		
		std::string getProfileName();
		std::vector<Entry> getEntries();

	private:
		Controller<Entry> controller;

};


#endif