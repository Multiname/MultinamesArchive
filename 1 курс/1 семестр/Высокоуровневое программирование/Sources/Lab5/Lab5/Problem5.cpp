#include <iostream>
#include <fstream>
using namespace std;

const int MAXLEN = 255;

void problem5()
{
	cout << "\tЧисла в файле" << endl << endl;

	char* middle = new char[MAXLEN] {};
	int n = 0;
	fstream file;
	file.open("numbers.txt");
	while (!file.eof())
	{
		file >> middle;
		n++;
	}
	file.close();
	file.open("numbers.txt");
	if (n % 2 == 0)
	{
		file >> middle;
		cout << "Кол-во чисел четное, первое число: " << middle << endl;
	}
	else
	{
		n /= 2;
		for (int i = 0; i < n; i++)
		{
			file >> middle;
		}
		file >> middle;
		cout << "Кол-во чисел нечетное, среднее число: " << middle << endl;
	}
	char buf{};
	cin.get(buf);
	if (buf != '\n')
	{
		cin.ignore(32767, '\n');
	}
}