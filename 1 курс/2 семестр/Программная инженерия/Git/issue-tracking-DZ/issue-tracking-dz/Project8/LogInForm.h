#pragma once
#include "NumbersMenu.h"
#include "LogIn.h"
#include <msclr\marshal_cppstd.h>
#include "InputHandler.h"

namespace Project8 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class LogInForm : public System::Windows::Forms::Form
	{
	public:
		LogInForm(NumbersMenu^ parent)
		{
			m_parent = parent;
			InitializeComponent();
			m_registrationMode = false;
		}

	protected:
		~LogInForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: bool m_registrationMode{};
	private: NumbersMenu^ m_parent;

	private: System::Windows::Forms::Label^ FullNameLabel;
	private: System::Windows::Forms::TextBox^ NameTextBox;
	private: System::Windows::Forms::Label^ InfoLabel;
	private: System::Windows::Forms::Button^ RegistrationButton;
	private: System::Windows::Forms::TextBox^ PasswordTextBox;
	private: System::Windows::Forms::Label^ PasswordLabel;
	private: System::Windows::Forms::Label^ LoginLabel;
	private: System::Windows::Forms::TextBox^ LoginTextBox;
	private: System::Windows::Forms::Button^ LogInButton;

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources =
				(gcnew System::ComponentModel::ComponentResourceManager(LogInForm::typeid));
			this->FullNameLabel = (gcnew System::Windows::Forms::Label());
			this->NameTextBox = (gcnew System::Windows::Forms::TextBox());
			this->InfoLabel = (gcnew System::Windows::Forms::Label());
			this->RegistrationButton = (gcnew System::Windows::Forms::Button());
			this->PasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PasswordLabel = (gcnew System::Windows::Forms::Label());
			this->LoginLabel = (gcnew System::Windows::Forms::Label());
			this->LoginTextBox = (gcnew System::Windows::Forms::TextBox());
			this->LogInButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// FullNameLabel
			// 
			this->FullNameLabel->AutoSize = true;
			this->FullNameLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->FullNameLabel->Location = System::Drawing::Point(12, 35);
			this->FullNameLabel->Name = L"FullNameLabel";
			this->FullNameLabel->Size = System::Drawing::Size(29, 13);
			this->FullNameLabel->TabIndex = 22;
			this->FullNameLabel->Text = L"Имя";
			this->FullNameLabel->Visible = false;
			// 
			// NameTextBox
			// 
			this->NameTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->NameTextBox->ForeColor = System::Drawing::Color::Navy;
			this->NameTextBox->Location = System::Drawing::Point(63, 32);
			this->NameTextBox->MaxLength = 40;
			this->NameTextBox->Name = L"NameTextBox";
			this->NameTextBox->Size = System::Drawing::Size(128, 20);
			this->NameTextBox->TabIndex = 5;
			this->NameTextBox->Visible = false;
			// 
			// InfoLabel
			// 
			this->InfoLabel->AutoSize = true;
			this->InfoLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->InfoLabel->Location = System::Drawing::Point(12, 9);
			this->InfoLabel->Name = L"InfoLabel";
			this->InfoLabel->Size = System::Drawing::Size(179, 13);
			this->InfoLabel->TabIndex = 20;
			this->InfoLabel->Text = L"Введите данные для авторизации";
			this->InfoLabel->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// RegistrationButton
			// 
			this->RegistrationButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->RegistrationButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->RegistrationButton->Location = System::Drawing::Point(63, 113);
			this->RegistrationButton->Name = L"RegistrationButton";
			this->RegistrationButton->Size = System::Drawing::Size(128, 23);
			this->RegistrationButton->TabIndex = 4;
			this->RegistrationButton->Text = L"Создать новый";
			this->RegistrationButton->UseVisualStyleBackColor = false;
			this->RegistrationButton->Click +=
				gcnew System::EventHandler(this, &LogInForm::RegistrationButton_Click);
			// 
			// PasswordTextBox
			// 
			this->PasswordTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->PasswordTextBox->ForeColor = System::Drawing::Color::Navy;
			this->PasswordTextBox->Location = System::Drawing::Point(63, 58);
			this->PasswordTextBox->MaxLength = 20;
			this->PasswordTextBox->Name = L"PasswordTextBox";
			this->PasswordTextBox->Size = System::Drawing::Size(128, 20);
			this->PasswordTextBox->TabIndex = 1;
			this->PasswordTextBox->UseSystemPasswordChar = true;
			// 
			// PasswordLabel
			// 
			this->PasswordLabel->AutoSize = true;
			this->PasswordLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->PasswordLabel->Location = System::Drawing::Point(12, 61);
			this->PasswordLabel->Name = L"PasswordLabel";
			this->PasswordLabel->Size = System::Drawing::Size(45, 13);
			this->PasswordLabel->TabIndex = 17;
			this->PasswordLabel->Text = L"Пароль";
			// 
			// LoginLabel
			// 
			this->LoginLabel->AutoSize = true;
			this->LoginLabel->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->LoginLabel->Location = System::Drawing::Point(12, 35);
			this->LoginLabel->Name = L"LoginLabel";
			this->LoginLabel->Size = System::Drawing::Size(38, 13);
			this->LoginLabel->TabIndex = 16;
			this->LoginLabel->Text = L"Логин";
			// 
			// LoginTextBox
			// 
			this->LoginTextBox->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->LoginTextBox->ForeColor = System::Drawing::Color::Navy;
			this->LoginTextBox->Location = System::Drawing::Point(63, 32);
			this->LoginTextBox->MaxLength = 20;
			this->LoginTextBox->Name = L"LoginTextBox";
			this->LoginTextBox->Size = System::Drawing::Size(128, 20);
			this->LoginTextBox->TabIndex = 0;
			// 
			// LogInButton
			// 
			this->LogInButton->BackColor = System::Drawing::Color::RoyalBlue;
			this->LogInButton->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->LogInButton->Location = System::Drawing::Point(63, 84);
			this->LogInButton->Name = L"LogInButton";
			this->LogInButton->Size = System::Drawing::Size(128, 23);
			this->LogInButton->TabIndex = 3;
			this->LogInButton->Text = L"Войти в аккаунт";
			this->LogInButton->UseVisualStyleBackColor = false;
			this->LogInButton->Click += gcnew System::EventHandler(this, &LogInForm::LogInButton_Click);
			// 
			// LogInForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)),
				static_cast<System::Int32>(static_cast<System::Byte>(135)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->ClientSize = System::Drawing::Size(203, 177);
			this->Controls->Add(this->FullNameLabel);
			this->Controls->Add(this->NameTextBox);
			this->Controls->Add(this->InfoLabel);
			this->Controls->Add(this->RegistrationButton);
			this->Controls->Add(this->PasswordTextBox);
			this->Controls->Add(this->PasswordLabel);
			this->Controls->Add(this->LoginLabel);
			this->Controls->Add(this->LoginTextBox);
			this->Controls->Add(this->LogInButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"LogInForm";
			this->Text = L"Вход";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	private: System::Void RegistrationButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->NameTextBox->Text = "";
		this->LoginTextBox->Text = "";
		this->PasswordTextBox->Text = "";

		if (m_registrationMode == false)
		{
			this->PasswordTextBox->UseSystemPasswordChar = false;

			this->LoginLabel->Location = System::Drawing::Point(12, 61);
			this->PasswordLabel->Location = System::Drawing::Point(12, 87);

			this->LoginTextBox->Location = System::Drawing::Point(63, 58);
			this->PasswordTextBox->Location = System::Drawing::Point(63, 84);

			this->LogInButton->Location = System::Drawing::Point(63, 113);
			this->RegistrationButton->Location = System::Drawing::Point(63, 142);

			this->FullNameLabel->Visible = true;
			this->NameTextBox->Visible = true;

			this->InfoLabel->Text = L"Введите данные для регистрации";

			this->LogInButton->Text = L"Зарегистрироваться";
			this->RegistrationButton->Text = L"Отмена";

			m_registrationMode = true;
		}
		else
		{
			this->PasswordTextBox->UseSystemPasswordChar = true;

			this->LoginLabel->Location = System::Drawing::Point(12, 35);
			this->PasswordLabel->Location = System::Drawing::Point(12, 61);

			this->LoginTextBox->Location = System::Drawing::Point(63, 32);
			this->PasswordTextBox->Location = System::Drawing::Point(63, 58);

			this->LogInButton->Location = System::Drawing::Point(63, 84);
			this->RegistrationButton->Location = System::Drawing::Point(63, 113);

			this->FullNameLabel->Visible = false;
			this->NameTextBox->Visible = false;

			this->InfoLabel->Text = L"Введите данные для авторизации";

			this->LogInButton->Text = L"Войти в аккаунт";
			this->RegistrationButton->Text = L"Создать новый";

			m_registrationMode = false;
		}
	}

	private: System::Void LogInButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (m_registrationMode == false)
		{
			BlackLine::InputHandler loginInput{ this->LoginTextBox->Text };
			BlackLine::InputHandler passwordInput{ this->PasswordTextBox->Text };
			unsigned long id = 0;
			try
			{
				std::string login = loginInput.GetLogin();
				std::string password = passwordInput.GetPassword();
				id = BlackLine::LogIn(*m_parent->m_userStorage, login, password);
			}
			catch (BlackLine::InputException& exception)
			{
				MessageBox::Show(exception.GetMessage(), exception.GetCaption(),
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}

			if (id != 0)
			{
				m_parent->m_authorizedId = id;
				BlackLine::User::Role role{};
				for (size_t i{}; i < m_parent->m_userStorage->GetSize(); ++i)
				{
					if (id == m_parent->m_userStorage->operator[](i).id)
					{
						role = m_parent->m_userStorage->operator[](i).role;
						if (role == BlackLine::User::BANNED)
						{
							break;
						}
						m_parent->LogInToolStripMenuItem->Text = gcnew
							System::String(("Вы вошли как " + m_parent->m_userStorage->operator[](i).fullName).c_str());
						break;
					}
				}
				if (role != BlackLine::User::BANNED)
				{
					m_parent->m_isAuthorized = true;
					m_parent->UserToolStripMenuItem->Visible = true;
					m_parent->LogOutToolStripMenuItem->Visible = true;

					if (role == BlackLine::User::ADMIN)
					{
						m_parent->UserToolStripMenuItem->Text = "Пользователи";
						m_parent->AddNumberToolStripMenuItem->Visible = true;
					}
					else if (role == BlackLine::User::CLIENT)
					{
						m_parent->UserToolStripMenuItem->Text = "Личный кабинет";
					}
				}
				else
				{
					MessageBox::Show("По каким-то причинам ваш аккаунт был удален или заблокирован",
						"Аккаунт удален", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}

				this->Close();
			}
			else
			{
				MessageBox::Show("Пользователь с введенными данными не найден", "Аккаунт не найден",
					MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
			}
		}
		else
		{
			BlackLine::InputHandler nicknameInput{ this->NameTextBox->Text };
			BlackLine::InputHandler loginInput{ this->LoginTextBox->Text };
			BlackLine::InputHandler passwordInput{ this->PasswordTextBox->Text };
			try
			{
				std::string nickname = nicknameInput.GetNickname();
				std::string login = loginInput.GetLogin();
				std::string password = passwordInput.GetPassword();

				if (BlackLine::Register(*m_parent->m_userStorage, nickname, login, password))
				{
					unsigned long id = BlackLine::LogIn(*m_parent->m_userStorage,
						msclr::interop::marshal_as<std::string>(this->LoginTextBox->Text),
						msclr::interop::marshal_as<std::string>(this->PasswordTextBox->Text));
					m_parent->m_authorizedId = id;

					MessageBox::Show("Новый аккаунт успешно создан", "Аккаунт создан",
						MessageBoxButtons::OK, MessageBoxIcon::Information);

					m_parent->UserToolStripMenuItem->Visible = true;
					m_parent->LogOutToolStripMenuItem->Visible = true;
					m_parent->UserToolStripMenuItem->Text = "Личный кабинет";
					m_parent->LogInToolStripMenuItem->Text = gcnew System::String(("Вы вошли как " +
						msclr::interop::marshal_as<std::string>(this->NameTextBox->Text)).c_str());
					m_parent->m_isAuthorized = true;

					this->Close();
				}
				else
				{
					MessageBox::Show("Пользователь с таким логином уже существует, воспользуйтесь другим", "Логин занят",
						MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
				}
			}
			catch (BlackLine::InputException& exception)
			{
				MessageBox::Show(exception.GetMessage(), exception.GetCaption(),
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	};
}