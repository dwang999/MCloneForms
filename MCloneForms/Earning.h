// Earning.h

#ifndef EARNING_H_INCLUDED
#define EARNING_H_INCLUDED

// INCLUDES
#include <string>
#include <ctime>
#include <iomanip>

class Earning
{
	friend std::ostream &operator<<(std::ostream &os, const Earning &entry);

	public:
		Earning(time_t date, float amount);
		~Earning();

		std::time_t date;
		float amount;
		static const int NUMOFMEMBERVARIABLES = 2;
		

		
	private:
		Earning();		


};



#endif