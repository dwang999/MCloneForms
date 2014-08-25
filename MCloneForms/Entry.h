// Entry.h

#ifndef ENTRY_H_INCLUDED
#define ENTRY_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>

class Entry
{
	friend std::ostream &operator<<(std::ostream &os, const Entry &entry);

	public:
		Entry(time_t date, std::string category, std::string subCategory, 
			std::string description, float amount);
		~Entry();

		std::time_t date;
		std::string category;
		std::string subCategory;
		std::string description;
		float amount;
		

		
	private:
		Entry();		


};


static const int NUMOFVARIABLESINENTRY = 5;

#endif