#include "LogInItem.h"
#include "Constants.h"
#include <iostream>

using namespace KMK;

LogInItem::LogInItem(char* itemName, char* tempDataBase, char* dataBase) : MenuItem(itemName)
{
	m_tempDataBase = new char[LENGTH_OF_FIELD];
	strcpy_s(m_tempDataBase, LENGTH_OF_FIELD, tempDataBase);
	m_dataBase = new char[LENGTH_OF_FIELD]; 
	strcpy_s(m_dataBase, LENGTH_OF_FIELD, dataBase);
}

int LogInItem::Run()
{
	std::cout << "Enter login and password...\n";
	std::cout << "What data do you want to change?..\n";

	return 1;
}