// Entry.h

#ifndef ENTRY_H_INCLUDED
#define ENTRY_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

#include "ControllerData.h"

class Entry : public ControllerData
{
public:
	static const int NUMOFMEMBERVARIABLES = 5;

	Entry(int id, time_t date, std::string category, 
		std::string description, float amount);
	~Entry();
	
	std::string toString() const;

	std::time_t date;
	std::string category;
	std::string description;
	float amount;




private:
	Entry();		


};


#endif