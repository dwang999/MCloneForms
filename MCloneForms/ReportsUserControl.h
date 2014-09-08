#pragma once

#include <map>
#include "EntryController.h"
#include "BudgetController.h"
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
		enum class ActiveChart {OverallBar, OverallLine, MonthlyBar};
		ActiveChart activeChart;

		std::set<time_t>::reverse_iterator* iter;
		std::set<time_t>* entryDates;



	public:
		ReportsUserControl(void)
		{
			InitializeComponent();
		}

		void Init(EntryController* tempEntryController, BudgetController* tempBudgetController)
		{
			entryController = tempEntryController;
			budgetController = tempBudgetController;
			setEntryDates();
			iter = new std::set<time_t>::reverse_iterator(entryDates->rbegin());	
			monthBackward -> Enabled = false;		
			if (*iter != entryDates->rend())
			{
				time_t firstMonth = **iter;
				initBudgetChartMonth(false, firstMonth);
			}
			else
				monthForward -> Enabled = false;
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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			this->reportChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->monthForward = (gcnew System::Windows::Forms::Button());
			this->monthBackward = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->reportChart))->BeginInit();
			this->SuspendLayout();
			// 
			// reportChart
			// 
			chartArea4->AxisX->Title = L"Date";
			chartArea4->AxisY->Title = L"Amount";
			chartArea4->Name = L"ChartArea";
			this->reportChart->ChartAreas->Add(chartArea4);
			legend4->Name = L"Legend";
			this->reportChart->Legends->Add(legend4);
			this->reportChart->Location = System::Drawing::Point(0, 0);
			this->reportChart->Name = L"reportChart";
			this->reportChart->Size = System::Drawing::Size(788, 715);
			this->reportChart->TabIndex = 0;
			this->reportChart->Text = L"chart";
			this->reportChart->VisibleChanged += gcnew System::EventHandler(this, &ReportsUserControl::reportChart_VisibleChanged);
			// 
			// monthForward
			// 
			this->monthForward->Location = System::Drawing::Point(565, 13);
			this->monthForward->Name = L"monthForward";
			this->monthForward->Size = System::Drawing::Size(75, 23);
			this->monthForward->TabIndex = 1;
			this->monthForward->Text = L"-->";
			this->monthForward->UseVisualStyleBackColor = true;
			this->monthForward->Click += gcnew System::EventHandler(this, &ReportsUserControl::monthForward_Click);
			// 
			// monthBackward
			// 
			this->monthBackward->Location = System::Drawing::Point(102, 13);
			this->monthBackward->Name = L"monthBackward";
			this->monthBackward->Size = System::Drawing::Size(75, 23);
			this->monthBackward->TabIndex = 2;
			this->monthBackward->Text = L"<--";
			this->monthBackward->UseVisualStyleBackColor = true;
			this->monthBackward->Click += gcnew System::EventHandler(this, &ReportsUserControl::monthBackward_Click);
			// 
			// ReportsUserControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->monthBackward);
			this->Controls->Add(this->monthForward);
			this->Controls->Add(this->reportChart);
			this->Name = L"ReportsUserControl";
			this->Size = System::Drawing::Size(788, 715);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->reportChart))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void reportChart_VisibleChanged(System::Object^  sender, System::EventArgs^  e) {
				 DataVisualization::Charting::Chart^ chart = (DataVisualization::Charting::Chart^) sender;
				 if (chart->Visible == true)
				 {
					 switch (activeChart)
					 {
					 case ActiveChart::OverallBar:
						 initBudgetChartOverall(false);
						 break;
					 case ActiveChart::OverallLine:
						 initBudgetChartOverall(true);
						 break;
					 case ActiveChart::MonthlyBar:
						 if (*iter != entryDates->rend())
						 {
							 initBudgetChartMonth(false, **iter);
						 }
						 break;
					 default:
						 initBudgetChartOverall(false);
						 break;
					 }
				 }
			 }

			 System::Void monthForward_Click(System::Object^  sender, System::EventArgs^  e) {
				 std::advance(*iter, 1);
				 if (*iter != entryDates->rend())
				 {
					 time_t month = **iter;
					 initBudgetChartMonth(false, month);

					 monthBackward -> Enabled = true;
					 if(std::next(*iter, 1) == entryDates->rend())
						 monthForward -> Enabled = false;
				 }
			 }
			 System::Void monthBackward_Click(System::Object^  sender, System::EventArgs^  e) {
				 std::advance(*iter, -1);
				 time_t month = **iter;
				 initBudgetChartMonth(false, month);
				 monthForward -> Enabled = true;
				 if (*iter == entryDates->rbegin())
				 {
					 monthBackward -> Enabled = false;
				 }
			 }

