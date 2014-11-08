// Controller.h


// IMPORTANT
// DataType of Controller must have following member variables and functions:



#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>

#include "String.h"

#include "ControllerData.h"

class Controller {
public:
	Controller(std::string profileName, std::string controllerName, std::string fileName, std::string backupFileName);
	virtual ~Controller();
	void save();
	void autoSave();
	void addData(ControllerData* data);
	void remove(int id);
	bool backupExists();
	bool deleteBackup();
	void load();
	void loadBackup();
	int generateID();
	virtual ControllerData* parseTokens(std::string str);

	
	std::vector<ControllerData*> controller;
	std::string profileName;
	std::string fileName;
	std::string backupFileName;	

private:
	std::string controllerName;
	bool saveController(std::string fileString);
	void loadController( std::string fileName);

};




#endif