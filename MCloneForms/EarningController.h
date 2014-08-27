// EarningController.h

#ifndef EARNINGCONTROLLER_H_INCLUDED
#define EARNINGCONTROLLER_H_INCLUDED

// INCLUDES
#include <stdio.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>

// MY CLASS INCLUDES
#include "Earning.h"
#include "Controller.h"


class EarningController
{
	public:
		EarningController(std::string profileName);
		void add(time_t date, float amount);
		void add(tm date, float amount);
		void load();
		void loadBackup();
		void modifyDate(int index, tm date);
		void modifyAmount(int index, float amount);
		time_t getDate(int index);
		float getAmount(int index);
		void sortByDate(bool descending);
		void sortByAmount(bool descending);
		std::string getProfileName();

		std::vector<Earning> getEarnings();

	private:
		Controller<Earning> controller;

};


#endif