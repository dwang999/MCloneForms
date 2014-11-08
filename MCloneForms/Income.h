// Income.h

#ifndef INCOME_H_INCLUDED
#define INCOME_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

#include "ControllerData.h"

class Income : public ControllerData
{
	friend std::ostream &operator<<(std::ostream &os, const Income &entry);

public:
	static const int NUMOFMEMBERVARIABLES = 3;
	Income(int id, time_t effectiveDate, float amount);
	~Income();
	
	std::string toString() const;

	std::time_t effectiveDate;
	float amount;



private:
	Income();		


};



#endif