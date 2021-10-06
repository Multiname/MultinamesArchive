#include "ShowNumber.h"
#include "OrderMenuForm.h"

using namespace Project8;

System::Void ShowNumber::EditOrderButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    OrderMenuForm^ form = gcnew OrderMenuForm(this);
    form->ShowDialog(this);
}

System::Void ShowNumber::BuyButton_Click(System::Object^ sender, System::EventArgs^ e)
{
    OrderMenuForm^ form = gcnew OrderMenuForm(this);
    form->ShowDialog(this);
}