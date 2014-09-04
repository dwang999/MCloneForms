// CueTextBox.h

#ifndef CUETEXTBOX_H_INCLUDED
#define CUETEXTBOX_H_INCLUDED

#include "String.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

public ref class CueTextBox : TextBox 
{
public: 
	String^ GetCue (){ return cue; };
	void SetCue (String^ cue){ this->cue = cue; updateCue(); };

protected: 
	virtual void OnHandleCreated(EventArgs^ e) override {
		TextBox::OnHandleCreated(e);
		updateCue();
	};
private: 
	String^ cue;
	void updateCue() {
		if (this->IsHandleCreated && cue != nullptr) 
			SendMessage(static_cast<HWND>(this->Handle.ToPointer()), 0x1501, 1, (LPARAM)((LPCTSTR)convertSystemToSTDString(cue).c_str()));
	};
};


#endif