#pragma once

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
	public:
		ReportsUserControl(void)
		{
			InitializeComponent();
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
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  reportChart;
	protected: 

	protected: 

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->reportChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->reportChart))->BeginInit();
			this->SuspendLayout();
			// 
			// reportChart
			// 
			chartArea->Name = L"ChartArea";
			this->reportChart->ChartAreas->Add(chartArea);
			legend->Name = L"Legend";
			this->reportChart->Legends->Add(legend);
			this->reportChart->Location = System::Drawing::Point(0, 0);
			this->reportChart->Name = L"reportChart";
			series->ChartArea = L"ChartArea";
			series->Legend = L"Legend";
			series->Name = L"Series";
			this->reportChart->Series->Add(series);
			this->reportChart->Size = System::Drawing::Size(788, 715);
			this->reportChart->TabIndex = 0;
			this->reportChart->Text = L"chart";
			// 
			// ReportsUserControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->reportChart);
			this->Name = L"ReportsUserControl";
			this->Size = System::Drawing::Size(788, 715);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->reportChart))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
