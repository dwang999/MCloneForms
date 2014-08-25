#pragma once

#include "EntriesUserControl.h"

namespace MCloneForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{

	public:
		MainWindow(void)
		{
			InitializeComponent();
			tabControl -> ItemSize = System::Drawing::Size(90, 30);

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

		System::Windows::Forms::TabControl^  tabControl;

		System::Windows::Forms::TabPage^  Spendings;
		System::Windows::Forms::TabPage^  Earnings;
		MCloneForms::EntriesUserControl^  entriesUserControl;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->Spendings = (gcnew System::Windows::Forms::TabPage());
			this->entriesUserControl = (gcnew MCloneForms::EntriesUserControl());
			this->Earnings = (gcnew System::Windows::Forms::TabPage());
			this->tabControl->SuspendLayout();
			this->Spendings->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->Spendings);
			this->tabControl->Controls->Add(this->Earnings);
			this->tabControl->Location = System::Drawing::Point(-1, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(804, 763);
			this->tabControl->TabIndex = 7;
			// 
			// Spendings
			// 
			this->Spendings->Controls->Add(this->entriesUserControl);
			this->Spendings->Location = System::Drawing::Point(4, 22);
			this->Spendings->Name = L"Spendings";
			this->Spendings->Padding = System::Windows::Forms::Padding(3);
			this->Spendings->Size = System::Drawing::Size(796, 737);
			this->Spendings->TabIndex = 0;
			this->Spendings->Text = L"Spendings";
			this->Spendings->UseVisualStyleBackColor = true;
			// 
			// entriesUserControl
			// 
			this->entriesUserControl->Location = System::Drawing::Point(3, 6);
			this->entriesUserControl->Name = L"entriesUserControl";
			this->entriesUserControl->Size = System::Drawing::Size(788, 715);
			this->entriesUserControl->TabIndex = 0;
			// 
			// Earnings
			// 
			this->Earnings->Location = System::Drawing::Point(4, 22);
			this->Earnings->Name = L"Earnings";
			this->Earnings->Padding = System::Windows::Forms::Padding(3);
			this->Earnings->Size = System::Drawing::Size(796, 737);
			this->Earnings->TabIndex = 1;
			this->Earnings->Text = L"Earnings";
			this->Earnings->UseVisualStyleBackColor = true;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(800, 761);
			this->Controls->Add(this->tabControl);
			this->Name = L"MainWindow";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainWindow::MainWindow_FormClosing);
			this->tabControl->ResumeLayout(false);
			this->Spendings->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
#pragma region Events
	private: System::Void MainWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 if(!entriesUserControl->closeUserControl())
				 {
					 e->Cancel = true;
				 }
			 }
#pragma endregion
	};

}

