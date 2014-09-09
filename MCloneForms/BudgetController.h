// BudgetController.h

#ifndef BUDGETCONTROLLER_H_INCLUDED
#define BUDGETCONTROLLER_H_INCLUDED

// INCLUDES
#include <stdio.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <set>

// MY CLASS INCLUDES
#include "Budget.h"
#include "Controller.h"
#include "String.h"


class BudgetController
{
	public:
		BudgetController(std::string profileName);
		int add(time_t effectiveDate, std::string category, float amount);
		int add(tm effectiveDate, std::string category, float amount);
		void remove(int id);
		void save();
		void autoSave();
		void load();
		void loadBackup();
		void modifyEffectiveDate(int id, tm effectiveDate);
		void modifyCategory(int id, std::string category);
		void modifyAmount(int id, float amount);
		time_t getEffectiveDate(int id);
		std::string getCategory(int id);
		float getAmount(int id);
		bool backupExists();
		bool deleteBackup();
		
		std::set<std::string> getDistinctCategories();
		std::string getProfileName();
		std::vector<Budget> getBudgets();

	private:
		Controller<Budget> controller;

};


#endif