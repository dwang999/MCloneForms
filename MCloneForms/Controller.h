//Controll
#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <string>

class Controller {
public:
	Controller(std::string profileName);
	virtual void save() = 0;
	virtual void autoSave() = 0;
	virtual void load() = 0;
	virtual void loadBackup() = 0;
	virtual	void remove(int indexToRemove) = 0;
	virtual bool backupExists() = 0;
	virtual bool deleteBackup() = 0;
	std::string getProfileName();

protected:
	std::string profileName;
};



#endif