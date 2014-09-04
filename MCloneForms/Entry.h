// Entry.h

#ifndef ENTRY_H_INCLUDED
#define ENTRY_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

class Entry
{
	friend std::ostream &operator<<(std::ostream &os, const Entry &entry);

public:
	Entry(int id, time_t date, std::string category, 
		std::string description, float amount);
	~Entry();

	int id;
	std::time_t date;
	std::string category;
	std::string description;
	float amount;
	static const int NUMOFMEMBERVARIABLES = 5;
	static Entry parseTokens(std::string str);



private:
	Entry();		


};


#endif