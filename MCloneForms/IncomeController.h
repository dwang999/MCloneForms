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



class IncomeController: public Controller
{
	public:
		IncomeController(std::string profileName);
		~IncomeController();
		int add(time_t effectiveDate, float amount);
		int add(tm effectiveDate, float amount);
		void modifyEffectiveDate(int id, tm effectiveDate);
		void modifyAmount(int id, float amount);
		time_t getEffectiveDate(int id);
		float getAmount(int id);
		
		ControllerData* parseTokens(std::string str);
		
		std::string getProfileName();
		std::vector<Income*> getIncomes();


};


#endif