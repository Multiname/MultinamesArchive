#pragma once

#include "NumbersMenu.h"
#include "OpenProfile.h"

namespace Project8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ProfileForm : public System::Windows::Forms::Form
	{
	public:
		ProfileForm(NumbersMenu^ parent)
		{
			m_parent = parent;

			InitializeComponent();

			std::vector<std::string> orders = BlackLine::ShowOrders(*m_parent->m_orderStorage,
				*m_parent->m_roomStorage, m_parent->m_authorizedId);

			for (size_t i{}; i < orders.size(); ++i)
			{
				this->OrdersListBox->Items->Add(gcnew System::String(orders[i].c_str()));
			}
			if (orders.size() == 0)
			{
				this->DeleteOrderButton->Enabled = false;
			}
			else
			{
				this->OrdersListBox->SelectedIndex = 0;
			}
		}

	protected:
		~ProfileForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: NumbersMenu^ m_parent;

	private: System::Windows::Forms::Button^ DeleteOrderButton;
	private: System::Windows::Forms::Label^ OrdersLabel;
	private: System::Windows::Forms::ListBox^ OrdersListBox;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources =
				(gcnew System::ComponentModel::ComponentResourceManager(ProfileForm::typeid));
			this->DeleteOrderButton = (gcnew System::Windows::Forms::Button());
			this->OrdersLabel = (gcnew System::Windows::Forms::Label());
			this->OrdersListBox = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// DeleteOrderButton
			// 
			this->DeleteOrderButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->DeleteOrderButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->DeleteOrderButton->Location = System::Drawing::Point(78, 126);
			this->DeleteOrderButton->Name = L"DeleteOrderButton";
			this->DeleteOrderButton->Size = System::Drawing::Size(100, 23);
			this->DeleteOrderButton->TabIndex = 1;
			this->DeleteOrderButton->Text = L"Отменить бронь";
			this->DeleteOrderButton->UseVisualStyleBackColor = false;
			this->DeleteOrderButton->Click += gcnew System::EventHandler(this,
				&ProfileForm::DeleteOrderButton_Click);
			// 
			// OrdersLabel
			// 
			this->OrdersLabel->AutoSize = true;
			this->OrdersLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->OrdersLabel->Location = System::Drawing::Point(86, 9);
			this->OrdersLabel->Name = L"OrdersLabel";
			this->OrdersLabel->Size = System::Drawing::Size(83, 13);
			this->OrdersLabel->TabIndex = 3;
			this->OrdersLabel->Text = L"Список броней";
			// 
			// OrdersListBox
			// 
			this->OrdersListBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->OrdersListBox->ForeColor = System::Drawing::Color::Navy;
			this->OrdersListBox->FormattingEnabled = true;
			this->OrdersListBox->Location = System::Drawing::Point(12, 25);
			this->OrdersListBox->Name = L"OrdersListBox";
			this->OrdersListBox->Size = System::Drawing::Size(230, 95);
			this->OrdersListBox->TabIndex = 0;
			// 
			// ProfileForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
					static_cast<System::Int32>(static_cast<System::Byte>(135)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(254, 161);
			this->Controls->Add(this->OrdersListBox);
			this->Controls->Add(this->OrdersLabel);
			this->Controls->Add(this->DeleteOrderButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"ProfileForm";
			this->Text = L"Личный кабинет";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void DeleteOrderButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (MessageBox::Show("Вы уверены, что хотите отменить выбранное забронированное время?",
			"Отказ от брони", MessageBoxButtons::YesNo, MessageBoxIcon::Question,
			MessageBoxDefaultButton::Button2) != System::Windows::Forms::DialogResult::Yes) { return; }

		BlackLine::CancelOrder(*m_parent->m_orderStorage, *m_parent->m_roomStorage,
			*m_parent->m_userStorage, m_parent->m_authorizedId, this->OrdersListBox->SelectedIndex);

		m_parent->NumbersRichTextBox->Text = gcnew
			System::String(BlackLine::ShowRoomList(*m_parent->m_roomStorage,
			*m_parent->m_orderStorage, true).c_str());
		
		this->OrdersListBox->Items->Clear();
		std::vector<std::string> orders = BlackLine::ShowOrders(*m_parent->m_orderStorage,
			*m_parent->m_roomStorage, m_parent->m_authorizedId);

		for (size_t i{}; i < orders.size(); ++i)
		{
			this->OrdersListBox->Items->Add(gcnew System::String(orders[i].c_str()));
		}
		if (orders.size() == 0)
		{
			this->DeleteOrderButton->Enabled = false;
		}
		else
		{
			this->OrdersListBox->SelectedIndex = 0;
		}
	}
	};
}