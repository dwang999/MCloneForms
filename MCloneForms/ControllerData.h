// ControllerData.h

#ifndef CONTROLLERDATA_H_INCLUDED
#define CONTROLLERDATA_H_INCLUDED

// INCLUDES
#include <iomanip>
#include <sstream>


class ControllerData
{
	
	friend std::ostream &operator<<(std::ostream &os, const ControllerData &data);
public:
	int id;
	ControllerData();
	ControllerData(int id);
	~ControllerData();
	virtual std::string toString() const;
	
	static const int NUMOFMEMBERVARIABLES = 1; 



};


#endif