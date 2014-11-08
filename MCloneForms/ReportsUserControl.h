#pragma once

#include <map>
#include "EntryController.h"
#include "BudgetController.h"
#include "IncomeController.h"
#include "String.h"
#include <time.h>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace MCloneForms {

	/// <summary>
	/// Summary for ReportsUserControl
	/// </summary>
	public ref class ReportsUserControl : public System::Windows::Forms::UserControl
	{
		// private member variables
	private: 
		EntryController* entryController;
		BudgetController* budgetController;
		IncomeController* incomeController;
		enum class ActiveChart {OverallBar, OverallNet, MonthlyBar, MonthlyNet, IncomeOverallBar, IncomeOverallNet};
		ActiveChart activeChart;

		std::set<time_t>::reverse_iterator* iter;
	private: System::Windows::Forms::ComboBox^  chartType;
	private: System::Windows::Forms::Label^  chartTypeLabel;


			 std::set<time_t>* entryDates;



	public:
		ReportsUserControl(void)
		{
			InitializeComponent();
		}

		void Init(EntryController* tempEntryController, BudgetController* tempBudgetController, IncomeController* tempIncomeController)
		{
			entryController = tempEntryController;
			budgetController = tempBudgetController;
			incomeController = tempIncomeController;
			createChart(activeChart);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ReportsUserControl()
		{
			if (components)
			{
				delete components;
			}

			if (entryDates)
			{
				delete entryDates;
				entryDates = NULL;
			}

			if (iter)
			{
				delete iter;
				iter = NULL;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  reportChart;

	private: System::Windows::Forms::Button^  monthForward;
	private: System::Windows::Forms::Button^  monthBackward;

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea2 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			this->reportChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->monthForward = (gcnew System::Windows::Forms::Button());
			this->monthBackward = (gcnew System::Windows::Forms::Button());
			this->chartType = (gcnew System::Windows::Forms::ComboBox());
			this->chartTypeLabel = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->reportChart))->BeginInit();
			this->SuspendLayout();
			// 
			// reportChart
			// 
			chartArea2->AxisX->Title = L"Date";
			chartArea2->AxisY->Title = L"Amount";
			chartArea2->Name = L"ChartArea";
			this->reportChart->ChartAreas->Add(chartArea2);
			legend2->Name = L"Legend";
			this->reportChart->Legends->Add(legend2);
			this->reportChart->Location = System::Drawing::Point(0, 20);
			this->reportChart->Name = L"reportChart";
			this->reportChart->Size = System::Drawing::Size(768, 715);
			this->reportChart->TabIndex = 0;
			this->reportChart->Text = L"chart";
			this->reportChart->VisibleChanged += gcnew System::EventHandler(this, &ReportsUserControl::reportChart_VisibleChanged);
			// 
			// monthForward
			// 
			this->monthForward->Location = System::Drawing::Point(545, 60);
			this->monthForward->Name = L"monthForward";
			this->monthForward->Size = System::Drawing::Size(75, 23);
			this->monthForward->TabIndex = 1;
			this->monthForward->Text = L"-->";
			this->monthForward->UseVisualStyleBackColor = true;
			this->monthForward->Click += gcnew System::EventHandler(this, &ReportsUserControl::monthForward_Click);
			// 
			// monthBackward
			// 
			this->monthBackward->Location = System::Drawing::Point(105, 60);
			this->monthBackward->Name = L"monthBackward";
			this->monthBackward->Size = System::Drawing::Size(75, 23);
			this->monthBackward->TabIndex = 2;
			this->monthBackward->Text = L"<--";
			this->monthBackward->UseVisualStyleBackColor = true;
			this->monthBackward->Click += gcnew System::EventHandler(this, &ReportsUserControl::monthBackward_Click);
			// 
			// chartType
			// 
			this->chartType->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->chartType->FormattingEnabled = true;
			this->chartType->Items->AddRange(gcnew cli::array< System::Object^  >(6) {L"Overall ", L"Overall Net Expenses", L"Monthly", 
				L"Monthly Net Expenses", L"Overall Income", L"Overall Income Net Expenses"});
			this->chartType->Location = System::Drawing::Point(193, 2);
			this->chartType->Name = L"chartType";
			this->chartType->Size = System::Drawing::Size(200, 21);
			this->chartType->TabIndex = 3;
			this->chartType->SelectedIndexChanged += gcnew System::EventHandler(this, &ReportsUserControl::chartType_SelectedIndexChanged);
			// 
			// chartTypeLabel
			// 
			this->chartTypeLabel->AutoSize = true;
			this->chartTypeLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->chartTypeLabel->Location = System::Drawing::Point(105, 3);
			this->chartTypeLabel->Name = L"chartTypeLabel";
			this->chartTypeLabel->Size = System::Drawing::Size(82, 17);
			this->chartTypeLabel->TabIndex = 0;
			this->chartTypeLabel->Text = L"Chart Type:";
			// 
			// ReportsUserControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->chartTypeLabel);
			this->Controls->Add(this->chartType);
			this->Controls->Add(this->monthBackward);
			this->Controls->Add(this->monthForward);
			this->Controls->Add(this->reportChart);
			this->Name = L"ReportsUserControl";
			this->Size = System::Drawing::Size(788, 715);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->reportChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void reportChart_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				 DataVisualization::Charting::Chart^ chart = (DataVisualization::Charting::Chart^) sender;
				 if (chart->Visible == true)
				 {
					 createChart(activeChart);
				 }
			 }

			 System::Void monthForward_Click(System::Object^  sender, System::EventArgs^  e) {
				 std::advance(*iter, 1);
				 if (*iter != entryDates->rend())
				 {
					 bool net = false;
					 if (activeChart == ActiveChart::MonthlyNet)
						 net = true;

					 time_t month = **iter;
					 createBudgetChartMonth(net, month);

					 monthBackward -> Enabled = true;
					 if(std::next(*iter, 1) == entryDates->rend())
						 monthForward -> Enabled = false;
				 }
			 }
			 System::Void monthBackward_Click(System::Object^  sender, System::EventArgs^  e) {
				 std::advance(*iter, -1);
				 time_t month = **iter;
				 bool net = false;
				 if (activeChart == ActiveChart::MonthlyNet)
					 net = true;
				 createBudgetChartMonth(net, month);
				 monthForward -> Enabled = true;
				 if (*iter == entryDates->rbegin())
				 {
					 monthBackward -> Enabled = false;
				 }
			 }
			 System::Void chartType_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
				 ComboBox^ comboBox = (ComboBox^) sender;
				 switch(comboBox -> SelectedIndex)
				 {
				 case 0:
					 activeChart = ActiveChart::OverallBar;
					 break;
				 case 1:
					 activeChart = ActiveChart::OverallNet;
					 break;
				 case 2:
					 activeChart = ActiveChart::MonthlyBar;
					 break;
				 case 3:
					 activeChart = ActiveChart::MonthlyNet;
					 break;
				 case 4:
					 activeChart = ActiveChart::IncomeOverallBar;
					 break;
				 case 5:
					 activeChart = ActiveChart::IncomeOverallNet;
					 break;
				 default:
					 activeChart = ActiveChart::OverallBar;
					 break;
				 }

				 createChart(activeChart);

			 }

