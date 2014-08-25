#pragma once

#include <algorithm>
#include <sstream> 
#include <regex>
#include "EntryController.h"
#include "String.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace MCloneForms {

	/// <summary>
	/// Summary for EntriesUserControl
	/// </summary>
	public ref class EntriesUserControl : public System::Windows::Forms::UserControl
	{
	private:
		EntryController *entryController;
		const int DIVIDER_HEIGHT;
		char * const profileName;

	public:
		EntriesUserControl(void): profileName("Test"), entryController(nullptr), DIVIDER_HEIGHT(4)
		{
			InitializeComponent();
			// Initialize Form Controls			
			dateTimePicker -> Format = DateTimePickerFormat::Custom;
			dateTimePicker -> CustomFormat = "ddd, MMMM dd, yyyy";


			// Initiallize member variables			
			entryController = new EntryController(profileName);
			if (entryController -> backupExists())
			{
				if (showYesNoMessage("MCloneForm Load Backup", "MCloneForm did not close properly. Do you wish to load data from previous session?"))
					entryController -> loadBackup();
				else
				{
					entryController -> load();
					entryController -> deleteBackup();
				}
			}
			else
			{
				entryController -> load();
			}
			entryController -> sortByDate(true);

			// Output details of entries
			std::vector<Entry> entries = entryController -> getEntries();
			for (size_t i = 0; i < entries.size(); i ++)
			{
				int newRowIndex = this->dataGridView->Rows->Add();
				setDataGridRowColumns(this->dataGridView->Rows[newRowIndex], convertToString(entries[i].date), entries[i].category, entries[i].subCategory, entries[i].description,
					entries[i].amount);

				if (i < entries.size() - 1)
				{
					const time_t temp = entries[i].date;
					const time_t temp2 = entries[i + 1].date;
					// Seperate the entries by month and year
					if (localtime(&temp) -> tm_mon != localtime(&temp2) -> tm_mon || localtime(&temp) -> tm_year != localtime(&temp2) -> tm_year) 
					{
						dataGridView->Rows[newRowIndex] ->DividerHeight = DIVIDER_HEIGHT;
					}
				}
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EntriesUserControl()
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
		}
	private: 
		System::Windows::Forms::DataGridView^  dataGridView;
		System::Windows::Forms::Button^  addButton;
		System::Windows::Forms::Button^  editButton;
		System::Windows::Forms::TextBox^  descriptionAdd;
		System::Windows::Forms::TextBox^  amountAdd;
		System::Windows::Forms::TextBox^  subCategoryAdd;
		System::Windows::Forms::TextBox^  categoryAdd;
		System::Windows::Forms::DateTimePicker^  dateTimePicker;
		System::Windows::Forms::Button^  saveButton;
		System::Windows::Forms::DataGridViewTextBoxColumn^  Date;
		System::Windows::Forms::DataGridViewTextBoxColumn^  Description;
		System::Windows::Forms::DataGridViewTextBoxColumn^  Category;
		System::Windows::Forms::DataGridViewTextBoxColumn^  SubCategory;
		System::Windows::Forms::DataGridViewTextBoxColumn^  Amount;
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
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->Date = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Description = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Category = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->SubCategory = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Amount = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->editButton = (gcnew System::Windows::Forms::Button());
			this->addButton = (gcnew System::Windows::Forms::Button());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->dateTimePicker = (gcnew System::Windows::Forms::DateTimePicker());
			this->categoryAdd = (gcnew System::Windows::Forms::TextBox());
			this->descriptionAdd = (gcnew System::Windows::Forms::TextBox());
			this->amountAdd = (gcnew System::Windows::Forms::TextBox());
			this->subCategoryAdd = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView
			// 
			this->dataGridView->AllowUserToAddRows = false;
			this->dataGridView->AllowUserToDeleteRows = false;
			this->dataGridView->AllowUserToOrderColumns = true;
			this->dataGridView->AllowUserToResizeRows = false;
			this->dataGridView->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView->BackgroundColor = System::Drawing::SystemColors::Window;
			this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->Date, this->Description, 
				this->Category, this->SubCategory, this->Amount});
			this->dataGridView->Location = System::Drawing::Point(3, 28);
			this->dataGridView->Name = L"dataGridView";
			this->dataGridView->ReadOnly = true;
			this->dataGridView->RowHeadersVisible = false;
			this->dataGridView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGridView->Size = System::Drawing::Size(780, 684);
			this->dataGridView->TabIndex = 1;
			this->dataGridView->TabStop = false;
			this->dataGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &EntriesUserControl::dataGridView_CellContentClick);
			this->dataGridView->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &EntriesUserControl::dataGridView_CellValueChanged);
			this->dataGridView->ColumnHeaderMouseClick += gcnew System::Windows::Forms::DataGridViewCellMouseEventHandler(this, &EntriesUserControl::dataGridView_ColumnHeaderMouseClick);
			// 
			// Date
			// 
			this->Date->FillWeight = 99.1972F;
			this->Date->HeaderText = L"Date";
			this->Date->Name = L"Date";
			this->Date->ReadOnly = true;
			// 
			// Description
			// 
			this->Description->FillWeight = 200;
			this->Description->HeaderText = L"Description";
			this->Description->Name = L"Description";
			this->Description->ReadOnly = true;
			// 
			// Category
			// 
			this->Category->FillWeight = 99.40995F;
			this->Category->HeaderText = L"Category";
			this->Category->Name = L"Category";
			this->Category->ReadOnly = true;
			// 
			// SubCategory
			// 
			this->SubCategory->FillWeight = 101.0354F;
			this->SubCategory->HeaderText = L"SubCategory";
			this->SubCategory->Name = L"SubCategory";
			this->SubCategory->ReadOnly = true;
			// 
			// Amount
			// 
			this->Amount->FillWeight = 100.3683F;
			this->Amount->HeaderText = L"Amount";
			this->Amount->Name = L"Amount";
			this->Amount->ReadOnly = true;
			// 
			// editButton
			// 
			this->editButton->Location = System::Drawing::Point(547, -1);
			this->editButton->Name = L"editButton";
			this->editButton->Size = System::Drawing::Size(75, 23);
			this->editButton->TabIndex = 3;
			this->editButton->TabStop = false;
			this->editButton->Text = L"Edit";
			this->editButton->UseVisualStyleBackColor = true;
			this->editButton->Click += gcnew System::EventHandler(this, &EntriesUserControl::editButton_Click);
			// 
			// addButton
			// 
			this->addButton->Location = System::Drawing::Point(628, -1);
			this->addButton->Name = L"addButton";
			this->addButton->Size = System::Drawing::Size(75, 23);
			this->addButton->TabIndex = 6;
			this->addButton->TabStop = false;
			this->addButton->Text = L"Add";
			this->addButton->UseVisualStyleBackColor = true;
			this->addButton->Click += gcnew System::EventHandler(this, &EntriesUserControl::addButton_Click);
			// 
			// saveButton
			// 
			this->saveButton->Location = System::Drawing::Point(709, -1);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(75, 23);
			this->saveButton->TabIndex = 7;
			this->saveButton->TabStop = false;
			this->saveButton->Text = L"Save";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &EntriesUserControl::saveButton_Click);
			// 
			// dateTimePicker
			// 
			this->dateTimePicker->Location = System::Drawing::Point(5, 28);
			this->dateTimePicker->Name = L"dateTimePicker";
			this->dateTimePicker->Size = System::Drawing::Size(190, 20);
			this->dateTimePicker->TabIndex = 8;
			this->dateTimePicker->Visible = false;
			// 
			// categoryAdd
			// 
			this->categoryAdd->Location = System::Drawing::Point(201, 28);
			this->categoryAdd->Name = L"categoryAdd";
			this->categoryAdd->Size = System::Drawing::Size(190, 20);
			this->categoryAdd->TabIndex = 9;
			this->categoryAdd->Tag = L"";
			this->categoryAdd->Visible = false;
			// 
			// descriptionAdd
			// 
			this->descriptionAdd->Location = System::Drawing::Point(4, 54);
			this->descriptionAdd->Multiline = true;
			this->descriptionAdd->Name = L"descriptionAdd";
			this->descriptionAdd->Size = System::Drawing::Size(779, 60);
			this->descriptionAdd->TabIndex = 12;
			this->descriptionAdd->Tag = L"";
			this->descriptionAdd->Visible = false;
			// 
			// amountAdd
			// 
			this->amountAdd->Location = System::Drawing::Point(593, 28);
			this->amountAdd->Name = L"amountAdd";
			this->amountAdd->Size = System::Drawing::Size(190, 20);
			this->amountAdd->TabIndex = 11;
			this->amountAdd->Tag = L"";
			this->amountAdd->Visible = false;
			// 
			// subCategoryAdd
			// 
			this->subCategoryAdd->Location = System::Drawing::Point(397, 28);
			this->subCategoryAdd->Name = L"subCategoryAdd";
			this->subCategoryAdd->Size = System::Drawing::Size(190, 20);
			this->subCategoryAdd->TabIndex = 10;
			this->subCategoryAdd->Tag = L"";
			this->subCategoryAdd->Visible = false;
			// 
			// EntriesUserControl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->dateTimePicker);
			this->Controls->Add(this->categoryAdd);
			this->Controls->Add(this->descriptionAdd);
			this->Controls->Add(this->amountAdd);
			this->Controls->Add(this->subCategoryAdd);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->addButton);
			this->Controls->Add(this->editButton);
			this->Controls->Add(this->dataGridView);
			this->Name = L"EntriesUserControl";
			this->Size = System::Drawing::Size(788, 715);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
