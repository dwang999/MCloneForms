#pragma once

#include "EntriesUserControl.h"
#include "BudgetsUserControl.h"
#include "ReportsUserControl.h"
#include "IncomesUserControl.h"

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
	private:
		EntryController* entryController;
		BudgetController* budgetController;
		IncomeController* incomeController;
		char * const profileName;


	public:
		MainWindow(void): profileName("Test"), entryController(nullptr), budgetController(nullptr)
		{
			InitializeComponent();
			entryController = new EntryController(profileName);
			entriesUserControl ->Init(entryController);
			budgetController = new BudgetController(profileName);
			budgetsUserControl ->Init(budgetController);
			incomeController = new IncomeController(profileName);
			incomesUserControl ->Init(incomeController);
			reportsUserControl -> Init(entryController, budgetController, incomeController);
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

			if (entryController)
			{
				delete entryController;
				entryController = NULL;
			}
			if (budgetController)
			{
				delete budgetController;
				budgetController = NULL;
			}
			if (incomeController)
			{
				delete incomeController;
				incomeController = NULL;
			}
		}

		System::Windows::Forms::TabControl^  tabControl;

		System::Windows::Forms::TabPage^  Expenses;
		System::Windows::Forms::TabPage^  Budgets;
		MCloneForms::EntriesUserControl^  entriesUserControl;
	    System::Windows::Forms::TabPage^  Incomes;
		MCloneForms::BudgetsUserControl^  budgetsUserControl;
		System::Windows::Forms::TabPage^  Reports;
		MCloneForms::ReportsUserControl^  reportsUserControl; 
		MCloneForms::IncomesUserControl^  incomesUserControl;



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
			this->Expenses = (gcnew System::Windows::Forms::TabPage());
			this->entriesUserControl = (gcnew MCloneForms::EntriesUserControl());
			this->Budgets = (gcnew System::Windows::Forms::TabPage());
			this->budgetsUserControl = (gcnew MCloneForms::BudgetsUserControl());
			this->Incomes = (gcnew System::Windows::Forms::TabPage());
			this->incomesUserControl = (gcnew MCloneForms::IncomesUserControl());
			this->Reports = (gcnew System::Windows::Forms::TabPage());
			this->reportsUserControl = (gcnew MCloneForms::ReportsUserControl());
			this->tabControl->SuspendLayout();
			this->Expenses->SuspendLayout();
			this->Budgets->SuspendLayout();
			this->Incomes->SuspendLayout();
			this->Reports->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->Expenses);
			this->tabControl->Controls->Add(this->Budgets);
			this->tabControl->Controls->Add(this->Incomes);
			this->tabControl->Controls->Add(this->Reports);
			this->tabControl->Location = System::Drawing::Point(-1, 0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(804, 763);
			this->tabControl->TabIndex = 7;
			this->tabControl->TabStop = false;
			// 
			// Expenses
			// 
			this->Expenses->Controls->Add(this->entriesUserControl);
			this->Expenses->Location = System::Drawing::Point(4, 22);
			this->Expenses->Name = L"Expenses";
			this->Expenses->Padding = System::Windows::Forms::Padding(3);
			this->Expenses->Size = System::Drawing::Size(796, 737);
			this->Expenses->TabIndex = 0;
			this->Expenses->Text = L"Expenses";
			this->Expenses->UseVisualStyleBackColor = true;
			// 
			// entriesUserControl
			// 
			this->entriesUserControl->Location = System::Drawing::Point(3, 6);
			this->entriesUserControl->Name = L"entriesUserControl";
			this->entriesUserControl->Size = System::Drawing::Size(788, 715);
			this->entriesUserControl->TabIndex = 0;
			// 
			// Budgets
			// 
			this->Budgets->Controls->Add(this->budgetsUserControl);
			this->Budgets->Location = System::Drawing::Point(4, 22);
			this->Budgets->Name = L"Budgets";
			this->Budgets->Padding = System::Windows::Forms::Padding(3);
			this->Budgets->Size = System::Drawing::Size(796, 737);
			this->Budgets->TabIndex = 1;
			this->Budgets->Text = L"Budgets";
			this->Budgets->UseVisualStyleBackColor = true;
			// 
			// budgetsUserControl
			// 
			this->budgetsUserControl->Location = System::Drawing::Point(3, 6);
			this->budgetsUserControl->Name = L"budgetsUserControl";
			this->budgetsUserControl->Size = System::Drawing::Size(788, 715);
			this->budgetsUserControl->TabIndex = 0;
			// 
			// Incomes
			// 
			this->Incomes->Controls->Add(this->incomesUserControl);
			this->Incomes->Location = System::Drawing::Point(4, 22);
			this->Incomes->Name = L"Incomes";
			this->Incomes->Padding = System::Windows::Forms::Padding(3);
			this->Incomes->Size = System::Drawing::Size(796, 737);
			this->Incomes->TabIndex = 2;
			this->Incomes->Text = L"Incomes";
			this->Incomes->UseVisualStyleBackColor = true;
			// 
			// incomesUserControl
			// 
			this->incomesUserControl->Location = System::Drawing::Point(3, 6);
			this->incomesUserControl->Name = L"incomesUserControl";
			this->incomesUserControl->Size = System::Drawing::Size(788, 715);
			this->incomesUserControl->TabIndex = 0;
			// 
			// Reports
			// 
			this->Reports->Controls->Add(this->reportsUserControl);
			this->Reports->Location = System::Drawing::Point(4, 22);
			this->Reports->Name = L"Reports";
			this->Reports->Padding = System::Windows::Forms::Padding(3);
			this->Reports->Size = System::Drawing::Size(796, 737);
			this->Reports->TabIndex = 3;
			this->Reports->Text = L"Reports";
			this->Reports->UseVisualStyleBackColor = true;
			// 
			// reportsUserControl
			// 
			this->reportsUserControl->Location = System::Drawing::Point(3, 6);
			this->reportsUserControl->Name = L"reportsUserControl";
			this->reportsUserControl->Size = System::Drawing::Size(788, 715);
			this->reportsUserControl->TabIndex = 0;
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(800, 761);
			this->Controls->Add(this->tabControl);
			this->KeyPreview = true;
			this->Name = L"MainWindow";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainWindow::MainWindow_FormClosing);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainWindow::MainWindow_KeyDown);
			this->tabControl->ResumeLayout(false);
			this->Expenses->ResumeLayout(false);
			this->Budgets->ResumeLayout(false);
			this->Incomes->ResumeLayout(false);
			this->Reports->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
#pragma region Events
	private: System::Void MainWindow_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 if(!entriesUserControl->closeUserControl())
				 {
					 e->Cancel = true;
				 }
				 if(!budgetsUserControl->closeUserControl())
				 {
					 e->Cancel = true;
				 }
				 if(!incomesUserControl->closeUserControl())
				 {
					 e->Cancel = true;
				 }
			 }
private: System::Void MainWindow_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			 if (CanFocus)
			 {
				 if (entriesUserControl -> Visible)
				 {
					 entriesUserControl -> KeyDown(e);
				 }
				 else if (budgetsUserControl -> Visible)
				 {
					 budgetsUserControl -> KeyDown(e);
				 }
				 else if (incomesUserControl -> Visible)
				 {
					 incomesUserControl -> KeyDown(e);
				 }
			 }
		 }
#pragma endregion
};

}

