#pragma once
#include "FilterRoomList.h"
#include "UserStorage.h"
#include "RemoveOrders.h"
#include "InputHandler.h"

namespace Project8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class NumbersMenu : public System::Windows::Forms::Form
	{
	public:
		NumbersMenu(void)
		{
			m_roomStorage = new BlackLine::RoomStorage("RoomStorage.bin", "Rooms IDs.bin");
			m_orderStorage = new BlackLine::OrderStorage("OrderStorage.bin", "Orders IDs.bin");
			m_userStorage = new BlackLine::UserStorage("UserStorage.bin", "Users IDs.bin");

			m_authorizedId = 0;
			m_isAuthorized = false;

			InitializeComponent();

			BlackLine::RemoveOutdatedOrders(*m_orderStorage, *m_roomStorage, *m_userStorage, "Orders log.txt");
			this->NumbersRichTextBox->Text = gcnew System::String(BlackLine::ShowRoomList(*m_roomStorage,
				*m_orderStorage, true).c_str());
		}

	protected:
		~NumbersMenu()
		{
			if (components)
			{
				delete components;
			}
		}

	public: BlackLine::RoomStorage* m_roomStorage{};
	public: BlackLine::OrderStorage* m_orderStorage{};
	public: BlackLine::UserStorage* m_userStorage{};
	public: unsigned long m_authorizedId{};
	public: bool m_isAuthorized{};

	private: System::Windows::Forms::TextBox^ ShowAvailableTextBox;
	private: System::Windows::Forms::Button^ ShowAvailableButton;
	private: System::Windows::Forms::Label^ EndDateLabel;
	private: System::Windows::Forms::Label^ StartDateLabel;
	private: System::Windows::Forms::Label^ YearLabel;
	private: System::Windows::Forms::Label^ MonthLabel;
	private: System::Windows::Forms::Label^ DayLabel;
	private: System::Windows::Forms::TextBox^ EndYearBox;
	private: System::Windows::Forms::TextBox^ EndMonthBox;
	private: System::Windows::Forms::TextBox^ EndDayBox;
	private: System::Windows::Forms::TextBox^ StartYearBox;
	private: System::Windows::Forms::TextBox^ StartMonthBox;
	private: System::Windows::Forms::TextBox^ StartDayBox;
	private: System::Windows::Forms::Button^ ChooseNumberButton;
	private: System::Windows::Forms::Label^ ChooseNumberLabel;
	public: System::Windows::Forms::NumericUpDown^ ChooseNumberNumericUpDown;
	public: System::Windows::Forms::RichTextBox^ NumbersRichTextBox;
	private: System::Windows::Forms::MenuStrip^ MenuStrip;
	public: System::Windows::Forms::ToolStripMenuItem^ LogInToolStripMenuItem;
	public: System::Windows::Forms::ToolStripMenuItem^ UserToolStripMenuItem;
	public: System::Windows::Forms::ToolStripMenuItem^ AddNumberToolStripMenuItem;
	public: System::Windows::Forms::ToolStripMenuItem^ LogOutToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^ NumbersGroupBox;
	private: System::Windows::Forms::GroupBox^ ShowAvailableGroupBox;
	private: System::Windows::Forms::PictureBox^ HotelPictureBox;
	private: System::Windows::Forms::Label^ availableNumbersLabel;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources =
				(gcnew System::ComponentModel::ComponentResourceManager(NumbersMenu::typeid));
			this->ShowAvailableTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ShowAvailableButton = (gcnew System::Windows::Forms::Button());
			this->EndDateLabel = (gcnew System::Windows::Forms::Label());
			this->StartDateLabel = (gcnew System::Windows::Forms::Label());
			this->YearLabel = (gcnew System::Windows::Forms::Label());
			this->MonthLabel = (gcnew System::Windows::Forms::Label());
			this->DayLabel = (gcnew System::Windows::Forms::Label());
			this->EndYearBox = (gcnew System::Windows::Forms::TextBox());
			this->EndMonthBox = (gcnew System::Windows::Forms::TextBox());
			this->EndDayBox = (gcnew System::Windows::Forms::TextBox());
			this->StartYearBox = (gcnew System::Windows::Forms::TextBox());
			this->StartMonthBox = (gcnew System::Windows::Forms::TextBox());
			this->StartDayBox = (gcnew System::Windows::Forms::TextBox());
			this->ChooseNumberButton = (gcnew System::Windows::Forms::Button());
			this->ChooseNumberLabel = (gcnew System::Windows::Forms::Label());
			this->ChooseNumberNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->NumbersRichTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->MenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->LogInToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->UserToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->AddNumberToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->LogOutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->NumbersGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->ShowAvailableGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->availableNumbersLabel = (gcnew System::Windows::Forms::Label());
			this->HotelPictureBox = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChooseNumberNumericUpDown))->BeginInit();
			this->MenuStrip->SuspendLayout();
			this->NumbersGroupBox->SuspendLayout();
			this->ShowAvailableGroupBox->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HotelPictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// ShowAvailableTextBox
			// 
			this->ShowAvailableTextBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->ShowAvailableTextBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->ShowAvailableTextBox->ForeColor = System::Drawing::Color::Navy;
			this->ShowAvailableTextBox->Location = System::Drawing::Point(11, 189);
			this->ShowAvailableTextBox->Name = L"ShowAvailableTextBox";
			this->ShowAvailableTextBox->ReadOnly = true;
			this->ShowAvailableTextBox->Size = System::Drawing::Size(290, 32);
			this->ShowAvailableTextBox->TabIndex = 10;
			// 
			// ShowAvailableButton
			// 
			this->ShowAvailableButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->ShowAvailableButton->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->ShowAvailableButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->ShowAvailableButton->Location = System::Drawing::Point(11, 227);
			this->ShowAvailableButton->Name = L"ShowAvailableButton";
			this->ShowAvailableButton->Size = System::Drawing::Size(290, 46);
			this->ShowAvailableButton->TabIndex = 9;
			this->ShowAvailableButton->Text = L"Показать";
			this->ShowAvailableButton->UseVisualStyleBackColor = false;
			this->ShowAvailableButton->Click +=
				gcnew System::EventHandler(this, &NumbersMenu::ShowAvailableButton_Click);
			// 
			// EndDateLabel
			// 
			this->EndDateLabel->AutoSize = true;
			this->EndDateLabel->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->EndDateLabel->Location = System::Drawing::Point(6, 106);
			this->EndDateLabel->Name = L"EndDateLabel";
			this->EndDateLabel->Size = System::Drawing::Size(76, 26);
			this->EndDateLabel->TabIndex = 69;
			this->EndDateLabel->Text = L"Конец";
			// 
			// StartDateLabel
			// 
			this->StartDateLabel->AutoSize = true;
			this->StartDateLabel->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->StartDateLabel->Location = System::Drawing::Point(6, 68);
			this->StartDateLabel->Name = L"StartDateLabel";
			this->StartDateLabel->Size = System::Drawing::Size(89, 26);
			this->StartDateLabel->TabIndex = 68;
			this->StartDateLabel->Text = L"Начало";
			// 
			// YearLabel
			// 
			this->YearLabel->AutoSize = true;
			this->YearLabel->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->YearLabel->Location = System::Drawing::Point(241, 34);
			this->YearLabel->Name = L"YearLabel";
			this->YearLabel->Size = System::Drawing::Size(60, 26);
			this->YearLabel->TabIndex = 67;
			this->YearLabel->Text = L"ГГГГ";
			// 
			// MonthLabel
			// 
			this->MonthLabel->AutoSize = true;
			this->MonthLabel->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->MonthLabel->Location = System::Drawing::Point(188, 34);
			this->MonthLabel->Name = L"MonthLabel";
			this->MonthLabel->Size = System::Drawing::Size(48, 26);
			this->MonthLabel->TabIndex = 66;
			this->MonthLabel->Text = L"ММ";
			// 
			// DayLabel
			// 
			this->DayLabel->AutoSize = true;
			this->DayLabel->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->DayLabel->Location = System::Drawing::Point(127, 34);
			this->DayLabel->Name = L"DayLabel";
			this->DayLabel->Size = System::Drawing::Size(46, 26);
			this->DayLabel->TabIndex = 65;
			this->DayLabel->Text = L"ДД";
			// 
			// EndYearBox
			// 
			this->EndYearBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->EndYearBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->EndYearBox->ForeColor = System::Drawing::Color::Navy;
			this->EndYearBox->Location = System::Drawing::Point(245, 103);
			this->EndYearBox->MaxLength = 4;
			this->EndYearBox->Name = L"EndYearBox";
			this->EndYearBox->Size = System::Drawing::Size(56, 32);
			this->EndYearBox->TabIndex = 8;
			this->EndYearBox->Tag = L"";
			// 
			// EndMonthBox
			// 
			this->EndMonthBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->EndMonthBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->EndMonthBox->ForeColor = System::Drawing::Color::Navy;
			this->EndMonthBox->Location = System::Drawing::Point(183, 103);
			this->EndMonthBox->MaxLength = 2;
			this->EndMonthBox->Name = L"EndMonthBox";
			this->EndMonthBox->Size = System::Drawing::Size(56, 32);
			this->EndMonthBox->TabIndex = 7;
			this->EndMonthBox->Tag = L"";
			// 
			// EndDayBox
			// 
			this->EndDayBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->EndDayBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->EndDayBox->ForeColor = System::Drawing::Color::Navy;
			this->EndDayBox->Location = System::Drawing::Point(121, 103);
			this->EndDayBox->MaxLength = 2;
			this->EndDayBox->Name = L"EndDayBox";
			this->EndDayBox->Size = System::Drawing::Size(56, 32);
			this->EndDayBox->TabIndex = 6;
			this->EndDayBox->Tag = L"";
			// 
			// StartYearBox
			// 
			this->StartYearBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->StartYearBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->StartYearBox->ForeColor = System::Drawing::Color::Navy;
			this->StartYearBox->Location = System::Drawing::Point(245, 65);
			this->StartYearBox->MaxLength = 4;
			this->StartYearBox->Name = L"StartYearBox";
			this->StartYearBox->Size = System::Drawing::Size(56, 32);
			this->StartYearBox->TabIndex = 5;
			this->StartYearBox->Tag = L"";
			// 
			// StartMonthBox
			// 
			this->StartMonthBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->StartMonthBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->StartMonthBox->ForeColor = System::Drawing::Color::Navy;
			this->StartMonthBox->Location = System::Drawing::Point(183, 65);
			this->StartMonthBox->MaxLength = 2;
			this->StartMonthBox->Name = L"StartMonthBox";
			this->StartMonthBox->Size = System::Drawing::Size(56, 32);
			this->StartMonthBox->TabIndex = 4;
			this->StartMonthBox->Tag = L"";
			// 
			// StartDayBox
			// 
			this->StartDayBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->StartDayBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->StartDayBox->ForeColor = System::Drawing::Color::Navy;
			this->StartDayBox->Location = System::Drawing::Point(121, 65);
			this->StartDayBox->MaxLength = 2;
			this->StartDayBox->Name = L"StartDayBox";
			this->StartDayBox->Size = System::Drawing::Size(56, 32);
			this->StartDayBox->TabIndex = 3;
			this->StartDayBox->Tag = L"";
			// 
			// ChooseNumberButton
			// 
			this->ChooseNumberButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->ChooseNumberButton->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->ChooseNumberButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ChooseNumberButton->Location = System::Drawing::Point(184, 405);
			this->ChooseNumberButton->Name = L"ChooseNumberButton";
			this->ChooseNumberButton->Size = System::Drawing::Size(192, 61);
			this->ChooseNumberButton->TabIndex = 2;
			this->ChooseNumberButton->Text = L"Выбрать";
			this->ChooseNumberButton->UseVisualStyleBackColor = false;
			this->ChooseNumberButton->Click +=
				gcnew System::EventHandler(this, &NumbersMenu::ChooseNumberButton_Click);
			// 
			// ChooseNumberLabel
			// 
			this->ChooseNumberLabel->AutoSize = true;
			this->ChooseNumberLabel->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->ChooseNumberLabel->Location = System::Drawing::Point(6, 405);
			this->ChooseNumberLabel->Name = L"ChooseNumberLabel";
			this->ChooseNumberLabel->Size = System::Drawing::Size(172, 26);
			this->ChooseNumberLabel->TabIndex = 56;
			this->ChooseNumberLabel->Text = L"Выбрать номер";
			// 
			// ChooseNumberNumericUpDown
			// 
			this->ChooseNumberNumericUpDown->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->ChooseNumberNumericUpDown->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->ChooseNumberNumericUpDown->ForeColor = System::Drawing::Color::Navy;
			this->ChooseNumberNumericUpDown->Location = System::Drawing::Point(6, 434);
			this->ChooseNumberNumericUpDown->Maximum =
				System::Decimal(gcnew cli::array< System::Int32 >(4) { 65535, 0, 0, 0 });
			this->ChooseNumberNumericUpDown->Minimum =
				System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->ChooseNumberNumericUpDown->Name = L"ChooseNumberNumericUpDown";
			this->ChooseNumberNumericUpDown->ReadOnly = true;
			this->ChooseNumberNumericUpDown->Size = System::Drawing::Size(172, 32);
			this->ChooseNumberNumericUpDown->TabIndex = 1;
			this->ChooseNumberNumericUpDown->Value =
				System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			// 
			// NumbersRichTextBox
			// 
			this->NumbersRichTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->NumbersRichTextBox->ForeColor = System::Drawing::Color::Navy;
			this->NumbersRichTextBox->Location = System::Drawing::Point(6, 31);
			this->NumbersRichTextBox->Name = L"NumbersRichTextBox";
			this->NumbersRichTextBox->ReadOnly = true;
			this->NumbersRichTextBox->Size = System::Drawing::Size(370, 368);
			this->NumbersRichTextBox->TabIndex = 0;
			this->NumbersRichTextBox->Text = L"";
			// 
			// MenuStrip
			// 
			this->MenuStrip->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->MenuStrip->Items->AddRange(gcnew
				cli::array<System::Windows::Forms::ToolStripItem^>(1) { this->LogInToolStripMenuItem });
			this->MenuStrip->Location = System::Drawing::Point(0, 0);
			this->MenuStrip->Name = L"MenuStrip";
			this->MenuStrip->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->MenuStrip->Size = System::Drawing::Size(732, 40);
			this->MenuStrip->TabIndex = 76;
			// 
			// LogInToolStripMenuItem
			// 
			this->LogInToolStripMenuItem->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->LogInToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->LogInToolStripMenuItem->DropDownItems->AddRange(gcnew
				cli::array<System::Windows::Forms::ToolStripItem^>(3) {
				this->UserToolStripMenuItem,
					this->AddNumberToolStripMenuItem, this->LogOutToolStripMenuItem
			});
			this->LogInToolStripMenuItem->Font =
				(gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold));
			this->LogInToolStripMenuItem->ForeColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
				static_cast<System::Int32>(static_cast<System::Byte>(135)),
					static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->LogInToolStripMenuItem->Name = L"LogInToolStripMenuItem";
			this->LogInToolStripMenuItem->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->LogInToolStripMenuItem->Size = System::Drawing::Size(98, 36);
			this->LogInToolStripMenuItem->Text = L"Войти";
			this->LogInToolStripMenuItem->Click +=
				gcnew System::EventHandler(this, &NumbersMenu::LogInToolStripMenuItem_Click);
			// 
			// UserToolStripMenuItem
			// 
			this->UserToolStripMenuItem->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
				static_cast<System::Int32>(static_cast<System::Byte>(135)),
					static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->UserToolStripMenuItem->DisplayStyle =
				System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->UserToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18));
			this->UserToolStripMenuItem->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->UserToolStripMenuItem->Name = L"UserToolStripMenuItem";
			this->UserToolStripMenuItem->Size = System::Drawing::Size(275, 36);
			this->UserToolStripMenuItem->Text = L"Личный кабинет";
			this->UserToolStripMenuItem->Visible = false;
			this->UserToolStripMenuItem->Click +=
				gcnew System::EventHandler(this, &NumbersMenu::UserToolStripMenuItem_Click);
			// 
			// AddNumberToolStripMenuItem
			// 
			this->AddNumberToolStripMenuItem->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
				static_cast<System::Int32>(static_cast<System::Byte>(135)),
					static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->AddNumberToolStripMenuItem->DisplayStyle =
				System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->AddNumberToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18));
			this->AddNumberToolStripMenuItem->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->AddNumberToolStripMenuItem->Name = L"AddNumberToolStripMenuItem";
			this->AddNumberToolStripMenuItem->Size = System::Drawing::Size(275, 36);
			this->AddNumberToolStripMenuItem->Text = L"Добавить номер";
			this->AddNumberToolStripMenuItem->Visible = false;
			this->AddNumberToolStripMenuItem->Click +=
				gcnew System::EventHandler(this, &NumbersMenu::AddNumberToolStripMenuItem_Click);
			// 
			// LogOutToolStripMenuItem
			// 
			this->LogOutToolStripMenuItem->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
				static_cast<System::Int32>(static_cast<System::Byte>(135)),
					static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->LogOutToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->LogOutToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18));
			this->LogOutToolStripMenuItem->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->LogOutToolStripMenuItem->Name = L"LogOutToolStripMenuItem";
			this->LogOutToolStripMenuItem->Size = System::Drawing::Size(275, 36);
			this->LogOutToolStripMenuItem->Text = L"Выход";
			this->LogOutToolStripMenuItem->Visible = false;
			this->LogOutToolStripMenuItem->Click +=
				gcnew System::EventHandler(this, &NumbersMenu::LogOutToolStripMenuItem_Click);
			// 
			// NumbersGroupBox
			// 
			this->NumbersGroupBox->Controls->Add(this->NumbersRichTextBox);
			this->NumbersGroupBox->Controls->Add(this->ChooseNumberLabel);
			this->NumbersGroupBox->Controls->Add(this->ChooseNumberNumericUpDown);
			this->NumbersGroupBox->Controls->Add(this->ChooseNumberButton);
			this->NumbersGroupBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->NumbersGroupBox->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->NumbersGroupBox->Location = System::Drawing::Point(12, 43);
			this->NumbersGroupBox->Name = L"NumbersGroupBox";
			this->NumbersGroupBox->Size = System::Drawing::Size(382, 472);
			this->NumbersGroupBox->TabIndex = 77;
			this->NumbersGroupBox->TabStop = false;
			this->NumbersGroupBox->Text = L"Номера и брони";
			// 
			// ShowAvailableGroupBox
			// 
			this->ShowAvailableGroupBox->Controls->Add(this->availableNumbersLabel);
			this->ShowAvailableGroupBox->Controls->Add(this->YearLabel);
			this->ShowAvailableGroupBox->Controls->Add(this->StartDayBox);
			this->ShowAvailableGroupBox->Controls->Add(this->ShowAvailableTextBox);
			this->ShowAvailableGroupBox->Controls->Add(this->StartMonthBox);
			this->ShowAvailableGroupBox->Controls->Add(this->ShowAvailableButton);
			this->ShowAvailableGroupBox->Controls->Add(this->StartYearBox);
			this->ShowAvailableGroupBox->Controls->Add(this->EndDateLabel);
			this->ShowAvailableGroupBox->Controls->Add(this->EndDayBox);
			this->ShowAvailableGroupBox->Controls->Add(this->StartDateLabel);
			this->ShowAvailableGroupBox->Controls->Add(this->EndMonthBox);
			this->ShowAvailableGroupBox->Controls->Add(this->EndYearBox);
			this->ShowAvailableGroupBox->Controls->Add(this->MonthLabel);
			this->ShowAvailableGroupBox->Controls->Add(this->DayLabel);
			this->ShowAvailableGroupBox->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->ShowAvailableGroupBox->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->ShowAvailableGroupBox->Location = System::Drawing::Point(400, 43);
			this->ShowAvailableGroupBox->Name = L"ShowAvailableGroupBox";
			this->ShowAvailableGroupBox->Size = System::Drawing::Size(318, 286);
			this->ShowAvailableGroupBox->TabIndex = 78;
			this->ShowAvailableGroupBox->TabStop = false;
			this->ShowAvailableGroupBox->Text = L"Доступные номера";
			// 
			// availableNumbersLabel
			// 
			this->availableNumbersLabel->AutoSize = true;
			this->availableNumbersLabel->Font =
				(gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.5F));
			this->availableNumbersLabel->Location = System::Drawing::Point(6, 160);
			this->availableNumbersLabel->Name = L"availableNumbersLabel";
			this->availableNumbersLabel->Size = System::Drawing::Size(300, 26);
			this->availableNumbersLabel->TabIndex = 70;
			this->availableNumbersLabel->Text = L"Список доступных номеров:";
			// 
			// HotelPictureBox
			// 
			this->HotelPictureBox->Image =
				(cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"HotelPictureBox.Image")));
			this->HotelPictureBox->Location = System::Drawing::Point(400, 335);
			this->HotelPictureBox->Name = L"HotelPictureBox";
			this->HotelPictureBox->Size = System::Drawing::Size(320, 180);
			this->HotelPictureBox->TabIndex = 79;
			this->HotelPictureBox->TabStop = false;
			// 
			// NumbersMenu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
					static_cast<System::Int32>(static_cast<System::Byte>(135)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(732, 527);
			this->Controls->Add(this->HotelPictureBox);
			this->Controls->Add(this->ShowAvailableGroupBox);
			this->Controls->Add(this->NumbersGroupBox);
			this->Controls->Add(this->MenuStrip);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon =
				(cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->MenuStrip;
			this->MaximizeBox = false;
			this->Name = L"NumbersMenu";
			this->Text = L"Отельная система";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChooseNumberNumericUpDown))->EndInit();
			this->MenuStrip->ResumeLayout(false);
			this->MenuStrip->PerformLayout();
			this->NumbersGroupBox->ResumeLayout(false);
			this->NumbersGroupBox->PerformLayout();
			this->ShowAvailableGroupBox->ResumeLayout(false);
			this->ShowAvailableGroupBox->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->HotelPictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ShowAvailableButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		BlackLine::InputHandler startDay{ this->StartDayBox->Text };
		BlackLine::InputHandler startMonth{ this->StartMonthBox->Text };
		BlackLine::InputHandler startYear{ this->StartYearBox->Text };
		BlackLine::InputHandler endDay{ this->EndDayBox->Text };
		BlackLine::InputHandler endMonth{ this->EndMonthBox->Text };
		BlackLine::InputHandler endYear{ this->EndYearBox->Text };

		try
		{
			this->ShowAvailableTextBox->Text =
				gcnew System::String(BlackLine::FilterRoomList(*m_roomStorage, *m_orderStorage,
					startDay.GetDay(), startMonth.GetMonth(), startYear.GetYear(),
					endDay.GetDay(), endMonth.GetMonth(), endYear.GetYear()).c_str());
		}
		catch (BlackLine::InputException& exception)
		{
			MessageBox::Show(exception.GetMessage(), exception.GetCaption(),
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void ChooseNumberButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void LogInToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void LogOutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (MessageBox::Show("Вы уверены, что хотите выйти?", "Выход", MessageBoxButtons::YesNo,
			MessageBoxIcon::Question, MessageBoxDefaultButton::Button2) !=
			System::Windows::Forms::DialogResult::Yes) { return; }

		m_isAuthorized = false;
		m_authorizedId = 0;
		this->LogInToolStripMenuItem->Text = "Войти";
		this->UserToolStripMenuItem->Visible = false;
		this->AddNumberToolStripMenuItem->Visible = false;
		this->LogOutToolStripMenuItem->Visible = false;
	}

	private: System::Void UserToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void AddNumberToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	};
}