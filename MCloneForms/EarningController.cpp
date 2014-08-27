// EarningController.cpp

#include "stdafx.h"
#include "EarningController.h"

namespace{


	bool sortEarningByDateDesc(Earning i, Earning j) 
	{ 
		return difftime(i.date, j.date) > 0; 
	}
	bool sortEarningByDateAsc(Earning i, Earning j) 
	{ 
		return difftime(i.date, j.date) < 0; 
	}

	bool sortEarningByAmountDesc(Earning i, Earning j) 
	{ 
		return i.amount > j.amount; 
	}
	bool sortEarningByAmountAsc(Earning i, Earning j) 
	{ 
		return i.amount < j.amount; 
	}

	

	void parseTokens(Controller<Earning> *earning, std::string str)
	{	
		// Get Tokens
		std::string delim = "/";
		std::vector<std::string> tokens;
		tokens.reserve(Earning::NUMOFMEMBERVARIABLES);
		unsigned int delimPos = str.find(delim);
		int start = 0;
		while (delimPos != std::string::npos)
		{
			std::string token = str.substr(start, delimPos - start);
			start = delimPos + 1;
			delimPos = str.find(delim, start);
			tokens.push_back(token);
		}

		if (tokens.size() != Earning::NUMOFMEMBERVARIABLES)
		{
			throw std::runtime_error("EarningController::parseTokens : Incorrect number of variables in earnings");
		}

		// Parse tokens 
		std::time_t date;
		float amount;

		for (int i = 0; i < Earning::NUMOFMEMBERVARIABLES; i++)
		{
			switch (i)
			{
			case 0: // date
				date = std::stoi(tokens[i]);
				break;
			case 1: // amount
				amount = std::stof(tokens[i]);
				break;
			}
		}

		earning -> add(Earning(date, amount));
	}

	void loadController(Controller<Earning> *controller, std::string fileName)
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

EarningController::EarningController(std::string profileName) : 
	controller(profileName, "Earnings", "Profiles/" + profileName + "/Earnings.txt", "Profiles/" + profileName + "/Earnings-Backup.txt") {}


// Methods

std::vector<Earning> EarningController::getEarnings()
{
	return controller.vectorT;
}

void EarningController::add(time_t date, float amount)
{
	controller.vectorT.push_back(Earning(date, amount));
}


void EarningController::add(tm date, float amount)
{
	controller.vectorT.push_back(Earning(mktime(&date), amount));
}



void EarningController::load()
{
	loadController(&controller, controller.fileName);
}
void EarningController::loadBackup()
{
	loadController(&controller, controller.backupFileName);
}





void EarningController::modifyDate(int index, tm date)
{
	controller.vectorT[index].date = mktime(&date);
}

void EarningController::modifyAmount(int index, float amount)
{
	controller.vectorT[index].amount = amount;
}


time_t EarningController::getDate(int index){
	return controller.vectorT[index].date;
}
float EarningController::getAmount(int index){
	return controller.vectorT[index].amount;
}


void EarningController::sortByDate(bool descending)
{
	if (descending)
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEarningByDateDesc);
	else
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEarningByDateAsc);

}

void EarningController::sortByAmount(bool descending)
{
	if (descending)
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEarningByAmountDesc);
	else
		std::sort(controller.vectorT.begin(), controller.vectorT.end(), sortEarningByAmountAsc);

}
std::string EarningController::getProfileName()
{
	return controller.profileName;
}
