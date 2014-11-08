// Budget.h

#ifndef BUDGET_H_INCLUDED
#define BUDGET_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

// MY CLASS INCLUDES
#include "ControllerData.h"


class Budget : public ControllerData
{

public:
	// 3 Member variables from Budget and 1 from ControllerData
	static const int NUMOFMEMBERVARIABLES = 4; 
	

	Budget(int id, time_t effectiveDate, std::string category, float amount);
	~Budget();

	std::string toString() const;

	std::time_t effectiveDate;
	std::string category;
	float amount;




private:
	Budget();		


};


#endif