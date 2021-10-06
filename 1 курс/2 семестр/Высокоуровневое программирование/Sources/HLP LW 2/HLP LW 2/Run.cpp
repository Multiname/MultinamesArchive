#include "CMenu.h"
#include "Users.h"
#include "User.h"
#include "Format.h"
#include "NewUser.h"
#include "LogIn.h"
#include "ItemWithMenu.h"
#include <iostream>

using namespace KMK;

int NewUserFunction();
int FormatFunction();
int UserFunction();
int LogInFunction();

int main()
{
	//NewUser* newUser = &NewUser((char*)"Create new user", &NewUserFunction);
	//Format* format = &Format((char*)"Format", &FormatFunction);
	User user_1 = User((char*)"User 1", &UserFunction);
	User user_2 = User((char*)"User 2", &UserFunction);
	User user_3 = User((char*)"User 3", &UserFunction);
	User* userList = new User[3]{user_1, user_2, user_3};

	//Users* users = &Users((char*)"Users", userList, 3, newUser, format);
	

	ItemWithMenu users = ItemWithMenu((char*)"Users", userList, 3, FormatFunction);
	LogIn logIn = LogIn((char*)"Log in", &LogInFunction);

	ItemMenu* items = new ItemMenu[2]{ users, logIn };

	CMenu menu = CMenu((char*)"Chat Bot", items, 2);

	//menu.runCommand();
	//ItemMenu** ptr = new ItemMenu * [2]{ &users, &logIn };
	//ptr[0]->run();

	std::cout << sizeof(short);

	return 0;
}

int NewUserFunction()
{
	std::cout << "New user created\n";
	return 0;
}

int FormatFunction()
{
	std::cout << "List sorted\n";
	return 0;
}

int UserFunction()
{
	std::cout << "User info\n";
	return 0;
}

int LogInFunction()
{
	std::cout << "Logged in\n";
	return 0;
}