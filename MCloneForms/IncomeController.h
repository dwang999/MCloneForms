// IncomeController.h

#ifndef INCOMECONTROLLER_H_INCLUDED
#define INCOMECONTROLLER_H_INCLUDED

// INCLUDES
#include <stdio.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <set>

// MY CLASS INCLUDES
#include "Income.h"
#include "Controller.h"
#include "String.h"


class IncomeController
{
	public:
		IncomeController(std::string profileName);
		int add(time_t effectiveDate, float amount);
		int add(tm effectiveDate, float amount);
		void remove(int id);
		void save();
		void autoSave();
		void load();
		void loadBackup();
		void modifyEffectiveDate(int id, tm effectiveDate);
		void modifyAmount(int id, float amount);
		time_t getEffectiveDate(int id);
		float getAmount(int id);
		bool backupExists();
		bool deleteBackup();

		
		std::string getProfileName();
		std::vector<Income> getIncomes();

	private:
		Controller<Income> controller;

};


#endif