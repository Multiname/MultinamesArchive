#include <iostream>
#include "Refresh.h"
using namespace std;

struct time
{
	int hours;
	int minutes;
	int seconds;
};

void next_sec(time t, time& t1, int d);
void error(const char field[]);

void problem1()
{
	char res = '0';
	while (res == '0')
	{
		refresh("СЛЕД_СЕК");
		time t;
		cout << "Введите час: ";
		cin >> t.hours;
		if (t.hours >= 0 && t.hours < 24)
		{
			cout << "Введите минуту: ";
			cin >> t.minutes;
			if (t.minutes >= 0 && t.minutes < 60)
			{
				cout << "Введите секунду: ";
				cin >> t.seconds;
				if (t.seconds >= 0 && t.seconds < 60)
				{
					cout << "Введите, на сколько секунд нужно перевести время: ";
					int offset{};
					cin >> offset;
					next_sec(t, t, offset);
					cout << "Переведенное время: " << t.hours << ":" << t.minutes << ":" << t.seconds << endl << endl;
					cout << "Введите 0, если хотите запустить программу еще раз: ";
					cin.ignore(32767, '\n');
					cin.get(res);
					if (res == '0')
					{
						cin.get(res);
						if (res != '\n')
						{
							res = '1';
						}
						else
						{
							res = '0';
						}
					}
					else if (res != '\n')
					{
						cin.ignore(32767, '\n');
					}
				}
				else
				{
					error("секунды");
				}
			}
			else
			{
				error("минуты");
			}
		}
		else
		{
			error("часа");
		}
	}
}

void next_sec(time t, time& t1, int d)
{
	t1.seconds = t.seconds + d;

	while (t1.seconds > 59)
	{
		t1.seconds -= 60;
		t1.minutes++;
	}
	while (t1.seconds < 0)
	{
		t1.seconds += 60;
		t1.minutes--;
	}

	while (t1.minutes > 59)
	{
		t1.minutes -= 60;
		t1.hours++;
	}
	while (t1.minutes < 0)
	{
		t1.minutes += 60;
		t1.hours--;
	}

	while (t1.hours > 23)
	{
		t1.hours -= 24;
	}
	while (t1.hours < 0)
	{
		t1.hours += 24;
	}
}

void error(const char field[])
{
	cout << "Ошибка ввода " << field << ", попробуйте еще раз ";
	char buf{};
	cin.get(buf);
	cin.ignore(32767, '\n');
}