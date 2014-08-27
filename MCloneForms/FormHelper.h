// FormHelper.h

#ifndef FORMHELPER_H_INCLUDED
#define FORMHELPER_H_INCLUDED

namespace FormHelper {
	void showErrorMessage(System::String^ title, System::String^ text);
	bool showYesNoMessage(System::String^ title, System::String^ text);
}

#endif