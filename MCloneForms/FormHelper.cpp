// FormHelper.cpp

#include "stdafx.h"
#include "FormHelper.h"

using namespace System::Windows::Forms;

namespace FormHelper {
	void showErrorMessage(System::String^ title, System::String^ text)
	{
		MessageBox::Show(text, title, MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	bool showYesNoMessage(System::String^ title, System::String^ text)
	{
		DialogResult dialogResult =  MessageBox::Show(text, title, MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation);
		if(dialogResult == DialogResult::Yes)
			return true;
		else
			return false;
	}
}