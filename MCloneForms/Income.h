// Income.h

#ifndef INCOME_H_INCLUDED
#define INCOME_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

class Income
{
	friend std::ostream &operator<<(std::ostream &os, const Income &entry);

public:
	Income(int id, time_t effectiveDate, float amount);
	~Income();
	
	int id;
	std::time_t effectiveDate;
	float amount;
	static const int NUMOFMEMBERVARIABLES = 3;
	static Income parseTokens(std::string str);



private:
	Income();		


};



#endif