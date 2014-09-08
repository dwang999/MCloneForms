//String.cpp

#include "stdafx.h"
#include "String.h"


System::String^ convertToSystemString(const std::string& string)
{
	System::String^ temp = gcnew System::String(string.c_str());
	return temp;
}

std::string convertToCurrencyString(float f)
{
	return "$ " + convertToString(f);
}


std::string convertToString(float f)
{
	char number[20];
	sprintf(number, "%.2f", f);
	return std::string(number);
}

std::string convertToString(time_t date, std::string format)
{
	char dateBuffer [160];
	tm *tempTM = &tm();
	localtime_s (tempTM, &date);
	strftime (dateBuffer, sizeof(dateBuffer), format.c_str(), tempTM);
	return std::string(dateBuffer);
}

std::string convertSystemToSTDString(System::String^ str)
{
	return msclr::interop::marshal_as<std::string>(str);
}


bool convertStringToTM(std::string str, tm &tm)
{	
	int day;
	int month;					 
	int year;
	if(sscanf(str.c_str(), "%d/%d/%d;", &month, &day, &year) == 3)
	{
		tm.tm_mday = day;
		tm.tm_mon = month - 1;
		tm.tm_year = year - 1900;
		return true;
	}
	else
		return false;
}

System::String^ capitalizeString(System::String^ str)
{
	return str -> Substring(0, 1) -> ToUpper() + str -> Substring(1, str->Length - 1) -> ToLower();
}