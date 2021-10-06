#pragma once
#include "NumbersMenu.h"
#include "ChooseRoom.h"
#include <msclr\marshal_cppstd.h>
#include "EditRoomList.h"
#include "InputHandler.h"
#include "NumberImageStorage.h"

namespace Project8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ShowNumber : public System::Windows::Forms::Form
	{
	public:
		ShowNumber(NumbersMenu^ parent)
		{
			m_parent = parent;

			m_index = BlackLine::FindIndex(*m_parent->m_roomStorage,
				System::UInt16::Parse(m_parent->ChooseNumberNumericUpDown->Text));
			
			InitializeComponent();

			this->NumberLabel->Text = m_parent->ChooseNumberNumericUpDown->Text;
			this->PriceTextBox->Text = gcnew
				System::String(std::to_string(m_parent->m_roomStorage->operator[](m_index).cost).c_str());

			if (m_parent->m_roomStorage->operator[](m_index).description.wifi == true)
			{
				this->WifiYesRadioButton->Checked = true;
			}
			else
			{
				this->WifiNoRadioButton->Checked = true;
			}

			if (m_parent->m_roomStorage->operator[](m_index).description.television == true)
			{
				this->TvYesRadioButton->Checked = true;
			}
			else
			{
				this->TvNoRadioButton->Checked = true;
			}

			this->SleepingPlaceTextBox->Text = gcnew
				System::String(m_parent->m_roomStorage->operator[](m_index).description.sleepingPlace.c_str());
			this->SquareTextBox->Text = gcnew
				System::String(m_parent->m_roomStorage->operator[](m_index).description.roomSize.c_str());

			if (m_parent->m_roomStorage->operator[](m_index).isAvailable)
			{
				this->AvailableRadioButton->Checked = true;
			}
			else
			{
				this->UnavailableRadioButton->Checked = true;
			}

			if (m_parent->m_isAuthorized == true)
			{
				BlackLine::User::Role role{};
				for (size_t i{}; i < m_parent->m_userStorage->GetSize(); ++i)
				{
					if (m_parent->m_authorizedId == m_parent->m_userStorage->operator[](i).id)
					{
						role = m_parent->m_userStorage->operator[](i).role;
						break;
					}
				}

				if (role == BlackLine::User::ADMIN)
				{
					size_t numberOfOrders{};
					this->BookedTimeRichTextBox->Text = gcnew System::String(BlackLine::FindOrdersWithUsers(*m_parent->m_roomStorage,
						*m_parent->m_orderStorage, *m_parent->m_userStorage, m_index, numberOfOrders).c_str());
					this->OrderNumericUpDown->Maximum = numberOfOrders;

					if (numberOfOrders == 0)
					{
						this->OrderNumericUpDown->Minimum = 0;
						this->OrderNumericUpDown->Enabled = false;
						this->EditOrderButton->Enabled = false;
						this->DeleteOrderButton->Enabled = false;
					}

					this->PriceTextBox->TabStop = true;
					this->SleepingPlaceTextBox->TabStop = true;
					this->SquareTextBox->TabStop = true;

					this->PriceTextBox->ReadOnly = false;
					this->WifiPanel->Enabled = true;
					this->TvPanel->Enabled = true;
					this->SleepingPlaceTextBox->ReadOnly = false;
					this->SquareTextBox->ReadOnly = false;
					this->AvailablePanel->Enabled = true;

					this->EditButton->Visible = true;
					this->DeleteButton->Visible = true;
					this->OrderNumberLabel->Visible = true;
					this->OrderNumericUpDown->Visible = true;
					this->EditOrderButton->Visible = true;
					this->DeleteOrderButton->Visible = true;
					this->BookedTimeRichTextBox->Visible = true;
					this->NumberPictureBox->Visible = false;

					this->BookedTimeLabel->Text = "Забронированное время";
				}
				else if (role == BlackLine::User::CLIENT)
				{
					this->PriceTextBox->TabStop = false;
					this->SleepingPlaceTextBox->TabStop = false;
					this->SquareTextBox->TabStop = false;

					this->BookedTimeLabel->Location = System::Drawing::Point(481, 9);

					this->BuyButton->Visible = true;
					this->BookedTimeRichTextBox->Visible = false;
					this->NumberPictureBox->Visible = true;

					this->BookedTimeLabel->Text = "Фото номера";

					if (this->UnavailableRadioButton->Checked)
					{
						this->BuyButton->Enabled = false;
					}
					else
					{
						this->BuyButton->Enabled = true;
					}

					BlackLine::NumberImageStorage storage("NumberImageStorage.bin");
					System::String^ imagePath = storage.GetPathById(m_parent->m_roomStorage->operator[](m_index).id);

					if (imagePath != "")
					{
						Bitmap^ image = gcnew Bitmap(imagePath);
						this->NumberPictureBox->Image = image;
					}
					else
					{
						MessageBox::Show("Не удалось загрузить изображение", "Изображение не найдено",
							MessageBoxButtons::OK, MessageBoxIcon::Error);
					}
				}
			}
			else
			{
				this->BookedTimeLabel->Location = System::Drawing::Point(481, 9);

				this->BookedTimeRichTextBox->Visible = false;
				this->NumberPictureBox->Visible = true;

				this->BookedTimeLabel->Text = "Фото номера";

				BlackLine::NumberImageStorage storage("NumberImageStorage.bin");
				System::String^ imagePath = storage.GetPathById(m_parent->m_roomStorage->operator[](m_index).id);

				if (imagePath != "")
				{
					Bitmap^ image = gcnew Bitmap(imagePath);
					this->NumberPictureBox->Image = image;
				}
				else
				{
					MessageBox::Show("Не удалось загрузить изображение", "Изображение не найдено",
						MessageBoxButtons::OK, MessageBoxIcon::Error);
				}

			}
		}

	protected:
		~ShowNumber()
		{
			if (components)
			{
				delete components;
			}
		}
	public: NumbersMenu^ m_parent;
	public: size_t m_index{};

	private: System::Windows::Forms::Panel^ TvPanel;
	private: System::Windows::Forms::RadioButton^ TvYesRadioButton;
	private: System::Windows::Forms::RadioButton^ TvNoRadioButton;
	private: System::Windows::Forms::Panel^ WifiPanel;
	private: System::Windows::Forms::RadioButton^ WifiYesRadioButton;
	private: System::Windows::Forms::RadioButton^ WifiNoRadioButton;
	private: System::Windows::Forms::TextBox^ SquareTextBox;
	private: System::Windows::Forms::TextBox^ SleepingPlaceTextBox;
	private: System::Windows::Forms::TextBox^ PriceTextBox;
	private: System::Windows::Forms::Label^ SquareLabel;
	private: System::Windows::Forms::Label^ SleepingPlaceLabel;
	private: System::Windows::Forms::Label^ TvLabel;
	private: System::Windows::Forms::Label^ WifiLabel;
	private: System::Windows::Forms::Label^ PriceLabel;
	private: System::Windows::Forms::Label^ NumberTextLabel;
	private: System::Windows::Forms::Label^ NowAvailableLabel;
	private: System::Windows::Forms::Label^ BookedTimeLabel;
	private: System::Windows::Forms::Panel^ AvailablePanel;
	private: System::Windows::Forms::RadioButton^ AvailableRadioButton;
	private: System::Windows::Forms::RadioButton^ UnavailableRadioButton;
	public: System::Windows::Forms::RichTextBox^ BookedTimeRichTextBox;
	private: System::Windows::Forms::Button^ BuyButton;
	private: System::Windows::Forms::Button^ EditButton;
	private: System::Windows::Forms::Button^ DeleteButton;
	public: System::Windows::Forms::Button^ EditOrderButton;
	public: System::Windows::Forms::NumericUpDown^ OrderNumericUpDown;
	private: System::Windows::Forms::Label^ OrderNumberLabel;
	private: System::Windows::Forms::Label^ NumberLabel;
	public: System::Windows::Forms::Button^ DeleteOrderButton;
	private: System::Windows::Forms::PictureBox^ NumberPictureBox;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources =
				(gcnew System::ComponentModel::ComponentResourceManager(ShowNumber::typeid));
			this->TvPanel = (gcnew System::Windows::Forms::Panel());
			this->TvYesRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->TvNoRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->WifiPanel = (gcnew System::Windows::Forms::Panel());
			this->WifiYesRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->WifiNoRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->SquareTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SleepingPlaceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PriceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SquareLabel = (gcnew System::Windows::Forms::Label());
			this->SleepingPlaceLabel = (gcnew System::Windows::Forms::Label());
			this->TvLabel = (gcnew System::Windows::Forms::Label());
			this->WifiLabel = (gcnew System::Windows::Forms::Label());
			this->PriceLabel = (gcnew System::Windows::Forms::Label());
			this->NumberTextLabel = (gcnew System::Windows::Forms::Label());
			this->NowAvailableLabel = (gcnew System::Windows::Forms::Label());
			this->BookedTimeLabel = (gcnew System::Windows::Forms::Label());
			this->AvailablePanel = (gcnew System::Windows::Forms::Panel());
			this->UnavailableRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->AvailableRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->BookedTimeRichTextBox = (gcnew System::Windows::Forms::RichTextBox());
			this->BuyButton = (gcnew System::Windows::Forms::Button());
			this->EditButton = (gcnew System::Windows::Forms::Button());
			this->DeleteButton = (gcnew System::Windows::Forms::Button());
			this->EditOrderButton = (gcnew System::Windows::Forms::Button());
			this->OrderNumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->OrderNumberLabel = (gcnew System::Windows::Forms::Label());
			this->NumberLabel = (gcnew System::Windows::Forms::Label());
			this->DeleteOrderButton = (gcnew System::Windows::Forms::Button());
			this->NumberPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->TvPanel->SuspendLayout();
			this->WifiPanel->SuspendLayout();
			this->AvailablePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OrderNumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumberPictureBox))->BeginInit();
			this->SuspendLayout();
			// 
			// TvPanel
			// 
			this->TvPanel->Controls->Add(this->TvYesRadioButton);
			this->TvPanel->Controls->Add(this->TvNoRadioButton);
			this->TvPanel->Enabled = false;
			this->TvPanel->Location = System::Drawing::Point(110, 85);
			this->TvPanel->Name = L"TvPanel";
			this->TvPanel->Size = System::Drawing::Size(100, 20);
			this->TvPanel->TabIndex = 3;
			// 
			// TvYesRadioButton
			// 
			this->TvYesRadioButton->AutoSize = true;
			this->TvYesRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->TvYesRadioButton->Location = System::Drawing::Point(0, 0);
			this->TvYesRadioButton->Name = L"TvYesRadioButton";
			this->TvYesRadioButton->Size = System::Drawing::Size(49, 17);
			this->TvYesRadioButton->TabIndex = 10;
			this->TvYesRadioButton->TabStop = true;
			this->TvYesRadioButton->Text = L"Есть";
			this->TvYesRadioButton->UseVisualStyleBackColor = true;
			// 
			// TvNoRadioButton
			// 
			this->TvNoRadioButton->AutoSize = true;
			this->TvNoRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->TvNoRadioButton->Location = System::Drawing::Point(55, 0);
			this->TvNoRadioButton->Name = L"TvNoRadioButton";
			this->TvNoRadioButton->Size = System::Drawing::Size(44, 17);
			this->TvNoRadioButton->TabIndex = 11;
			this->TvNoRadioButton->TabStop = true;
			this->TvNoRadioButton->Text = L"Нет";
			this->TvNoRadioButton->UseVisualStyleBackColor = true;
			// 
			// WifiPanel
			// 
			this->WifiPanel->Controls->Add(this->WifiYesRadioButton);
			this->WifiPanel->Controls->Add(this->WifiNoRadioButton);
			this->WifiPanel->Enabled = false;
			this->WifiPanel->Location = System::Drawing::Point(110, 59);
			this->WifiPanel->Name = L"WifiPanel";
			this->WifiPanel->Size = System::Drawing::Size(99, 20);
			this->WifiPanel->TabIndex = 2;
			// 
			// WifiYesRadioButton
			// 
			this->WifiYesRadioButton->AutoSize = true;
			this->WifiYesRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->WifiYesRadioButton->Location = System::Drawing::Point(0, 0);
			this->WifiYesRadioButton->Name = L"WifiYesRadioButton";
			this->WifiYesRadioButton->Size = System::Drawing::Size(49, 17);
			this->WifiYesRadioButton->TabIndex = 8;
			this->WifiYesRadioButton->Text = L"Есть";
			this->WifiYesRadioButton->UseVisualStyleBackColor = true;
			// 
			// WifiNoRadioButton
			// 
			this->WifiNoRadioButton->AutoSize = true;
			this->WifiNoRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->WifiNoRadioButton->Location = System::Drawing::Point(55, 0);
			this->WifiNoRadioButton->Name = L"WifiNoRadioButton";
			this->WifiNoRadioButton->Size = System::Drawing::Size(44, 17);
			this->WifiNoRadioButton->TabIndex = 9;
			this->WifiNoRadioButton->Text = L"Нет";
			this->WifiNoRadioButton->UseVisualStyleBackColor = true;
			// 
			// SquareTextBox
			// 
			this->SquareTextBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->SquareTextBox->ForeColor = System::Drawing::Color::Navy;
			this->SquareTextBox->Location = System::Drawing::Point(110, 137);
			this->SquareTextBox->MaxLength = 3;
			this->SquareTextBox->Name = L"SquareTextBox";
			this->SquareTextBox->ReadOnly = true;
			this->SquareTextBox->Size = System::Drawing::Size(49, 20);
			this->SquareTextBox->TabIndex = 5;
			this->SquareTextBox->TabStop = false;
			// 
			// SleepingPlaceTextBox
			// 
			this->SleepingPlaceTextBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->SleepingPlaceTextBox->ForeColor = System::Drawing::Color::Navy;
			this->SleepingPlaceTextBox->Location = System::Drawing::Point(110, 111);
			this->SleepingPlaceTextBox->MaxLength = 50;
			this->SleepingPlaceTextBox->Name = L"SleepingPlaceTextBox";
			this->SleepingPlaceTextBox->ReadOnly = true;
			this->SleepingPlaceTextBox->Size = System::Drawing::Size(215, 20);
			this->SleepingPlaceTextBox->TabIndex = 4;
			this->SleepingPlaceTextBox->TabStop = false;
			// 
			// PriceTextBox
			// 
			this->PriceTextBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->PriceTextBox->ForeColor = System::Drawing::Color::Navy;
			this->PriceTextBox->Location = System::Drawing::Point(110, 33);
			this->PriceTextBox->MaxLength = 10;
			this->PriceTextBox->Name = L"PriceTextBox";
			this->PriceTextBox->ReadOnly = true;
			this->PriceTextBox->Size = System::Drawing::Size(99, 20);
			this->PriceTextBox->TabIndex = 1;
			this->PriceTextBox->TabStop = false;
			// 
			// SquareLabel
			// 
			this->SquareLabel->AutoSize = true;
			this->SquareLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->SquareLabel->Location = System::Drawing::Point(12, 140);
			this->SquareLabel->Name = L"SquareLabel";
			this->SquareLabel->Size = System::Drawing::Size(54, 13);
			this->SquareLabel->TabIndex = 24;
			this->SquareLabel->Text = L"Площадь";
			// 
			// SleepingPlaceLabel
			// 
			this->SleepingPlaceLabel->AutoSize = true;
			this->SleepingPlaceLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->SleepingPlaceLabel->Location = System::Drawing::Point(12, 114);
			this->SleepingPlaceLabel->Name = L"SleepingPlaceLabel";
			this->SleepingPlaceLabel->Size = System::Drawing::Size(92, 13);
			this->SleepingPlaceLabel->TabIndex = 23;
			this->SleepingPlaceLabel->Text = L"Спальные места";
			// 
			// TvLabel
			// 
			this->TvLabel->AutoSize = true;
			this->TvLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->TvLabel->Location = System::Drawing::Point(12, 87);
			this->TvLabel->Name = L"TvLabel";
			this->TvLabel->Size = System::Drawing::Size(21, 13);
			this->TvLabel->TabIndex = 22;
			this->TvLabel->Text = L"TV";
			// 
			// WifiLabel
			// 
			this->WifiLabel->AutoSize = true;
			this->WifiLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->WifiLabel->Location = System::Drawing::Point(12, 61);
			this->WifiLabel->Name = L"WifiLabel";
			this->WifiLabel->Size = System::Drawing::Size(31, 13);
			this->WifiLabel->TabIndex = 21;
			this->WifiLabel->Text = L"Wi-Fi";
			// 
			// PriceLabel
			// 
			this->PriceLabel->AutoSize = true;
			this->PriceLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->PriceLabel->Location = System::Drawing::Point(12, 36);
			this->PriceLabel->Name = L"PriceLabel";
			this->PriceLabel->Size = System::Drawing::Size(33, 13);
			this->PriceLabel->TabIndex = 20;
			this->PriceLabel->Text = L"Цена";
			// 
			// NumberTextLabel
			// 
			this->NumberTextLabel->AutoSize = true;
			this->NumberTextLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->NumberTextLabel->Location = System::Drawing::Point(12, 9);
			this->NumberTextLabel->Name = L"NumberTextLabel";
			this->NumberTextLabel->Size = System::Drawing::Size(41, 13);
			this->NumberTextLabel->TabIndex = 19;
			this->NumberTextLabel->Text = L"Номер";
			// 
			// NowAvailableLabel
			// 
			this->NowAvailableLabel->AutoSize = true;
			this->NowAvailableLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->NowAvailableLabel->Location = System::Drawing::Point(12, 165);
			this->NowAvailableLabel->Name = L"NowAvailableLabel";
			this->NowAvailableLabel->Size = System::Drawing::Size(61, 13);
			this->NowAvailableLabel->TabIndex = 31;
			this->NowAvailableLabel->Text = L"Состояние";
			// 
			// BookedTimeLabel
			// 
			this->BookedTimeLabel->AutoSize = true;
			this->BookedTimeLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->BookedTimeLabel->Location = System::Drawing::Point(404, 9);
			this->BookedTimeLabel->Name = L"BookedTimeLabel";
			this->BookedTimeLabel->Size = System::Drawing::Size(133, 13);
			this->BookedTimeLabel->TabIndex = 32;
			this->BookedTimeLabel->Text = L"Забронированное время";
			// 
			// AvailablePanel
			// 
			this->AvailablePanel->Controls->Add(this->UnavailableRadioButton);
			this->AvailablePanel->Controls->Add(this->AvailableRadioButton);
			this->AvailablePanel->Enabled = false;
			this->AvailablePanel->Location = System::Drawing::Point(110, 163);
			this->AvailablePanel->Name = L"AvailablePanel";
			this->AvailablePanel->Size = System::Drawing::Size(216, 20);
			this->AvailablePanel->TabIndex = 6;
			// 
			// UnavailableRadioButton
			// 
			this->UnavailableRadioButton->AutoSize = true;
			this->UnavailableRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->UnavailableRadioButton->Location = System::Drawing::Point(78, 0);
			this->UnavailableRadioButton->Name = L"UnavailableRadioButton";
			this->UnavailableRadioButton->Size = System::Drawing::Size(137, 17);
			this->UnavailableRadioButton->TabIndex = 12;
			this->UnavailableRadioButton->Text = L"Временно недоступен";
			this->UnavailableRadioButton->UseVisualStyleBackColor = true;
			// 
			// AvailableRadioButton
			// 
			this->AvailableRadioButton->AutoSize = true;
			this->AvailableRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->AvailableRadioButton->Location = System::Drawing::Point(0, 0);
			this->AvailableRadioButton->Name = L"AvailableRadioButton";
			this->AvailableRadioButton->Size = System::Drawing::Size(72, 17);
			this->AvailableRadioButton->TabIndex = 10;
			this->AvailableRadioButton->Text = L"Работает";
			this->AvailableRadioButton->UseVisualStyleBackColor = true;
			// 
			// BookedTimeRichTextBox
			// 
			this->BookedTimeRichTextBox->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->BookedTimeRichTextBox->ForeColor = System::Drawing::Color::Navy;
			this->BookedTimeRichTextBox->Location = System::Drawing::Point(357, 25);
			this->BookedTimeRichTextBox->Name = L"BookedTimeRichTextBox";
			this->BookedTimeRichTextBox->ReadOnly = true;
			this->BookedTimeRichTextBox->Size = System::Drawing::Size(220, 187);
			this->BookedTimeRichTextBox->TabIndex = 10;
			this->BookedTimeRichTextBox->Text = L"";
			// 
			// BuyButton
			// 
			this->BuyButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->BuyButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->BuyButton->Location = System::Drawing::Point(110, 189);
			this->BuyButton->Name = L"BuyButton";
			this->BuyButton->Size = System::Drawing::Size(99, 23);
			this->BuyButton->TabIndex = 8;
			this->BuyButton->Text = L"Купить";
			this->BuyButton->UseVisualStyleBackColor = false;
			this->BuyButton->Visible = false;
			this->BuyButton->Click +=
				gcnew System::EventHandler(this, &ShowNumber::BuyButton_Click);
			// 
			// EditButton
			// 
			this->EditButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->EditButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->EditButton->Location = System::Drawing::Point(15, 189);
			this->EditButton->Name = L"EditButton";
			this->EditButton->Size = System::Drawing::Size(91, 23);
			this->EditButton->TabIndex = 7;
			this->EditButton->Text = L"Изменить";
			this->EditButton->UseVisualStyleBackColor = false;
			this->EditButton->Visible = false;
			this->EditButton->Click +=
				gcnew System::EventHandler(this, &ShowNumber::EditButton_Click);
			// 
			// DeleteButton
			// 
			this->DeleteButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->DeleteButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->DeleteButton->Location = System::Drawing::Point(215, 189);
			this->DeleteButton->Name = L"DeleteButton";
			this->DeleteButton->Size = System::Drawing::Size(89, 23);
			this->DeleteButton->TabIndex = 9;
			this->DeleteButton->Text = L"Удалить";
			this->DeleteButton->UseVisualStyleBackColor = false;
			this->DeleteButton->Visible = false;
			this->DeleteButton->Click +=
				gcnew System::EventHandler(this, &ShowNumber::DeleteButton_Click);
			// 
			// EditOrderButton
			// 
			this->EditOrderButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->EditOrderButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->EditOrderButton->Location = System::Drawing::Point(583, 52);
			this->EditOrderButton->Name = L"EditOrderButton";
			this->EditOrderButton->Size = System::Drawing::Size(100, 23);
			this->EditOrderButton->TabIndex = 12;
			this->EditOrderButton->Text = L"Изменить бронь";
			this->EditOrderButton->UseVisualStyleBackColor = false;
			this->EditOrderButton->Visible = false;
			this->EditOrderButton->Click +=
				gcnew System::EventHandler(this, &ShowNumber::EditOrderButton_Click);
			// 
			// OrderNumericUpDown
			// 
			this->OrderNumericUpDown->BackColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->OrderNumericUpDown->ForeColor = System::Drawing::Color::Navy;
			this->OrderNumericUpDown->Location = System::Drawing::Point(607, 26);
			this->OrderNumericUpDown->Minimum =
				System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->OrderNumericUpDown->Name = L"OrderNumericUpDown";
			this->OrderNumericUpDown->Size = System::Drawing::Size(76, 20);
			this->OrderNumericUpDown->TabIndex = 11;
			this->OrderNumericUpDown->Value =
				System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->OrderNumericUpDown->Visible = false;
			// 
			// OrderNumberLabel
			// 
			this->OrderNumberLabel->AutoSize = true;
			this->OrderNumberLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->OrderNumberLabel->Location = System::Drawing::Point(583, 28);
			this->OrderNumberLabel->Name = L"OrderNumberLabel";
			this->OrderNumberLabel->Size = System::Drawing::Size(18, 13);
			this->OrderNumberLabel->TabIndex = 39;
			this->OrderNumberLabel->Text = L"№";
			this->OrderNumberLabel->Visible = false;
			// 
			// NumberLabel
			// 
			this->NumberLabel->AutoSize = true;
			this->NumberLabel->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->NumberLabel->Location = System::Drawing::Point(107, 9);
			this->NumberLabel->Name = L"NumberLabel";
			this->NumberLabel->Size = System::Drawing::Size(13, 13);
			this->NumberLabel->TabIndex = 0;
			this->NumberLabel->Text = L"1";
			// 
			// DeleteOrderButton
			// 
			this->DeleteOrderButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->DeleteOrderButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->DeleteOrderButton->Location = System::Drawing::Point(583, 81);
			this->DeleteOrderButton->Name = L"DeleteOrderButton";
			this->DeleteOrderButton->Size = System::Drawing::Size(100, 23);
			this->DeleteOrderButton->TabIndex = 13;
			this->DeleteOrderButton->Text = L"Удалить бронь";
			this->DeleteOrderButton->UseVisualStyleBackColor = false;
			this->DeleteOrderButton->Visible = false;
			this->DeleteOrderButton->Click +=
				gcnew System::EventHandler(this, &ShowNumber::DeleteOrderButton_Click);
			// 
			// NumberPictureBox
			// 
			this->NumberPictureBox->Location = System::Drawing::Point(347, 25);
			this->NumberPictureBox->Name = L"NumberPictureBox";
			this->NumberPictureBox->Size = System::Drawing::Size(336, 189);
			this->NumberPictureBox->SizeMode =
				System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->NumberPictureBox->TabIndex = 40;
			this->NumberPictureBox->TabStop = false;
			// 
			// ShowNumber
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
					static_cast<System::Int32>(static_cast<System::Byte>(135)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(695, 226);
			this->Controls->Add(this->NumberPictureBox);
			this->Controls->Add(this->DeleteOrderButton);
			this->Controls->Add(this->NumberLabel);
			this->Controls->Add(this->OrderNumberLabel);
			this->Controls->Add(this->OrderNumericUpDown);
			this->Controls->Add(this->EditOrderButton);
			this->Controls->Add(this->DeleteButton);
			this->Controls->Add(this->EditButton);
			this->Controls->Add(this->BuyButton);
			this->Controls->Add(this->BookedTimeRichTextBox);
			this->Controls->Add(this->AvailablePanel);
			this->Controls->Add(this->BookedTimeLabel);
			this->Controls->Add(this->NowAvailableLabel);
			this->Controls->Add(this->TvPanel);
			this->Controls->Add(this->WifiPanel);
			this->Controls->Add(this->SquareTextBox);
			this->Controls->Add(this->SleepingPlaceTextBox);
			this->Controls->Add(this->PriceTextBox);
			this->Controls->Add(this->SquareLabel);
			this->Controls->Add(this->SleepingPlaceLabel);
			this->Controls->Add(this->TvLabel);
			this->Controls->Add(this->WifiLabel);
			this->Controls->Add(this->PriceLabel);
			this->Controls->Add(this->NumberTextLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"ShowNumber";
			this->Text = L"Номер отеля";
			this->FormClosed +=
				gcnew System::Windows::Forms::FormClosedEventHandler(this,
					&ShowNumber::ShowNumber_FormClosed);
			this->TvPanel->ResumeLayout(false);
			this->TvPanel->PerformLayout();
			this->WifiPanel->ResumeLayout(false);
			this->WifiPanel->PerformLayout();
			this->AvailablePanel->ResumeLayout(false);
			this->AvailablePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->OrderNumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumberPictureBox))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ShowNumber_FormClosed(System::Object^ sender,
		System::Windows::Forms::FormClosedEventArgs^ e)
	{
		delete this->NumberPictureBox->Image;
		this->NumberPictureBox->Image = nullptr;
	}

	private: System::Void EditButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		BlackLine::InputHandler costInput{ this->PriceTextBox->Text };
		BlackLine::InputHandler squareInput{ this->SquareTextBox->Text };

		try
		{
			unsigned long cost = costInput.GetCost();
			std::string square = squareInput.GetSquare();
			BlackLine::EditNumber(*m_parent->m_roomStorage, m_index, cost,
				this->WifiYesRadioButton->Checked, this->TvYesRadioButton->Checked,
				msclr::interop::marshal_as<std::string>(this->SleepingPlaceTextBox->Text),
				square, this->AvailableRadioButton->Checked);

			m_parent->NumbersRichTextBox->Text =
				gcnew System::String(BlackLine::ShowRoomList(*m_parent->m_roomStorage,
					*m_parent->m_orderStorage, true).c_str());

			MessageBox::Show("Информация о номере изменена", "Номер изменен",
				MessageBoxButtons::OK, MessageBoxIcon::Information);

			this->Close();
		}
		catch (BlackLine::InputException& exception)
		{
			MessageBox::Show(exception.GetMessage(), exception.GetCaption(),
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	private: System::Void DeleteButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (MessageBox::Show("Вы уверены, что хотите удалить этот номер? Информация о нем не сохранится",
			"Удаление номера", MessageBoxButtons::YesNo, MessageBoxIcon::Question,
			MessageBoxDefaultButton::Button2) != System::Windows::Forms::DialogResult::Yes) { return; }

		BlackLine::NumberImageStorage storage("NumberImageStorage.bin");
		storage.Remove(m_parent->m_roomStorage->operator[](m_index).id);

		BlackLine::DeleteRoom(*m_parent->m_roomStorage, System::UInt16::Parse(this->NumberLabel->Text));
		m_parent->NumbersRichTextBox->Text =
			gcnew System::String(BlackLine::ShowRoomList(*m_parent->m_roomStorage,
			*m_parent->m_orderStorage, true).c_str());

		MessageBox::Show("Номер успешно удален", "Номер удален",
			MessageBoxButtons::OK, MessageBoxIcon::Information);

		this->Close();
	}

	private: System::Void EditOrderButton_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void DeleteOrderButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (MessageBox::Show("Вы уверены, что хотите удалить этот забронированный промежуток времени? Информация о нем сохранится в журнале",
			"Удаление брони", MessageBoxButtons::YesNo, MessageBoxIcon::Question, MessageBoxDefaultButton::Button2) !=
			System::Windows::Forms::DialogResult::Yes) { return; }

		BlackLine::DeleteOrder(*m_parent->m_roomStorage, *m_parent->m_orderStorage,
			*m_parent->m_userStorage, m_index, System::UInt32::Parse(this->OrderNumericUpDown->Text));

		size_t numberOfOrders{};
		this->BookedTimeRichTextBox->Text =
			gcnew System::String(BlackLine::FindOrdersWithUsers(*m_parent->m_roomStorage,
			*m_parent->m_orderStorage, *m_parent->m_userStorage, m_index, numberOfOrders).c_str());
		this->OrderNumericUpDown->Maximum = numberOfOrders;

		if (numberOfOrders == 0)
		{
			this->OrderNumericUpDown->Minimum = 0;
			this->OrderNumericUpDown->Enabled = false;
			this->EditOrderButton->Enabled = false;
			this->DeleteOrderButton->Enabled = false;
		}

		m_parent->NumbersRichTextBox->Text =
			gcnew System::String(BlackLine::ShowRoomList(*m_parent->m_roomStorage,
				*m_parent->m_orderStorage, true).c_str());

		MessageBox::Show("Заказ успешно удален", "Заказ удален",
			MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void BuyButton_Click(System::Object^ sender, System::EventArgs^ e);
	};
}