#include "UserItem.h"
#include "Constants.h"
#include <iostream>

using namespace KMK;

UserItem::UserItem(char* itemName, char* tempDataBase, char* Id):
	ItemWithMenu(itemName, nullptr, 0)
{
	m_tempDataBase = new char[LENGTH_OF_FIELD];
	strcpy_s(m_tempDataBase, LENGTH_OF_FIELD, tempDataBase);
	m_id = Id;
}

int UserItem::Run()
{
	//� ������� id ����� � tempDataBase ���� ������
	//�������� ������� ����� �������
	std::cout << "Change custom data\n";
	std::cout << "Change base data\n";

	return 1;
}