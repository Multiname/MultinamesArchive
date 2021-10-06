#pragma once

#include "NumbersMenu.h"
#include "ShowUserList.h"
#include "ChooseUser.h"

namespace Project8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ShowUsersForm : public System::Windows::Forms::Form
	{
	public:
		ShowUsersForm(NumbersMenu^ parent)
		{
			m_parent = parent;

			InitializeComponent();

			std::vector<std::string> text = BlackLine::ShowUserList(*m_parent->m_userStorage,
				*m_parent->m_orderStorage, *m_parent->m_roomStorage);

			for (size_t i{}; i < text.size(); ++i)
			{
				this->UsersListBox->Items->Add(gcnew System::String(text[i].c_str()));
			}

			this->UsersListBox->SelectedIndex = 0;

			if (m_parent->m_userStorage->operator[](0).role == BlackLine::User::ADMIN)
			{
				this->AdminRadioButton->Checked = true;
			}
			else if (m_parent->m_userStorage->operator[](0).role == BlackLine::User::CLIENT)
			{
				this->ClientRadioButton->Checked = true;
			}
			else if (m_parent->m_userStorage->operator[](0).role == BlackLine::User::BANNED)
			{
				this->BannedRadioButton->Checked = true;
			}

			if (m_parent->m_userStorage->operator[](0).id == m_parent->m_authorizedId)
			{
				this->RoleButton->Enabled = false;
			}
		}

	protected:
		~ShowUsersForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: NumbersMenu^ m_parent;

	private: System::Windows::Forms::RadioButton^ ClientRadioButton;
	private: System::Windows::Forms::RadioButton^ AdminRadioButton;
	private: System::Windows::Forms::RadioButton^ BannedRadioButton;
	private: System::Windows::Forms::Button^ RoleButton;
	private: System::Windows::Forms::Label^ UsersLabel;
	private: System::Windows::Forms::ListBox^ UsersListBox;
	private: System::Windows::Forms::Label^ RoleLabel;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources =
				(gcnew System::ComponentModel::ComponentResourceManager(ShowUsersForm::typeid));
			this->ClientRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->AdminRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->BannedRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->RoleButton = (gcnew System::Windows::Forms::Button());
			this->UsersLabel = (gcnew System::Windows::Forms::Label());
			this->UsersListBox = (gcnew System::Windows::Forms::ListBox());
			this->RoleLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// ClientRadioButton
			// 
			this->ClientRadioButton->AutoSize = true;
			this->ClientRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->ClientRadioButton->Location = System::Drawing::Point(301, 28);
			this->ClientRadioButton->Name = L"ClientRadioButton";
			this->ClientRadioButton->Size = System::Drawing::Size(61, 17);
			this->ClientRadioButton->TabIndex = 1;
			this->ClientRadioButton->TabStop = true;
			this->ClientRadioButton->Text = L"Клиент";
			this->ClientRadioButton->UseVisualStyleBackColor = true;
			// 
			// AdminRadioButton
			// 
			this->AdminRadioButton->AutoSize = true;
			this->AdminRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->AdminRadioButton->Location = System::Drawing::Point(301, 51);
			this->AdminRadioButton->Name = L"AdminRadioButton";
			this->AdminRadioButton->Size = System::Drawing::Size(104, 17);
			this->AdminRadioButton->TabIndex = 2;
			this->AdminRadioButton->TabStop = true;
			this->AdminRadioButton->Text = L"Администратор";
			this->AdminRadioButton->UseVisualStyleBackColor = true;
			// 
			// BannedRadioButton
			// 
			this->BannedRadioButton->AutoSize = true;
			this->BannedRadioButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->BannedRadioButton->Location = System::Drawing::Point(301, 74);
			this->BannedRadioButton->Name = L"BannedRadioButton";
			this->BannedRadioButton->Size = System::Drawing::Size(98, 17);
			this->BannedRadioButton->TabIndex = 3;
			this->BannedRadioButton->TabStop = true;
			this->BannedRadioButton->Text = L"Заблокирован";
			this->BannedRadioButton->UseVisualStyleBackColor = true;
			// 
			// RoleButton
			// 
			this->RoleButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->RoleButton->ForeColor =
				System::Drawing::SystemColors::ButtonHighlight;
			this->RoleButton->Location = System::Drawing::Point(301, 97);
			this->RoleButton->Name = L"RoleButton";
			this->RoleButton->Size = System::Drawing::Size(104, 23);
			this->RoleButton->TabIndex = 4;
			this->RoleButton->Text = L"Изменить роль";
			this->RoleButton->UseVisualStyleBackColor = false;
			this->RoleButton->Click +=
				gcnew System::EventHandler(this, &ShowUsersForm::RoleButton_Click);
			// 
			// UsersLabel
			// 
			this->UsersLabel->AutoSize = true;
			this->UsersLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->UsersLabel->Location = System::Drawing::Point(118, 9);
			this->UsersLabel->Name = L"UsersLabel";
			this->UsersLabel->Size = System::Drawing::Size(80, 13);
			this->UsersLabel->TabIndex = 4;
			this->UsersLabel->Text = L"Пользователи";
			// 
			// UsersListBox
			// 
			this->UsersListBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->UsersListBox->ForeColor = System::Drawing::Color::Navy;
			this->UsersListBox->FormattingEnabled = true;
			this->UsersListBox->Location = System::Drawing::Point(12, 25);
			this->UsersListBox->Name = L"UsersListBox";
			this->UsersListBox->Size = System::Drawing::Size(283, 95);
			this->UsersListBox->TabIndex = 0;
			this->UsersListBox->SelectedValueChanged +=
				gcnew System::EventHandler(this, &ShowUsersForm::UsersListBox_SelectedValueChanged);
			// 
			// RoleLabel
			// 
			this->RoleLabel->AutoSize = true;
			this->RoleLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->RoleLabel->Location = System::Drawing::Point(343, 9);
			this->RoleLabel->Name = L"RoleLabel";
			this->RoleLabel->Size = System::Drawing::Size(32, 13);
			this->RoleLabel->TabIndex = 8;
			this->RoleLabel->Text = L"Роль";
			// 
			// ShowUsersForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor =
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
					static_cast<System::Int32>(static_cast<System::Byte>(135)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(417, 132);
			this->Controls->Add(this->RoleLabel);
			this->Controls->Add(this->UsersListBox);
			this->Controls->Add(this->UsersLabel);
			this->Controls->Add(this->RoleButton);
			this->Controls->Add(this->BannedRadioButton);
			this->Controls->Add(this->ClientRadioButton);
			this->Controls->Add(this->AdminRadioButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"ShowUsersForm";
			this->Text = L"Список пользователей";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void RoleButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		BlackLine::User::Role role{};

		if (this->AdminRadioButton->Checked)
		{
			role = BlackLine::User::ADMIN;
		}
		else if (this->ClientRadioButton->Checked)
		{
			role = BlackLine::User::CLIENT;
		}
		else if (this->BannedRadioButton->Checked)
		{
			role = BlackLine::User::BANNED;
		}

		BlackLine::ChangeRole(*m_parent->m_userStorage, this->UsersListBox->SelectedIndex, role);
		MessageBox::Show("Роль успешно изменена", "Роль изменена",
			MessageBoxButtons::OK, MessageBoxIcon::Information);
	}

	private: System::Void UsersListBox_SelectedValueChanged(System::Object^ sender,
		System::EventArgs^ e)
	{
		if (m_parent->m_userStorage->operator[](this->UsersListBox->SelectedIndex).role ==
			BlackLine::User::ADMIN)
		{
			this->AdminRadioButton->Checked = true;
		}
		else if (m_parent->m_userStorage->operator[](this->UsersListBox->SelectedIndex).role ==
			BlackLine::User::CLIENT)
		{
			this->ClientRadioButton->Checked = true;
		}
		else if (m_parent->m_userStorage->operator[](this->UsersListBox->SelectedIndex).role ==
			BlackLine::User::BANNED)
		{
			this->BannedRadioButton->Checked = true;
		}

		if (m_parent->m_userStorage->operator[](this->UsersListBox->SelectedIndex).id ==
			m_parent->m_authorizedId)
		{
			this->RoleButton->Enabled = false;
		}
		else
		{
			this->RoleButton->Enabled = true;
		}
	}
	};
}