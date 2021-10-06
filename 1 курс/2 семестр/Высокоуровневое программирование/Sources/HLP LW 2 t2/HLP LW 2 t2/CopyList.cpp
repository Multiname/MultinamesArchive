#include "CopyList.h"

using namespace KMK;

Dialogue** KMK::CopyList(Dialogue** list, size_t size)
{
	Dialogue** temp = new Dialogue * [size];
	for (Iteration i{}; i < size; ++i)
	{
		temp[i] = new Dialogue{ *list[i] };
	}
	return temp;
}

Interest** KMK::CopyList(Interest** list, size_t size)
{
	Interest** temp = new Interest * [size];
	for (Iteration i{}; i < size; ++i)
	{
		temp[i] = new Interest{ *list[i] };
	}
	return temp;
}

Reminder** KMK::CopyList(Reminder** list, size_t size)
{
	Reminder** temp = new Reminder * [size];
	for (Iteration i{}; i < size; ++i)
	{
		temp[i] = new Reminder{ *list[i] };
	}
	return temp;
}

Theme** KMK::CopyList(Theme** list, size_t size)
{
	Theme** temp = new Theme * [size];
	for (Iteration i{}; i < size; ++i)
	{
		temp[i] = new Theme{ *list[i] };
	}
	return temp;
}

User** KMK::CopyList(User** list, size_t size)
{
	User** temp = new User * [size];
	for (Iteration i{}; i < size; ++i)
	{
		temp[i] = new User{ *list[i] };
	}
	return temp;
}