#pragma region Events
		// private events
	private: System::Void addButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 System::Windows::Forms::Button^ addButton = (System::Windows::Forms::Button^) sender;
				 if (addButton -> Text == "Add")
				 {
					 toggleAddTextBoxes();
					 changeDisplayAddButton(0, 100, -100);
					 addButton -> Text = "OK";
				 }
				 else
				 {

					 // Validate Input
					 if(validateInputsAdd(categoryAdd -> Text, amountAdd -> Text))
					 {
						 float amount;
						 amount = stof(convertSystemToSTDString(amountAdd -> Text));
						 // Add row to data grid view
						 int newRowIndex = dataGridView -> Rows -> Add();
						 setDataGridRowColumns(dataGridView -> Rows[newRowIndex], dateTimePicker -> Value.ToString("MMM dd, yyyy"), categoryAdd -> Text, subCategoryAdd -> Text, descriptionAdd -> Text, amount);

						 tm tm = {0};
						 convertStringToTM(convertSystemToSTDString(dateTimePicker -> Value.ToString("MM/dd/yyyy")), tm);
						 // Auto save Entry Controller
						 entryController -> add(tm, convertSystemToSTDString(categoryAdd -> Text), 
							 convertSystemToSTDString(subCategoryAdd -> Text), convertSystemToSTDString(descriptionAdd -> Text), amount);
						 entryController->autoSave();

						 changeDisplayAddButton(0, -100, 100);
						 toggleAddTextBoxes();	
						 resetAddTextBoxes();
						 sortByDate();
						 addButton -> Text = "Add";
					 }

				 }
			 }
	private: System::Void editButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (dataGridView -> ReadOnly) //Enter edit mode
				 {
					 editButton -> Text = "Stop Edit";
					 DataGridViewButtonColumn^ column = gcnew DataGridViewButtonColumn();
					 column -> Name = "Remove";
					 column -> UseColumnTextForButtonValue = true;
					 column -> HeaderText = "";
					 column -> Text = "X";
					 column -> FillWeight = 25;
					 dataGridView-> Columns -> Add(column);
					 dataGridView-> ReadOnly = false;
				 }
				 else //exit edit mode
				 {
					 dataGridView -> CancelEdit();
					 editButton -> Text = "Edit";
					 dataGridView->Columns -> Remove("Remove");
					 dataGridView->ReadOnly = true;
				 }
			 }

	private: System::Void saveButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 entryController -> save();
			 }

	private: System::Void dataGridView_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
				 if (!dataGridView ->ReadOnly)
				 {
					 System::String^ cellValue;
					 if (dataGridView -> Rows[e->RowIndex] -> Cells[e->ColumnIndex] -> Value != nullptr)
						 cellValue = dataGridView -> Rows[e->RowIndex] -> Cells[e->ColumnIndex] -> Value -> ToString();

					 std::string columnName = convertSystemToSTDString(dataGridView -> Columns[e -> ColumnIndex] -> Name -> ToString());

					 if (columnName == "Date")
					 {		
						 DateTime datetime;
						 if (!System::String::IsNullOrWhiteSpace(cellValue) && DateTime::TryParse(cellValue, datetime))
						 {
							 std::string dateString = convertSystemToSTDString(datetime.ToString("MM/dd/yyyy"));
							 tm tm = {0};
							 convertStringToTM(dateString, tm);
							 entryController->modifyDate(e->RowIndex, tm);

							 // Format data cell
							 System::String^ systemDateString = datetime.ToString("MMM dd, yyyy");
							 dataGridView -> Rows[e->RowIndex] -> Cells[e->ColumnIndex] -> Value = systemDateString;
						 }
						 else
						 {
							 char buff[20];
							 time_t tt = entryController->getDate(e->RowIndex);
							 strftime(buff, 20,"%b %d, %Y", localtime(&tt));
							 dataGridView -> Rows[e->RowIndex] -> Cells[e->ColumnIndex] -> Value = convertToSystemString(buff); 
							 showErrorMessage("Edit Error", "Date value is not a valid Date");
						 }
					 }
					 else if (columnName == "Category")
					 {
						 if (!System::String::IsNullOrWhiteSpace(cellValue))
							 entryController->modifyCategory(e->RowIndex, convertSystemToSTDString(cellValue));
						 else
						 {
							 dataGridView -> Rows[e->RowIndex] -> Cells[e->ColumnIndex] -> Value = convertToSystemString(entryController->getCategory(e->RowIndex)); 
							 showErrorMessage("Edit Error", "Category must not be an empty string");
						 }
					 }
					 else if (columnName == "SubCategory")
					 {
						 entryController->modifySubCategory(e->RowIndex, convertSystemToSTDString(cellValue));
					 }
					 else if (columnName  == "Description")
					 {
						 entryController->modifyDescription(e->RowIndex, convertSystemToSTDString(cellValue));
					 }
					 else if (columnName  == "Amount")
					 {
						 if (!System::String::IsNullOrWhiteSpace(cellValue) && System::Text::RegularExpressions::Regex::IsMatch(cellValue, "^[$]?\\s?[0-9]{1}[0-9]*([.][0-9]{2})?$"))
						 {
							 cellValue = cellValue -> Replace("$", "");
							 cellValue = cellValue -> Replace(" ", "");
							 float amount = stof(convertSystemToSTDString(cellValue));
							 entryController->modifyAmount(e->RowIndex, amount);
							 // Format data cell
							 dataGridView -> Rows[e->RowIndex] -> Cells[e->ColumnIndex] -> Value = convertToSystemString(convertToCurrencyString(amount));
						 }
						 else
						 {
							 dataGridView -> Rows[e->RowIndex] -> Cells[e->ColumnIndex] -> Value = convertToSystemString(convertToCurrencyString(entryController->getAmount(e->RowIndex))); 
							 showErrorMessage("Edit Error", "Amount must be a non-empty all numeral value");
						 }
					 }
					 else
					 {

						 throw std::runtime_error("MainWindow::dataGridView_CellValueChanged : Column header \"" + columnName + "\" not found");
					 }

					 entryController -> autoSave();
				 }
			 }

	private: System::Void dataGridView_ColumnHeaderMouseClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellMouseEventArgs^  e) {
				 std::string columnName = convertSystemToSTDString(dataGridView -> Columns[e -> ColumnIndex] -> Name -> ToString());

				 bool desc;
				 if(dataGridView -> SortOrder == Windows::Forms::SortOrder::Descending)
					 desc = true;
				 else
					 desc = false;

				 if (columnName == "Date")
				 {
					 entryController -> sortByDate(desc);
				 }
				 else if (columnName == "Category")
				 {
					 entryController -> sortByCategory(desc);
				 }
				 else if (columnName == "SubCategory")
				 {
					 entryController -> sortBySubCategory(desc);
				 }
				 else if (columnName  == "Description")
				 {
					 entryController -> sortByDescription(desc);
				 }
				 else if (columnName  == "Amount")
				 {
					 entryController -> sortByAmount(desc);
				 }
				 else
				 {
					 throw std::runtime_error("MainWindow::dataGridView_ColumnHeaderMouseClick : Column header \"" + columnName + "\" not found");
				 }
				 resetDividers(columnName);
			 }
	private: System::Void dataGridView_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
				 std::string columnName = convertSystemToSTDString(dataGridView -> Columns[e -> ColumnIndex] -> Name -> ToString()); 
				 if (columnName == "Remove")
				 {
					 dataGridView -> Rows -> RemoveAt(e -> RowIndex);
					 entryController -> remove(e->RowIndex);
					 entryController -> autoSave();
				 }
			 }



			 // private Methods
