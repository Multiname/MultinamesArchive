#include "NumbersMenu.h"
#include <Windows.h>
#include "ShowNumber.h"
#include "ChooseRoom.h"
#include "LogInForm.h"
#include "CreateNewNumber.h"
#include "ShowUsersForm.h"
#include "ProfileForm.h"

using namespace Project8;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew NumbersMenu);
    return 0;
}

System::Void NumbersMenu::ChooseNumberButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (BlackLine::FindIndex(*m_roomStorage, UINT16::Parse(ChooseNumberNumericUpDown->Text)) != -1)
    {
        ShowNumber^ form = gcnew ShowNumber(this);
        form->ShowDialog(this);
    }
    else
    {
        MessageBox::Show("Выбранный номер не найден", "Не найдено",
            MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
    }
}

System::Void NumbersMenu::LogInToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    if (m_isAuthorized == false)
    {
        LogInForm^ form = gcnew LogInForm(this);
        form->ShowDialog(this);
    }
}

System::Void NumbersMenu::AddNumberToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    CreateNewNumber^ form = gcnew CreateNewNumber(this);
    form->ShowDialog(this);
}

System::Void NumbersMenu::UserToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
    size_t index{};
    for (size_t i{}; i < m_userStorage->GetSize(); ++i)
    {
        if (m_userStorage->operator[](i).id == m_authorizedId)
        {
            index = i;
            break;
        }
    }

    if (m_userStorage->operator[](index).role == BlackLine::User::ADMIN)
    {
        ShowUsersForm^ form = gcnew ShowUsersForm(this);
        form->ShowDialog(this);
    }
    else if (m_userStorage->operator[](index).role == BlackLine::User::CLIENT)
    {
        ProfileForm^ form = gcnew ProfileForm(this);
        form->ShowDialog(this);
    }
}