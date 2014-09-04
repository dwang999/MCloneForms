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
#include "String.h"


class EarningController
{
	public:
		EarningController(std::string profileName);
		int add(time_t date, float amount);
		int add(tm date, float amount);
		void remove(int indexToRemove);
		void save();
		void autoSave();
		void load();
		void loadBackup();
		void modifyDate(int id, tm date);
		void modifyAmount(int id, float amount);
		time_t getDate(int id);
		float getAmount(int id);
		bool backupExists();
		bool deleteBackup();
		
		std::string getProfileName();
		std::vector<Earning> getEarnings();

	private:
		Controller<Earning> controller;

};


#endif