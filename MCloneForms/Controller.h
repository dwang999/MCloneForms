// Controller.h


// IMPORTANT
// DataType of Controller must have following member variables and functions:
//     int id;
//     static datatype parseTokens(std::string str);



#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>

template <typename T>
class Controller {
public:
	Controller(std::string profileName, std::string controllerName, std::string fileName, std::string backupFileName);
	void save();
	void autoSave();
	void add(T t);
	void remove(int indexToRemove);
	bool backupExists();
	bool deleteBackup();
	std::vector<T> vectorT;
	std::string profileName;
	std::string fileName;
	std::string backupFileName;	
	void loadController( std::string fileName);
	int generateID();

private:
	std::string controllerName;
	bool saveController(std::string fileString);

};

#include "Controller.tcc"



#endif