// Earning.h

#ifndef EARNING_H_INCLUDED
#define EARNING_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>

class Earning
{
	friend std::ostream &operator<<(std::ostream &os, const Earning &entry);

public:
	Earning(int id, time_t date, float amount);
	~Earning();
	
	int id;
	std::time_t date;
	float amount;
	static const int NUMOFMEMBERVARIABLES = 3;
	static Earning parseTokens(std::string str);



private:
	Earning();		


};



#endif