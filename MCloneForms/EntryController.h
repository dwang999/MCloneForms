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
#include <set>

// MY CLASS INCLUDES
#include "Entry.h"
#include "Controller.h"
#include "String.h"


class EntryController : public Controller
{
	public:
		EntryController(std::string profileName);
		~EntryController();
		int add(time_t date, std::string category, std::string description, float amount);
		int add(tm date, std::string category, std::string description, float amount);

		void modifyDate(int id, tm date);
		void modifyCategory(int id, std::string category);
		void modifyDescription(int id, std::string description);
		void modifyAmount(int id, float amount);
		time_t getDate(int id);
		std::string getCategory(int id);
		std::string getDescription(int id);
		float getAmount(int id);
		
		ControllerData* parseTokens(std::string str);
		
		std::set<std::string> getDistinctCategories();
		std::string getProfileName();
		std::vector<Entry*> getEntries();


};


#endif