#pragma region Private Methods
			 void createIncomeChartOverall(bool netExpenses)
			 {
				 budgetChartMonthVisibility(false);
				 reportChart -> Series -> Clear();
				 reportChart -> Titles ->Clear();
				 if (netExpenses)
				 {
					 activeChart = ActiveChart::IncomeOverallBar;
					 reportChart-> Series -> Add("NetExpenses");
					 reportChart-> Series["NetExpenses"] -> ToolTip = "#VALX: $#VAL";
					 reportChart-> Series["NetExpenses"] -> IsVisibleInLegend = false;
				 }
				 else
				 {
					 activeChart = ActiveChart::IncomeOverallNet;
					 reportChart-> Series -> Add("Expenses");
					 reportChart-> Series -> Add("Incomes");
					 reportChart->Series["Incomes"] -> ToolTip = "#VALX: $#VAL";
					 reportChart->Series["Expenses"] -> ToolTip = "#VALX: $#VAL";
				 }
				 reportChart -> ChartAreas["ChartArea"] -> RecalculateAxesScale();
				 reportChart -> ChartAreas["ChartArea"]->AxisY->LabelStyle->Format = "$ #";
				 reportChart -> ChartAreas["ChartArea"] -> AxisY -> Title = "Amount";
				 reportChart -> ChartAreas["ChartArea"] -> AxisX -> Title = "Date";

				 std::vector<Entry*> entries = entryController->getEntries();
				 std::map<time_t, float> entryData = std::map<time_t, float>();
				 std::vector<Income*> incomes = incomeController->getIncomes();
				 std::map<time_t, float> incomeData = std::map<time_t, float>();
				 
				 for (size_t i = 0; i < entries.size(); i++)
				 {
					 // Set day to the first
					 const time_t entryDate = entries[i]->date;
					 tm tm;
					 localtime_s(&tm, &entryDate);
					 tm.tm_mday = 1;
					 formatTMMonthDayYear(tm);
					 time_t date;
					 date = mktime(&tm);
					 if (entryData.find(date) == entryData.end())
					 {
						 entryData.insert(std::pair<time_t, float>(date, entries[i]->amount));
					 }
					 else
						 entryData[date] += entries[i]->amount;
				 }

				 // Add income up based on entry date
				 std::set<std::string> entryCategories = entryController->getDistinctCategories();
				 for (std::pair<time_t, float> entry: entryData)
				 {
					 incomeData.insert(std::pair<time_t, float>(entry.first, 0));

					 // Find budget entry that has greatest date that is less than entry date
					 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
					 for (auto income : incomes)
					 {
						 if (income->effectiveDate <= entry.first && income->effectiveDate > max.first)
							 max = std::pair<time_t, float>(income->effectiveDate, income->amount);
					 }

					 incomeData[entry.first] += max.second;

				 }

				 //Title
				 std::map<time_t, float>::iterator iterator = std::map<time_t, float>::iterator(entryData.end());
				 std::advance(iterator, -1);
				 std::string title = convertToString(entryData.begin() -> first, "%b %Y") + " - " + convertToString(iterator -> first, "%b %Y");
				 reportChart -> Titles -> Add(gcnew DataVisualization::Charting::Title(convertToSystemString(title), DataVisualization::Charting::Docking::Top, gcnew Drawing::Font("Verdana", 14), Color::Black));
				

				 if (netExpenses)
				 {
					 for (std::pair<time_t, float> entry: entryData)
					 {
						 float netSpending = incomeData[entry.first] - entry.second;
						 int index = reportChart -> Series["NetExpenses"] -> Points -> AddXY(convertToSystemString(convertToString(entry.first, "%b %Y")), Math::Round(netSpending, 2) + 0.00);

						 if (netSpending >= 0)
							 reportChart -> Series["NetExpenses"] -> Points[index] ->Color = Color::Green;
						 else
							 reportChart -> Series["NetExpenses"] -> Points[index] ->Color = Color::Red;
					 }
				 }
				 else
				 {
					 for (std::pair<time_t, float> entry: entryData)
					 {
						 reportChart -> Series["Expenses"] -> Points -> AddXY(convertToSystemString(convertToString(entry.first, "%b %Y")), Math::Round(entry.second, 2) + 0.00);
					 }
					 for (std::pair<time_t, float> income: incomeData)
					 {
						 reportChart -> Series["Incomes"] -> Points -> AddXY(convertToSystemString(convertToString(income.first, "%b %Y")), Math::Round(income.second, 2) + 0.00);
					 }

				 }


			 }
			 void createBudgetChartMonth(bool netExpenses, time_t month)
			 {
				 budgetChartMonthVisibility(true);
				 reportChart -> Series -> Clear();
				 reportChart -> Titles ->Clear();
				 if (netExpenses)
				 {
					 monthForward -> Location = Point(645, monthForward->Location.Y);
					 activeChart = ActiveChart::MonthlyNet;
					 reportChart-> Series -> Add("NetExpenses");
					 reportChart-> Series["NetExpenses"] -> ToolTip = "#VALX: $#VAL";
					 reportChart-> Series["NetExpenses"] -> IsVisibleInLegend = false;
				 }
				 else
				 {
					 monthForward -> Location = Point(545, monthForward->Location.Y);
					 activeChart = ActiveChart::MonthlyBar;
					 reportChart-> Series -> Add("Expenses");
					 reportChart-> Series -> Add("Budgets");
					 reportChart->Series["Budgets"] -> ToolTip = "#VALX: $#VAL";
					 reportChart->Series["Expenses"] -> ToolTip = "#VALX: $#VAL";
				 }
				 reportChart -> Titles -> Add(gcnew DataVisualization::Charting::Title(convertToSystemString(convertToString(month, "%b %Y")), DataVisualization::Charting::Docking::Top, gcnew Drawing::Font("Verdana", 14), Color::Black));

				 reportChart -> ChartAreas["ChartArea"] -> RecalculateAxesScale();
				 reportChart -> ChartAreas["ChartArea"] -> AxisY -> Title = "Amount";
				 reportChart -> ChartAreas["ChartArea"] -> AxisX -> Title = "Category";
				 reportChart -> ChartAreas["ChartArea"]->AxisY->LabelStyle->Format = "$ #";

				 // create a time_t that is month parameter + 1 month
				 tm temp;
				 localtime_s(&temp, &month);
				 temp.tm_mon = (temp.tm_mon + 1);
				 time_t endOfMonth = mktime(&temp);

				 std::vector<Entry*> entries = entryController->getEntries();
				 std::map<std::string, float> categoryData = std::map<std::string, float>();
				 std::vector<Budget*> budgets = budgetController->getBudgets();
				 std::map<std::string, float> budgetData = std::map<std::string, float>();

				 for (size_t i = 0; i < entries.size(); i++)
				 {
					 if (entries[i]->date < endOfMonth && entries[i]->date >= month)
					 {
						 if (categoryData.find(entries[i]->category) == categoryData.end())
						 {
							 categoryData.insert(std::pair<std::string, float>(entries[i]->category, entries[i]->amount));
						 }
						 else
							 categoryData[entries[i]->category] += entries[i]->amount;
					 }
				 }


				 for (std::pair<std::string, float> category: categoryData)
				 {
					 budgetData.insert(std::pair<std::string, float>(category.first, 0));

					 // Find budget entry that has greatest date that is less than entry date
					 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
					 for (auto budget : budgets)
					 {
						 if (budget->category == category.first && budget->effectiveDate <= month && budget->effectiveDate > max.first)
							 max = std::pair<time_t, float>(budget->effectiveDate, budget->amount);
					 }

					 // If there is not budget for category then assign it to 0
					 if (max.first != 0)
						 budgetData[category.first] = max.second;

				 }


				 for (size_t i = 0; i < budgets.size(); i++)
				 {
					 if (budgetData.find(budgets[i]->category) == budgetData.end())
					 {
						 std::string hi = budgets[i]->category;
						 // Find budget entry that has greatest date that is less than entry date
						 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
						 for (auto budget : budgets)
						 {
							 if (budget->category == budgets[i]->category && budget->effectiveDate <= month && budget->effectiveDate > max.first)
								 max = std::pair<time_t, float>(budget->effectiveDate, budget->amount);
						 }

						 budgetData.insert(std::pair<std::string, float>(budgets[i]->category, max.second));
						 categoryData.insert(std::pair<std::string, float>(budgets[i]->category, 0));
					 }		
				 }

				 if (netExpenses)
				 {
					 for (std::pair<std::string, float> category: categoryData)
					 {
						 float netSpending = budgetData[category.first] - category.second;
						 int index = reportChart -> Series["NetExpenses"] -> Points -> AddXY(convertToSystemString(category.first), Math::Round(netSpending, 2) + 0.00);

						 if (netSpending >= 0)
							 reportChart -> Series["NetExpenses"] -> Points[index] ->Color = Color::Green;
						 else
							 reportChart -> Series["NetExpenses"] -> Points[index] ->Color = Color::Red;
					 }
				 }
				 else
				 {
					 for (std::pair<std::string, float> category: categoryData)
					 {
						 reportChart -> Series["Expenses"] -> Points -> AddXY(convertToSystemString(category.first), Math::Round(category.second, 2) + 0.00);
					 }
					 for (std::pair<std::string, float> budget: budgetData)
					 {
						 reportChart -> Series["Budgets"] -> Points -> AddXY(convertToSystemString(budget.first), Math::Round(budget.second, 2) + 0.00);
					 }
				 }
			 }

			 void createBudgetChartOverall(bool netExpenses)
			 {
				 budgetChartMonthVisibility(false);
				 reportChart -> Series -> Clear();
				 reportChart -> Titles ->Clear();
				 if (netExpenses)
				 {
					 activeChart = ActiveChart::OverallNet;
					 reportChart-> Series -> Add("NetExpenses");
					 reportChart-> Series["NetExpenses"] -> ToolTip = "#VALX: $#VAL";
					 reportChart-> Series["NetExpenses"] -> IsVisibleInLegend = false;
				 }
				 else
				 {
					 activeChart = ActiveChart::OverallBar;
					 reportChart-> Series -> Add("Expenses");
					 reportChart-> Series -> Add("Budgets");
					 reportChart->Series["Budgets"] -> ToolTip = "#VALX: $#VAL";
					 reportChart->Series["Expenses"] -> ToolTip = "#VALX: $#VAL";
				 }
				 reportChart -> ChartAreas["ChartArea"] -> RecalculateAxesScale();
				 reportChart -> ChartAreas["ChartArea"]->AxisY->LabelStyle->Format = "$ #";
				 reportChart -> ChartAreas["ChartArea"] -> AxisY -> Title = "Amount";
				 reportChart -> ChartAreas["ChartArea"] -> AxisX -> Title = "Date";

				 std::vector<Entry*> entries = entryController->getEntries();
				 std::map<time_t, float> entryData = std::map<time_t, float>();
				 std::vector<Budget*> budgets = budgetController->getBudgets();
				 std::map<time_t, float> budgetData = std::map<time_t, float>();
				 
				 for (size_t i = 0; i < entries.size(); i++)
				 {
					 // Set day to the first
					 const time_t entryDate = entries[i]->date;
					 tm tm;
					 localtime_s(&tm, &entryDate);
					 tm.tm_mday = 1;
					 formatTMMonthDayYear(tm);
					 time_t date;
					 date = mktime(&tm);
					 if (entryData.find(date) == entryData.end())
					 {
						 entryData.insert(std::pair<time_t, float>(date, entries[i]->amount));
					 }
					 else
						 entryData[date] += entries[i]->amount;
				 }

				 // Add budgets up based on categories in entries
				 std::set<std::string> entryCategories = entryController->getDistinctCategories();
				 for (std::pair<time_t, float> entry: entryData)
				 {
					 budgetData.insert(std::pair<time_t, float>(entry.first, 0));

					 for (auto category: entryCategories)
					 {
						 // Find budget entry that has greatest date that is less than entry date
						 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
						 for (auto budget : budgets)
						 {
							 if (budget->category == category && budget->effectiveDate <= entry.first && budget->effectiveDate > max.first)
								 max = std::pair<time_t, float>(budget->effectiveDate, budget->amount);
						 }

						 budgetData[entry.first] += max.second;


					 }
				 }

				 // Add budget categories that may not have been an entry category
				 std::set<std::string> budgetCategories  = budgetController->getDistinctCategories();
				 for(auto category :budgetCategories)
				 {
					 if (entryCategories.find(category) == entryCategories.end())
					 {

						 for (auto budgetDataEntry :budgetData)
						 {
							 // For each budgetData find the budgetEntry which should be added to the budget
							 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
							 for (auto budget : budgets)
							 {
								if (budget->category == category && budget->effectiveDate <= budgetDataEntry.first && budget->effectiveDate > max.first)
									max = std::pair<time_t, float>(budget->effectiveDate, budget->amount);
							 }

							 budgetData[budgetDataEntry.first] += max.second;
						 }
						 
					 }

				 }

				 //Title
				 std::map<time_t, float>::iterator iterator = std::map<time_t, float>::iterator(entryData.end());
				 std::advance(iterator, -1);
				 std::string title = convertToString(entryData.begin() -> first, "%b %Y") + " - " + convertToString(iterator -> first, "%b %Y");
				 reportChart -> Titles -> Add(gcnew DataVisualization::Charting::Title(convertToSystemString(title), DataVisualization::Charting::Docking::Top, gcnew Drawing::Font("Verdana", 14), Color::Black));
				

				 if (netExpenses)
				 {
					 for (std::pair<time_t, float> entry: entryData)
					 {
						 float netSpending = budgetData[entry.first] - entry.second;
						 int index = reportChart -> Series["NetExpenses"] -> Points -> AddXY(convertToSystemString(convertToString(entry.first, "%b %Y")), Math::Round(netSpending, 2) + 0.00);

						 if (netSpending >= 0)
							 reportChart -> Series["NetExpenses"] -> Points[index] ->Color = Color::Green;
						 else
							 reportChart -> Series["NetExpenses"] -> Points[index] ->Color = Color::Red;
					 }
				 }
				 else
				 {
					 for (std::pair<time_t, float> entry: entryData)
					 {
						 reportChart -> Series["Expenses"] -> Points -> AddXY(convertToSystemString(convertToString(entry.first, "%b %Y")), Math::Round(entry.second, 2) + 0.00);
					 }
					 for (std::pair<time_t, float> budget: budgetData)
					 {
						 reportChart -> Series["Budgets"] -> Points -> AddXY(convertToSystemString(convertToString(budget.first, "%b %Y")), Math::Round(budget.second, 2) + 0.00);
					 }

				 }
			 }

			 void setEntryDates()
			 {
				 if (entryDates)
				 {
					 delete entryDates;
					 entryDates = NULL;
				 }

				 entryDates = new std::set<time_t>();
				 std::vector<Entry*> entries = entryController->getEntries();
				 for (size_t i = 0; i < entries.size(); i++)
				 {
					 // Set day to the first
					 const time_t entryDate = entries[i]->date;
					 tm tm;
					 localtime_s (&tm, &entryDate);
					 tm.tm_mday = 1;
					 formatTMMonthDayYear(tm);
					 time_t date;
					 date = mktime(&tm);
					 entryDates->insert(date);
				 }
			 }

			 void formatTMMonthDayYear(tm &tm)
			 {
				 tm.tm_sec = 0;
				 tm.tm_min = 0;
				 tm.tm_hour = 0;
				 tm.tm_wday = 0;
				 tm.tm_isdst = 0;
			 }

			 void budgetChartMonthVisibility(bool visible)
			 {
				 monthForward -> Visible = visible;
				 monthBackward -> Visible = visible;
			 }


			 // Call once before creating BudgetChartMonth
			 void initBudgetChartMonth(bool net)
			 {
				 monthBackward -> Enabled = true;	
				 monthForward -> Enabled = true;

				 setEntryDates();
				 if (iter)
				 {
					 delete iter;
					 iter = NULL;
				 }

				 iter = new std::set<time_t>::reverse_iterator(entryDates->rbegin());	
				 monthBackward -> Enabled = false;		
				 if (*iter != entryDates->rend())
				 {
					 time_t firstMonth = **iter;
					 createBudgetChartMonth(net, firstMonth);
				 }
				 else
					 monthForward -> Enabled = false;
			 }

			 void createChart(ActiveChart activeChart)
			 {
				 switch (activeChart)
				 {
				 case ActiveChart::OverallBar:
					 createBudgetChartOverall(false);
					 break;
				 case ActiveChart::OverallNet:
					 createBudgetChartOverall(true);
					 break;
				 case ActiveChart::MonthlyBar:
					 initBudgetChartMonth(false);
					 break;
				 case ActiveChart::MonthlyNet:
					 initBudgetChartMonth(true);
					 break;
				 case ActiveChart::IncomeOverallBar:
					 createIncomeChartOverall(false);
					 break;
				 case ActiveChart::IncomeOverallNet:
					 createIncomeChartOverall(true);
					 break;
				 default:
					 createBudgetChartOverall(false);
					 break;
				 }
			 }
#pragma endregion
};
}