#pragma endregion
#pragma region Private Methods
	private:
		bool validateInputsAdd(System::String^ category, System::String^ amount)
		{
			int errors = 0;

			std::string amountSTD = convertSystemToSTDString(amount);
			if (!std::regex_match(amountSTD, std::regex("^[0-9]+")) || amountSTD.empty())
			{
				errors++; 
				showErrorMessage("Add Error", "Amount must be a non-empty all numeral value");
			}


			if (convertSystemToSTDString(category).empty())
			{
				errors++; 
				showErrorMessage("Add Error", "Category must not be empty");
			}

			if (errors > 0)
				return false;
			else
				return true;
		}

		void changeDisplayAddButton(int locationX, int locationY, int height)
		{
			dataGridView -> Location = System::Drawing::Point(dataGridView -> Location.X + locationX, dataGridView -> Location.Y + locationY); 
			dataGridView -> Height = dataGridView -> Height + height; 
		}

		void toggleAddTextBoxes()
		{
			dateTimePicker -> Visible = !(dateTimePicker -> Visible);
			categoryAdd -> Visible = !(categoryAdd -> Visible);
			subCategoryAdd -> Visible = !(subCategoryAdd -> Visible);
			amountAdd -> Visible = !(amountAdd -> Visible);
			descriptionAdd -> Visible = !(descriptionAdd -> Visible);
		}
		void resetAddTextBoxes()
		{
			dateTimePicker -> Value = System::DateTime::Now;
			categoryAdd -> Text = "";
			subCategoryAdd -> Text = "";
			amountAdd -> Text = "";
			descriptionAdd -> Text = "";
		}
		void sortByDate()
		{
			dataGridView -> Sort(dataGridView->Columns[0], System::ComponentModel::ListSortDirection::Descending);
			resetDividers("Date");
		}

		void setDataGridRowColumns(DataGridViewRow^ row, std::string date, std::string category, std::string subCategory, std::string description, float amount)
		{
			row -> Cells["Date"] -> Value = convertToSystemString(date);
			row -> Cells["Category"] -> Value = convertToSystemString(category);
			row -> Cells["SubCategory"] -> Value = convertToSystemString(subCategory);
			row -> Cells["Description"] -> Value = convertToSystemString(description);
			row -> Cells["Amount"] -> Value = convertToSystemString(convertToCurrencyString(amount));
		}

		void setDataGridRowColumns(DataGridViewRow^ row, System::String^ date, System::String^ category, System::String^ subCategory, System::String^ description, float amount)
		{
			row -> Cells["Date"] -> Value = date;
			row -> Cells["Category"] -> Value = category;
			row -> Cells["SubCategory"] -> Value = subCategory;
			row -> Cells["Description"] -> Value = description;
			row -> Cells["Amount"] -> Value = convertToSystemString(convertToCurrencyString(amount));
		}

		void showErrorMessage(System::String^ title, System::String^ text)
		{
			Windows::Forms::MessageBox::Show(text, title, MessageBoxButtons::OK, MessageBoxIcon::Error);
		}

		bool showYesNoMessage(System::String^ title, System::String^ text)
		{
			System::Windows::Forms::DialogResult dialogResult =  Windows::Forms::MessageBox::Show(text, title, MessageBoxButtons::YesNo, MessageBoxIcon::Exclamation);
			if(dialogResult == System::Windows::Forms::DialogResult::Yes)
				return true;
			else
				return false;
		}

		void resetDividers(std::string columnName)
		{
			for (int i = 0; i < dataGridView -> RowCount; i++)
			{
				dataGridView->Rows[i] -> DividerHeight = 1;
				if (i < dataGridView -> RowCount - 1)
				{

					if (columnName == "Date")
					{
						System::DateTime temp = System::DateTime::Parse(dataGridView->Rows[i] -> Cells["Date"] -> Value -> ToString());
						System::DateTime temp2 = System::DateTime::Parse(dataGridView->Rows[i + 1] -> Cells["Date"] -> Value -> ToString());
						if (temp.Month != temp2.Month || temp.Year != temp2.Year) 
						{
							dataGridView->Rows[i] -> DividerHeight = DIVIDER_HEIGHT;
						}
					}
					else if (columnName == "Category")
					{
						if (!dataGridView->Rows[i] -> Cells["Category"] -> Value -> ToString() -> Equals(dataGridView->Rows[i + 1] -> Cells["Category"] -> Value -> ToString())) 
						{
							dataGridView->Rows[i] -> DividerHeight = DIVIDER_HEIGHT;
						}
					}
					else if (columnName == "SubCategory")
					{
						if (!dataGridView->Rows[i] -> Cells["SubCategory"] -> Value -> ToString() -> Equals(dataGridView->Rows[i + 1] -> Cells["SubCategory"] -> Value -> ToString())) 
						{
							dataGridView->Rows[i] -> DividerHeight = DIVIDER_HEIGHT;
						}
					}
					else if (columnName  == "Description")
					{
						if (!dataGridView->Rows[i] -> Cells["Description"] -> Value -> ToString() -> Equals(dataGridView->Rows[i + 1] -> Cells["Description"] -> Value -> ToString())) 
						{
							dataGridView->Rows[i] -> DividerHeight = DIVIDER_HEIGHT;
						}
					}
					else if (columnName  == "Amount")
					{
						System::String^ temp = dataGridView->Rows[i] -> Cells["Amount"] -> Value -> ToString();
						System::String^ temp2 = dataGridView->Rows[i + 1] -> Cells["Amount"] -> Value -> ToString();
						temp = temp -> Replace("$", "");
						temp = temp -> Replace(" ", "");
						temp2 = temp2 -> Replace("$", "");
						temp2 = temp2 -> Replace(" ", "");
						if (!temp -> Equals(temp2))
						{
							dataGridView->Rows[i] -> DividerHeight = 3;
						}
					}
					else
					{
						throw std::runtime_error("MainWindow::resetDividers : Column header \"" + columnName + "\" not found");
					}
				}

			}

		}
#pragma endregion
		
#pragma region Public Methods
		// public methods
	public: bool closeUserControl()
			{
				if (entryController -> backupExists())
				{
					if(showYesNoMessage("Entries Not Saved!","Entries for profile " + convertToSystemString(entryController -> getProfileName()) + " have not been saved. Do you wish to save changes and exit?"))
					{
						entryController -> save();
						return true;
					}
					else
					{
						if(showYesNoMessage("Continue Exit","Do you want to discared changes for " + convertToSystemString(entryController -> getProfileName()) + "'s Entries and exit the window?"))
						{
							entryController -> deleteBackup();
							return true;
						}
						else
							return false;
					}
				}
				else 
					return true;
			}
#pragma endregion
	};
}
