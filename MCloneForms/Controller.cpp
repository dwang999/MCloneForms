// Controller.cpp
#include "stdafx.h"
#include "Controller.h"

Controller::Controller(std::string profileName, std::string controllerName, std::string fileName, std::string backupFileName) : 
	profileName(profileName), controllerName(controllerName), fileName(fileName), backupFileName(backupFileName){
}

Controller::~Controller(){
	for (unsigned int i = 0; i < controller.size(); i++)
	{
		delete controller[i];
		controller[i] = NULL;
	}
}
// Methods

bool Controller::saveController(std::string fileString)
{
	std::fstream fs;
	fs.open(fileString, std::fstream::out | std::fstream::trunc);

	if (fs.is_open())
	{
		for(ControllerData* data: controller)
		{
			
			fs << *data << std::endl;
		} 

		fs.close();
		return true;
	}
	else
		return false;
};

// Save Controller and delete the backup
void Controller::save()
{
	if(saveController(fileName))
	{
		if (backupExists())
		{
			if(!deleteBackup())
				throw std::runtime_error(controllerName + "::save : Entries backup was not deleted");
		}
	}
	else
		throw std::runtime_error(controllerName + "::save : Entries save file could not be opened");
}

void Controller::autoSave()
{
	if(!saveController(backupFileName))
		throw std::runtime_error(controllerName + "::save : Entries save file could not be opened");
}

void Controller::remove(int id){
	bool success = false;
	for (size_t i = 0; i < controller.size(); i++)
	{
		if (controller[i] -> id == id)
		{
			controller.erase(controller.begin() + i);
			success = true;
			break;
		}
	}

	if (!success)
		throw std::invalid_argument(controllerName + "::remove : id " + convertSystemToSTDString(id.ToString()) + " not found");

}

int Controller::generateID()
{
	if (controller.empty())
		return 1;
	else
	{
		int largest = 0;
		for (size_t i = 0; i < controller.size(); i++)
		{
			if (controller[i]->id > largest)
				largest = controller[i]->id;
		}

		return largest + 1;

	}
}


void Controller::addData(ControllerData* data)
{

	controller.push_back(data);
}

void Controller::load()
{
	loadController(fileName);
}
void Controller::loadBackup()
{
	loadController(backupFileName);
}

void Controller::loadController(std::string fileName)
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
				{
					this->addData(parseTokens(line));
				}

			}
			fs.close();
		}
	}

bool Controller::backupExists()
{
	std::ifstream ifile(backupFileName.c_str());
	if(ifile.good())
	{
		ifile.close();
		return true;
	}
	else
		return false;
}

bool Controller::deleteBackup(){
	if(std::remove(backupFileName.c_str()) != 0)
		return false;
	else
		return true;
}

ControllerData* Controller::parseTokens(std::string str){
	
	std::string delim = "/";
	std::vector<std::string> tokens;
	tokens.reserve(ControllerData::NUMOFMEMBERVARIABLES);
	unsigned int delimPos = str.find(delim);
	int start = 0;
	while (delimPos != std::string::npos)
	{
		std::string token = str.substr(start, delimPos - start);
		start = delimPos + 1;
		delimPos = str.find(delim, start);
		tokens.push_back(token);
	}

	if (tokens.size() != ControllerData::NUMOFMEMBERVARIABLES)
	{
		throw std::runtime_error("ControllerData::parseTokens : Incorrect number of variables in entrys");
	}
	// Parse tokens 
	int id;

	// Format: [ID]/[EffectiveDate]/[Category]/[Amount]

	for (int i = 0; i < ControllerData::NUMOFMEMBERVARIABLES; i++)
	{
		switch (i)
		{
		case 0: // id
			id = atoi(tokens[i].c_str());
			break;
		}
	}

	return new ControllerData(id);
}

