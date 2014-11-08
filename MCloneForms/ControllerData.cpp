// ControllerData.cpp

#include "stdafx.h"
#include "ControllerData.h"


ControllerData::ControllerData() {}
ControllerData::ControllerData(int id): id(id) {}
ControllerData::~ControllerData(){}

std::ostream& operator<<(std::ostream& os, const ControllerData &data)
{
	os << data.toString().c_str();
	return os;
}

std::string ControllerData::toString() const{	
	std::stringstream ss;
	ss << id;
	return ss.str();
}