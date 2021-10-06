#pragma once
#include "ShowNumber.h"
#include "RemoveOrders.h"
#include "InputHandler.h"

namespace Project8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class OrderMenuForm : public System::Windows::Forms::Form
	{
	public:
		OrderMenuForm(ShowNumber^ parent)
		{
			m_parent = parent;

			InitializeComponent();

			for (size_t i{}; i < m_parent->m_parent->m_userStorage->GetSize(); ++i)
			{
				if (m_parent->m_parent->m_authorizedId == m_parent->m_parent->m_userStorage->operator[](i).id)
				{
					m_role = m_parent->m_parent->m_userStorage->operator[](i).role;
					break;
				}
			}
			if (m_role == BlackLine::User::ADMIN)
			{
				this->InfoLabel->Text = "Введите новое время";
				this->BuyButton->Text = "Изменить";
			}
		}

	protected:
		~OrderMenuForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: ShowNumber^ m_parent;
	private: BlackLine::User::Role m_role;

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
	private: System::Windows::Forms::Label^ InfoLabel;
	private: System::Windows::Forms::Button^ BuyButton;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources =
				(gcnew System::ComponentModel::ComponentResourceManager(OrderMenuForm::typeid));
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
			this->InfoLabel = (gcnew System::Windows::Forms::Label());
			this->BuyButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// EndDateLabel
			// 
			this->EndDateLabel->AutoSize = true;
			this->EndDateLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->EndDateLabel->Location = System::Drawing::Point(12, 80);
			this->EndDateLabel->Name = L"EndDateLabel";
			this->EndDateLabel->Size = System::Drawing::Size(38, 13);
			this->EndDateLabel->TabIndex = 81;
			this->EndDateLabel->Text = L"Конец";
			// 
			// StartDateLabel
			// 
			this->StartDateLabel->AutoSize = true;
			this->StartDateLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->StartDateLabel->Location = System::Drawing::Point(12, 54);
			this->StartDateLabel->Name = L"StartDateLabel";
			this->StartDateLabel->Size = System::Drawing::Size(44, 13);
			this->StartDateLabel->TabIndex = 80;
			this->StartDateLabel->Text = L"Начало";
			// 
			// YearLabel
			// 
			this->YearLabel->AutoSize = true;
			this->YearLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->YearLabel->Location = System::Drawing::Point(130, 31);
			this->YearLabel->Name = L"YearLabel";
			this->YearLabel->Size = System::Drawing::Size(31, 13);
			this->YearLabel->TabIndex = 79;
			this->YearLabel->Text = L"ГГГГ";
			// 
			// MonthLabel
			// 
			this->MonthLabel->AutoSize = true;
			this->MonthLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->MonthLabel->Location = System::Drawing::Point(99, 31);
			this->MonthLabel->Name = L"MonthLabel";
			this->MonthLabel->Size = System::Drawing::Size(25, 13);
			this->MonthLabel->TabIndex = 78;
			this->MonthLabel->Text = L"ММ";
			// 
			// DayLabel
			// 
			this->DayLabel->AutoSize = true;
			this->DayLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->DayLabel->Location = System::Drawing::Point(65, 31);
			this->DayLabel->Name = L"DayLabel";
			this->DayLabel->Size = System::Drawing::Size(25, 13);
			this->DayLabel->TabIndex = 77;
			this->DayLabel->Text = L"ДД";
			// 
			// EndYearBox
			// 
			this->EndYearBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->EndYearBox->ForeColor = System::Drawing::Color::Navy;
			this->EndYearBox->Location = System::Drawing::Point(133, 77);
			this->EndYearBox->MaxLength = 4;
			this->EndYearBox->Name = L"EndYearBox";
			this->EndYearBox->Size = System::Drawing::Size(28, 20);
			this->EndYearBox->TabIndex = 5;
			this->EndYearBox->Tag = L"";
			// 
			// EndMonthBox
			// 
			this->EndMonthBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->EndMonthBox->ForeColor = System::Drawing::Color::Navy;
			this->EndMonthBox->Location = System::Drawing::Point(99, 77);
			this->EndMonthBox->MaxLength = 2;
			this->EndMonthBox->Name = L"EndMonthBox";
			this->EndMonthBox->Size = System::Drawing::Size(28, 20);
			this->EndMonthBox->TabIndex = 4;
			this->EndMonthBox->Tag = L"";
			// 
			// EndDayBox
			// 
			this->EndDayBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->EndDayBox->ForeColor = System::Drawing::Color::Navy;
			this->EndDayBox->Location = System::Drawing::Point(62, 77);
			this->EndDayBox->MaxLength = 2;
			this->EndDayBox->Name = L"EndDayBox";
			this->EndDayBox->Size = System::Drawing::Size(28, 20);
			this->EndDayBox->TabIndex = 3;
			this->EndDayBox->Tag = L"";
			// 
			// StartYearBox
			// 
			this->StartYearBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->StartYearBox->ForeColor = System::Drawing::Color::Navy;
			this->StartYearBox->Location = System::Drawing::Point(133, 51);
			this->StartYearBox->MaxLength = 4;
			this->StartYearBox->Name = L"StartYearBox";
			this->StartYearBox->Size = System::Drawing::Size(28, 20);
			this->StartYearBox->TabIndex = 2;
			this->StartYearBox->Tag = L"";
			// 
			// StartMonthBox
			// 
			this->StartMonthBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->StartMonthBox->ForeColor = System::Drawing::Color::Navy;
			this->StartMonthBox->Location = System::Drawing::Point(99, 51);
			this->StartMonthBox->MaxLength = 2;
			this->StartMonthBox->Name = L"StartMonthBox";
			this->StartMonthBox->Size = System::Drawing::Size(28, 20);
			this->StartMonthBox->TabIndex = 1;
			this->StartMonthBox->Tag = L"";
			// 
			// StartDayBox
			// 
			this->StartDayBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->StartDayBox->ForeColor = System::Drawing::Color::Navy;
			this->StartDayBox->Location = System::Drawing::Point(62, 51);
			this->StartDayBox->MaxLength = 2;
			this->StartDayBox->Name = L"StartDayBox";
			this->StartDayBox->Size = System::Drawing::Size(28, 20);
			this->StartDayBox->TabIndex = 0;
			this->StartDayBox->Tag = L"";
			// 
			// InfoLabel
			// 
			this->InfoLabel->AutoSize = true;
			this->InfoLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->InfoLabel->Location = System::Drawing::Point(42, 9);
			this->InfoLabel->Name = L"InfoLabel";
			this->InfoLabel->Size = System::Drawing::Size(138, 13);
			this->InfoLabel->TabIndex = 70;
			this->InfoLabel->Text = L"Введите время для брони";
			this->InfoLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// BuyButton
			// 
			this->BuyButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->BuyButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->BuyButton->Location = System::Drawing::Point(62, 103);
			this->BuyButton->Name = L"BuyButton";
			this->BuyButton->Size = System::Drawing::Size(99, 23);
			this->BuyButton->TabIndex = 6;
			this->BuyButton->Text = L"Купить";
			this->BuyButton->UseVisualStyleBackColor = false;
			this->BuyButton->Click +=
				gcnew System::EventHandler(this, &OrderMenuForm::BuyButton_Click);
			// 
			// OrderMenuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
					static_cast<System::Int32>(static_cast<System::Byte>(135)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(192, 138);
			this->Controls->Add(this->BuyButton);
			this->Controls->Add(this->EndDateLabel);
			this->Controls->Add(this->StartDateLabel);
			this->Controls->Add(this->YearLabel);
			this->Controls->Add(this->MonthLabel);
			this->Controls->Add(this->DayLabel);
			this->Controls->Add(this->EndYearBox);
			this->Controls->Add(this->EndMonthBox);
			this->Controls->Add(this->EndDayBox);
			this->Controls->Add(this->StartYearBox);
			this->Controls->Add(this->StartMonthBox);
			this->Controls->Add(this->StartDayBox);
			this->Controls->Add(this->InfoLabel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"OrderMenuForm";
			this->Text = L"Бронь";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BuyButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (m_role == BlackLine::User::ADMIN)
		{
			BlackLine::InputHandler startDay{ this->StartDayBox->Text };
			BlackLine::InputHandler startMonth{ this->StartMonthBox->Text };
			BlackLine::InputHandler startYear{ this->StartYearBox->Text };
			BlackLine::InputHandler endDay{ this->EndDayBox->Text };
			BlackLine::InputHandler endMonth{ this->EndMonthBox->Text };
			BlackLine::InputHandler endYear{ this->EndYearBox->Text };

			try
			{
				if (BlackLine::EditOrder(*m_parent->m_parent->m_roomStorage,
					*m_parent->m_parent->m_orderStorage,
					m_parent->m_index, System::UInt32::Parse(m_parent->OrderNumericUpDown->Text),
					startDay.GetDay(), startMonth.GetMonth(), startYear.GetYear(),
					endDay.GetDay(), endMonth.GetMonth(), endYear.GetYear()))
				{
					BlackLine::RemoveOutdatedOrders(*m_parent->m_parent->m_orderStorage,
						*m_parent->m_parent->m_roomStorage,
						*m_parent->m_parent->m_userStorage, "Orders log.txt");

					size_t numberOfOrders{};
					m_parent->BookedTimeRichTextBox->Text = gcnew
						System::String(BlackLine::FindOrdersWithUsers(*m_parent->m_parent->m_roomStorage,
						*m_parent->m_parent->m_orderStorage,
							*m_parent->m_parent->m_userStorage, m_parent->m_index,
							numberOfOrders).c_str());
					m_parent->OrderNumericUpDown->Maximum = numberOfOrders;
					if (numberOfOrders == 0)
					{
						m_parent->OrderNumericUpDown->Minimum = 0;
						m_parent->OrderNumericUpDown->Enabled = false;
						m_parent->EditOrderButton->Enabled = false;
						m_parent->DeleteOrderButton->Enabled = false;
					}

					m_parent->m_parent->NumbersRichTextBox->Text = gcnew
						System::String(BlackLine::ShowRoomList(*m_parent->m_parent->m_roomStorage,
						*m_parent->m_parent->m_orderStorage, true).c_str());

					MessageBox::Show("Заказ успешно изменен", "Заказ изменен",
						MessageBoxButtons::OK, MessageBoxIcon::Information);

					this->Close();
				}
				else
				{
					MessageBox::Show("В введенной дате конец идет раньше начала, попробуйте еще раз",
						"Невозможная дата", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			catch (BlackLine::InputException& exception)
			{
				MessageBox::Show(exception.GetMessage(), exception.GetCaption(),
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		else if (m_role == BlackLine::User::CLIENT)
		{
			BlackLine::InputHandler startDay{ this->StartDayBox->Text };
			BlackLine::InputHandler startMonth{ this->StartMonthBox->Text };
			BlackLine::InputHandler startYear{ this->StartYearBox->Text };
			BlackLine::InputHandler endDay{ this->EndDayBox->Text };
			BlackLine::InputHandler endMonth{ this->EndMonthBox->Text };
			BlackLine::InputHandler endYear{ this->EndYearBox->Text };

			short buyCode = -1;
			try
			{
				buyCode = BlackLine::BuyNumber(*m_parent->m_parent->m_roomStorage,
					*m_parent->m_parent->m_orderStorage,
					m_parent->m_index, System::UInt32::Parse(m_parent->OrderNumericUpDown->Text),
					startDay.GetDay(), startMonth.GetMonth(), startYear.GetYear(),
					endDay.GetDay(), endMonth.GetMonth(), endYear.GetYear(),
					m_parent->m_parent->m_authorizedId);
			}
			catch (BlackLine::InputException& exception)
			{
				MessageBox::Show(exception.GetMessage(), exception.GetCaption(),
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			switch (buyCode)
			{
			case 1:
				MessageBox::Show("В введенной дате конец идет раньше начала, попробуйте еще раз",
					"Невозможная дата", MessageBoxButtons::OK, MessageBoxIcon::Error);
				break;
			case 2:
				MessageBox::Show("Введенная дата частично или полностью устарела, выберите другую",
					"Устаревший заказ", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				break;
			case 3:
				MessageBox::Show("Введенная бронь пересекается с другой, выберите другую",
					"Время занято", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				break;
			}

			if (buyCode == 0)
			{
				m_parent->m_parent->NumbersRichTextBox->Text = gcnew
					System::String(BlackLine::ShowRoomList(*m_parent->m_parent->m_roomStorage,
					*m_parent->m_parent->m_orderStorage, true).c_str());

				MessageBox::Show("Заказ успешно оформлен", "Номер заказан",
					MessageBoxButtons::OK, MessageBoxIcon::Information);

				this->Close();
			}
		}
	}
	};
}