#pragma region Private Methods
			 void initBudgetChartMonth(bool lineChart, time_t month)
			 {
				 toggleMonthChartButtonVisibility(true);
				 reportChart -> Series -> Clear();
				 reportChart -> Titles ->Clear();
				 activeChart = ActiveChart::MonthlyBar;
				 reportChart-> Series -> Add("Expenses");
				 reportChart-> Series -> Add("Budgets");
				 reportChart->Series["Budgets"] -> ToolTip = "#VALX: $#VAL";
				 reportChart->Series["Expenses"] -> ToolTip = "#VALX: $#VAL";
				 reportChart -> Titles -> Add(convertToSystemString(convertToString(month, "%b %Y")));

				 reportChart -> ChartAreas["ChartArea"] -> RecalculateAxesScale();
				 reportChart -> ChartAreas["ChartArea"] -> AxisY -> Title = "Amount";
				 reportChart -> ChartAreas["ChartArea"] -> AxisX -> Title = "Category";
				 reportChart -> ChartAreas["ChartArea"]->AxisY->LabelStyle->Format = "$ #";

				 // create a time_t that is month parameter + 1 month
				 tm *temp;
				 temp = localtime(&month);
				 temp -> tm_mon = (temp->tm_mon + 1);
				 time_t endOfMonth = mktime(temp);

				 std::vector<Entry> entries = entryController->getEntries();
				 std::map<std::string, float> categoryData = std::map<std::string, float>();
				 std::vector<Budget> budgets = budgetController->getBudgets();
				 std::map<std::string, float> budgetData = std::map<std::string, float>();

				 for (size_t i = 0; i < entries.size(); i++)
				 {
					 if (entries[i].date < endOfMonth && entries[i].date >= month)
					 {
						 if (categoryData.find(entries[i].category) == categoryData.end())
						 {
							 categoryData.insert(std::pair<std::string, float>(entries[i].category, entries[i].amount));
						 }
						 else
							 categoryData[entries[i].category] += entries[i].amount;
					 }
				 }


				 for (std::pair<std::string, float> category: categoryData)
				 {
					 budgetData.insert(std::pair<std::string, float>(category.first, 0));

					 // Find budget entry that has greatest date that is less than entry date
					 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
					 for (auto budget : budgets)
					 {
						 if (budget.category == category.first && budget.effectiveDate <= month && budget.effectiveDate > max.first)
							 max = std::pair<time_t, float>(budget.effectiveDate, budget.amount);
					 }

					 // If there is not budget for category then assign it to 0
					 if (max.first != 0)
						 budgetData[category.first] = max.second;

				 }


				 for (size_t i = 0; i < budgets.size(); i++)
				 {
					 if (budgetData.find(budgets[i].category) == budgetData.end())
					 {
						 std::string hi = budgets[i].category;
						 // Find budget entry that has greatest date that is less than entry date
						 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
						 for (auto budget : budgets)
						 {
							 if (budget.category == budgets[i].category && budget.effectiveDate <= month && budget.effectiveDate > max.first)
								 max = std::pair<time_t, float>(budget.effectiveDate, budget.amount);
						 }

						 budgetData.insert(std::pair<std::string, float>(budgets[i].category, max.second));
						 categoryData.insert(std::pair<std::string, float>(budgets[i].category, 0));
					 }		
				 }

				 for (std::pair<std::string, float> category: categoryData)
				 {
					 reportChart -> Series["Expenses"] -> Points -> AddXY(convertToSystemString(category.first), Math::Round(category.second, 2) + 0.00);
				 }
				 for (std::pair<std::string, float> budget: budgetData)
				 {
					 reportChart -> Series["Budgets"] -> Points -> AddXY(convertToSystemString(budget.first), Math::Round(budget.second, 2) + 0.00);
				 }
			 }

			 void initBudgetChartOverall(bool lineChart)
			 {
				 reportChart -> Series -> Clear();
				 reportChart -> Titles ->Clear();
				 if (lineChart)
				 {
					 activeChart = ActiveChart::OverallLine;
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

				 std::vector<Entry> entries = entryController->getEntries();
				 std::map<time_t, float> entryData = std::map<time_t, float>();
				 std::vector<Budget> budgets = budgetController->getBudgets();
				 std::map<time_t, float> budgetData = std::map<time_t, float>();

				 for (size_t i = 0; i < entries.size(); i++)
				 {
					 // Set day to the first
					 const time_t entryDate = entries[i].date;
					 tm *tm;
					 tm = localtime (&entryDate);
					 tm -> tm_mday = 1;
					 formatTMMonthDayYear(*tm);
					 time_t date;
					 date = mktime(tm);
					 if (entryData.find(date) == entryData.end())
					 {
						 entryData.insert(std::pair<time_t, float>(date, entries[i].amount));
					 }
					 else
						 entryData[date] += entries[i].amount;
				 }


				 for (std::pair<time_t, float> entry: entryData)
				 {
					 budgetData.insert(std::pair<time_t, float>(entry.first, 0));

					 for (auto category: entryController->getDistinctCategories())
					 {
						 // Find budget entry that has greatest date that is less than entry date
						 std::pair<time_t, float> max = std::pair<time_t, float>(0, 0);
						 for (auto budget : budgets)
						 {
							 if (budget.category == category && budget.effectiveDate <= entry.first && budget.effectiveDate > max.first)
								 max = std::pair<time_t, float>(budget.effectiveDate, budget.amount);
						 }

						 // If there is not budget for category then assign it to 0
						 if (max.first == 0)
							 max = std::pair<time_t, float>(entry.first, 0);

						 budgetData[entry.first] += max.second;
					 }
				 }

				 if (lineChart)
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
				 if (!entryDates)
					 entryDates = new std::set<time_t>();
				 std::vector<Entry> entries = entryController->getEntries();
				 for (size_t i = 0; i < entries.size(); i++)
				 {
					 // Set day to the first
					 const time_t entryDate = entries[i].date;
					 tm *tm;
					 tm = localtime (&entryDate);
					 tm -> tm_mday = 1;
					 formatTMMonthDayYear(*tm);
					 time_t date;
					 date = mktime(tm);
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

			 void toggleMonthChartButtonVisibility(bool visible)
			 {
				 monthForward -> Visible = visible;
				 monthBackward -> Visible = visible;
			 }
#pragma endregion
	};
}
