// Budget.h

#ifndef BUDGET_H_INCLUDED
#define BUDGET_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

class Budget
{
	friend std::ostream &operator<<(std::ostream &os, const Budget &entry);

public:
	Budget(int id, time_t effectiveDate, std::string category, float amount);
	~Budget();

	int id;
	std::time_t effectiveDate;
	std::string category;
	float amount;
	static const int NUMOFMEMBERVARIABLES = 4;
	static Budget parseTokens(std::string str);



private:
	Budget();		


};


#endif