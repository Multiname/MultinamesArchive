#include "NumbersMenu.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Project8::NumbersMenu numbersMenu;
	Application::Run(% numbersMenu);
}