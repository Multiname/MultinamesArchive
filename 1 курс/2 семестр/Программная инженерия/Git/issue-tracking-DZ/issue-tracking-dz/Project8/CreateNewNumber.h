#pragma once
#include "NumbersMenu.h"
#include "EditRoomList.h"
#include <msclr\marshal_cppstd.h>
#include "InputHandler.h"
#include "NumberImageStorage.h"

namespace Project8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class CreateNewNumber : public System::Windows::Forms::Form
	{
	public:
		CreateNewNumber(NumbersMenu^ parent)
		{
			m_parent = parent;

			InitializeComponent();
		}

	protected:
		~CreateNewNumber()
		{
			if (components)
			{
				delete components;
			}
		}

	private: NumbersMenu^ m_parent;

	private: System::Windows::Forms::Label^ NumberLabel;
	private: System::Windows::Forms::Label^ PriceLabel;
	private: System::Windows::Forms::Label^ WifiLabel;
	private: System::Windows::Forms::Label^ TvLabel;
	private: System::Windows::Forms::Label^ SleepingPlaceLabel;
	private: System::Windows::Forms::Label^ SquareLabel;
	private: System::Windows::Forms::NumericUpDown^ NumberNumericUpDown;
	private: System::Windows::Forms::TextBox^ PriceTextBox;
	private: System::Windows::Forms::RadioButton^ WifiYesRadioButton;
	private: System::Windows::Forms::RadioButton^ WifiNoRadioButton;
	private: System::Windows::Forms::RadioButton^ TvYesRadioButton;
	private: System::Windows::Forms::RadioButton^ TvNoRadioButton;
	private: System::Windows::Forms::TextBox^ SleepingPlaceTextBox;
	private: System::Windows::Forms::TextBox^ SquareTextBox;
	private: System::Windows::Forms::Button^ CreateButton;
	private: System::Windows::Forms::Panel^ WifiPanel;
	private: System::Windows::Forms::Panel^ TvPanel;
	private: System::Windows::Forms::Label^ ImagePathLabel;
	private: System::Windows::Forms::TextBox^ ImagePathTextBox;
	private: System::Windows::Forms::Button^ ImagePathButton;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources =
				(gcnew System::ComponentModel::ComponentResourceManager(CreateNewNumber::typeid));
			this->NumberLabel = (gcnew System::Windows::Forms::Label());
			this->PriceLabel = (gcnew System::Windows::Forms::Label());
			this->WifiLabel = (gcnew System::Windows::Forms::Label());
			this->TvLabel = (gcnew System::Windows::Forms::Label());
			this->SleepingPlaceLabel = (gcnew System::Windows::Forms::Label());
			this->SquareLabel = (gcnew System::Windows::Forms::Label());
			this->NumberNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->PriceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->WifiYesRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->WifiNoRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->TvYesRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->TvNoRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->SleepingPlaceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SquareTextBox = (gcnew System::Windows::Forms::TextBox());
			this->CreateButton = (gcnew System::Windows::Forms::Button());
			this->WifiPanel = (gcnew System::Windows::Forms::Panel());
			this->TvPanel = (gcnew System::Windows::Forms::Panel());
			this->ImagePathLabel = (gcnew System::Windows::Forms::Label());
			this->ImagePathTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ImagePathButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumberNumericUpDown))->BeginInit();
			this->WifiPanel->SuspendLayout();
			this->TvPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// NumberLabel
			// 
			this->NumberLabel->AutoSize = true;
			this->NumberLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->NumberLabel->Location = System::Drawing::Point(12, 14);
			this->NumberLabel->Name = L"NumberLabel";
			this->NumberLabel->Size = System::Drawing::Size(41, 13);
			this->NumberLabel->TabIndex = 0;
			this->NumberLabel->Text = L"Номер";
			// 
			// PriceLabel
			// 
			this->PriceLabel->AutoSize = true;
			this->PriceLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->PriceLabel->Location = System::Drawing::Point(12, 41);
			this->PriceLabel->Name = L"PriceLabel";
			this->PriceLabel->Size = System::Drawing::Size(33, 13);
			this->PriceLabel->TabIndex = 1;
			this->PriceLabel->Text = L"Цена";
			// 
			// WifiLabel
			// 
			this->WifiLabel->AutoSize = true;
			this->WifiLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->WifiLabel->Location = System::Drawing::Point(12, 66);
			this->WifiLabel->Name = L"WifiLabel";
			this->WifiLabel->Size = System::Drawing::Size(31, 13);
			this->WifiLabel->TabIndex = 2;
			this->WifiLabel->Text = L"Wi-Fi";
			// 
			// TvLabel
			// 
			this->TvLabel->AutoSize = true;
			this->TvLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->TvLabel->Location = System::Drawing::Point(12, 92);
			this->TvLabel->Name = L"TvLabel";
			this->TvLabel->Size = System::Drawing::Size(21, 13);
			this->TvLabel->TabIndex = 3;
			this->TvLabel->Text = L"TV";
			// 
			// SleepingPlaceLabel
			// 
			this->SleepingPlaceLabel->AutoSize = true;
			this->SleepingPlaceLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->SleepingPlaceLabel->Location = System::Drawing::Point(12, 119);
			this->SleepingPlaceLabel->Name = L"SleepingPlaceLabel";
			this->SleepingPlaceLabel->Size = System::Drawing::Size(92, 13);
			this->SleepingPlaceLabel->TabIndex = 4;
			this->SleepingPlaceLabel->Text = L"Спальные места";
			// 
			// SquareLabel
			// 
			this->SquareLabel->AutoSize = true;
			this->SquareLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->SquareLabel->Location = System::Drawing::Point(12, 145);
			this->SquareLabel->Name = L"SquareLabel";
			this->SquareLabel->Size = System::Drawing::Size(54, 13);
			this->SquareLabel->TabIndex = 5;
			this->SquareLabel->Text = L"Площадь";
			// 
			// NumberNumericUpDown
			// 
			this->NumberNumericUpDown->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->NumberNumericUpDown->ForeColor = System::Drawing::Color::Navy;
			this->NumberNumericUpDown->Location = System::Drawing::Point(110, 12);
			this->NumberNumericUpDown->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 65535, 0, 0, 0 });
			this->NumberNumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->NumberNumericUpDown->Name = L"NumberNumericUpDown";
			this->NumberNumericUpDown->Size = System::Drawing::Size(49, 20);
			this->NumberNumericUpDown->TabIndex = 0;
			this->NumberNumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// PriceTextBox
			// 
			this->PriceTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->PriceTextBox->ForeColor = System::Drawing::Color::Navy;
			this->PriceTextBox->Location = System::Drawing::Point(110, 38);
			this->PriceTextBox->MaxLength = 10;
			this->PriceTextBox->Name = L"PriceTextBox";
			this->PriceTextBox->Size = System::Drawing::Size(99, 20);
			this->PriceTextBox->TabIndex = 1;
			// 
			// WifiYesRadioButton
			// 
			this->WifiYesRadioButton->AutoSize = true;
			this->WifiYesRadioButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->WifiYesRadioButton->Location = System::Drawing::Point(0, 0);
			this->WifiYesRadioButton->Name = L"WifiYesRadioButton";
			this->WifiYesRadioButton->Size = System::Drawing::Size(49, 17);
			this->WifiYesRadioButton->TabIndex = 2;
			this->WifiYesRadioButton->Text = L"Есть";
			this->WifiYesRadioButton->UseVisualStyleBackColor = true;
			// 
			// WifiNoRadioButton
			// 
			this->WifiNoRadioButton->AutoSize = true;
			this->WifiNoRadioButton->Checked = true;
			this->WifiNoRadioButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->WifiNoRadioButton->Location = System::Drawing::Point(55, 0);
			this->WifiNoRadioButton->Name = L"WifiNoRadioButton";
			this->WifiNoRadioButton->Size = System::Drawing::Size(44, 17);
			this->WifiNoRadioButton->TabIndex = 3;
			this->WifiNoRadioButton->TabStop = true;
			this->WifiNoRadioButton->Text = L"Нет";
			this->WifiNoRadioButton->UseVisualStyleBackColor = true;
			// 
			// TvYesRadioButton
			// 
			this->TvYesRadioButton->AutoSize = true;
			this->TvYesRadioButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->TvYesRadioButton->Location = System::Drawing::Point(0, 0);
			this->TvYesRadioButton->Name = L"TvYesRadioButton";
			this->TvYesRadioButton->Size = System::Drawing::Size(49, 17);
			this->TvYesRadioButton->TabIndex = 4;
			this->TvYesRadioButton->Text = L"Есть";
			this->TvYesRadioButton->UseVisualStyleBackColor = true;
			// 
			// TvNoRadioButton
			// 
			this->TvNoRadioButton->AutoSize = true;
			this->TvNoRadioButton->Checked = true;
			this->TvNoRadioButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->TvNoRadioButton->Location = System::Drawing::Point(55, 0);
			this->TvNoRadioButton->Name = L"TvNoRadioButton";
			this->TvNoRadioButton->Size = System::Drawing::Size(44, 17);
			this->TvNoRadioButton->TabIndex = 5;
			this->TvNoRadioButton->TabStop = true;
			this->TvNoRadioButton->Text = L"Нет";
			this->TvNoRadioButton->UseVisualStyleBackColor = true;
			// 
			// SleepingPlaceTextBox
			// 
			this->SleepingPlaceTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->SleepingPlaceTextBox->ForeColor = System::Drawing::Color::Navy;
			this->SleepingPlaceTextBox->Location = System::Drawing::Point(110, 116);
			this->SleepingPlaceTextBox->MaxLength = 50;
			this->SleepingPlaceTextBox->Name = L"SleepingPlaceTextBox";
			this->SleepingPlaceTextBox->Size = System::Drawing::Size(194, 20);
			this->SleepingPlaceTextBox->TabIndex = 6;
			// 
			// SquareTextBox
			// 
			this->SquareTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->SquareTextBox->ForeColor = System::Drawing::Color::Navy;
			this->SquareTextBox->Location = System::Drawing::Point(110, 142);
			this->SquareTextBox->MaxLength = 3;
			this->SquareTextBox->Name = L"SquareTextBox";
			this->SquareTextBox->Size = System::Drawing::Size(49, 20);
			this->SquareTextBox->TabIndex = 7;
			// 
			// CreateButton
			// 
			this->CreateButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->CreateButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->CreateButton->Location = System::Drawing::Point(110, 194);
			this->CreateButton->Name = L"CreateButton";
			this->CreateButton->Size = System::Drawing::Size(99, 23);
			this->CreateButton->TabIndex = 9;
			this->CreateButton->Text = L"Создать";
			this->CreateButton->UseVisualStyleBackColor = false;
			this->CreateButton->Click += gcnew System::EventHandler(this, &CreateNewNumber::CreateButton_Click);
			// 
			// WifiPanel
			// 
			this->WifiPanel->Controls->Add(this->WifiYesRadioButton);
			this->WifiPanel->Controls->Add(this->WifiNoRadioButton);
			this->WifiPanel->Location = System::Drawing::Point(110, 64);
			this->WifiPanel->Name = L"WifiPanel";
			this->WifiPanel->Size = System::Drawing::Size(99, 20);
			this->WifiPanel->TabIndex = 2;
			this->WifiPanel->TabStop = true;
			// 
			// TvPanel
			// 
			this->TvPanel->Controls->Add(this->TvYesRadioButton);
			this->TvPanel->Controls->Add(this->TvNoRadioButton);
			this->TvPanel->Location = System::Drawing::Point(110, 90);
			this->TvPanel->Name = L"TvPanel";
			this->TvPanel->Size = System::Drawing::Size(100, 20);
			this->TvPanel->TabIndex = 3;
			this->TvPanel->TabStop = true;
			// 
			// ImagePathLabel
			// 
			this->ImagePathLabel->AutoSize = true;
			this->ImagePathLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ImagePathLabel->Location = System::Drawing::Point(12, 171);
			this->ImagePathLabel->Name = L"ImagePathLabel";
			this->ImagePathLabel->Size = System::Drawing::Size(65, 13);
			this->ImagePathLabel->TabIndex = 9;
			this->ImagePathLabel->Text = L"Фото (16:9)";
			// 
			// ImagePathTextBox
			// 
			this->ImagePathTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ImagePathTextBox->ForeColor = System::Drawing::Color::Navy;
			this->ImagePathTextBox->Location = System::Drawing::Point(110, 168);
			this->ImagePathTextBox->Name = L"ImagePathTextBox";
			this->ImagePathTextBox->ReadOnly = true;
			this->ImagePathTextBox->Size = System::Drawing::Size(127, 20);
			this->ImagePathTextBox->TabIndex = 10;
			this->ImagePathTextBox->TabStop = false;
			// 
			// ImagePathButton
			// 
			this->ImagePathButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->ImagePathButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ImagePathButton->Location = System::Drawing::Point(243, 166);
			this->ImagePathButton->Name = L"ImagePathButton";
			this->ImagePathButton->Size = System::Drawing::Size(61, 23);
			this->ImagePathButton->TabIndex = 8;
			this->ImagePathButton->Text = L"Выбрать";
			this->ImagePathButton->UseVisualStyleBackColor = false;
			this->ImagePathButton->Click +=
				gcnew System::EventHandler(this, &CreateNewNumber::ImagePathButton_Click);
			// 
			// CreateNewNumber
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
					static_cast<System::Int32>(static_cast<System::Byte>(135)),
					static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(316, 229);
			this->Controls->Add(this->ImagePathButton);
			this->Controls->Add(this->ImagePathTextBox);
			this->Controls->Add(this->ImagePathLabel);
			this->Controls->Add(this->TvPanel);
			this->Controls->Add(this->WifiPanel);
			this->Controls->Add(this->CreateButton);
			this->Controls->Add(this->SquareTextBox);
			this->Controls->Add(this->SleepingPlaceTextBox);
			this->Controls->Add(this->PriceTextBox);
			this->Controls->Add(this->NumberNumericUpDown);
			this->Controls->Add(this->SquareLabel);
			this->Controls->Add(this->SleepingPlaceLabel);
			this->Controls->Add(this->TvLabel);
			this->Controls->Add(this->WifiLabel);
			this->Controls->Add(this->PriceLabel);
			this->Controls->Add(this->NumberLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"CreateNewNumber";
			this->Text = L"Создать новый номер";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumberNumericUpDown))->EndInit();
			this->WifiPanel->ResumeLayout(false);
			this->WifiPanel->PerformLayout();
			this->TvPanel->ResumeLayout(false);
			this->TvPanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void CreateButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		unsigned short selectedNumber = System::UInt16::Parse(this->NumberNumericUpDown->Text);
		for (size_t i{}; i < m_parent->m_roomStorage->GetSize(); ++i)
		{
			if (selectedNumber == m_parent->m_roomStorage->operator[](i).number)
			{
				MessageBox::Show("Такой номер уже существует", "Номер занят",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}
		}

		BlackLine::InputHandler costInput{ this->PriceTextBox->Text };
		BlackLine::InputHandler squareInput{ this->SquareTextBox->Text };

		try
		{
			unsigned long cost = costInput.GetCost();
			std::string square = squareInput.GetSquare();

			if (this->ImagePathTextBox->Text != "")
			{
				unsigned long id = BlackLine::AddRoom(*m_parent->m_roomStorage, selectedNumber,
					cost, this->WifiYesRadioButton->Checked, this->TvYesRadioButton->Checked,
					msclr::interop::marshal_as<std::string>(this->SleepingPlaceTextBox->Text), square);
				m_parent->NumbersRichTextBox->Text = gcnew
					System::String(BlackLine::ShowRoomList(*m_parent->m_roomStorage, *m_parent->m_orderStorage, true).c_str());

				BlackLine::NumberImageStorage storage("NumberImageStorage.bin");
				storage.Add(id, this->ImagePathTextBox->Text);

				MessageBox::Show("Новый номер успешно создан", "Номер создан",
					MessageBoxButtons::OK, MessageBoxIcon::Information);
				this->Close();
			}
			else
			{
				MessageBox::Show("Поле выбора изображения не заполнено", "Выберите изображение",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		catch (BlackLine::InputException& exception)
		{
			MessageBox::Show(exception.GetMessage(), exception.GetCaption(),
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void ImagePathButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenFileDialog^ imageDialog = gcnew OpenFileDialog();
		imageDialog->Filter = "Изображения (*.png, *.jpg)|*.png;*.jpg";
		if (imageDialog->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			this->ImagePathTextBox->Text = imageDialog->FileName;
		}
	}
	};
}