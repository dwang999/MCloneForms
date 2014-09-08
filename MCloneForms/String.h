// String.h

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

// INCLUDES
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <msclr\marshal_cppstd.h>

System::String^ convertToSystemString(const std::string& string);
std::string convertToString(float f);
std::string convertToString(time_t date, std::string format);
std::string convertToCurrencyString(float f);
std::string convertSystemToSTDString(System::String^ str);
bool convertStringToTM(std::string str, tm &tm);
System::String^ capitalizeString(System::String^ str);

#endif