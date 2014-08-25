// Controller.cpp

#include "stdafx.h"
#include "Controller.h"

// Constructors
Controller::Controller(std::string profileName) : profileName(profileName){}

// Methods
std::string Controller::getProfileName()
{
	return profileName;
}