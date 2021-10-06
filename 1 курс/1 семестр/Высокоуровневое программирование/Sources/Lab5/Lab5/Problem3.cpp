#include <iostream>
using namespace std;

struct complex
{
	float real{};
	float imaginary{};
	void algebraic()
	{
		cout << "z = " << real << " + " << imaginary << "i" << endl;
	}
	void indicative()
	{
		float mod = sqrt(real * real + imaginary * imaginary);
		mod = round(mod * 100) / 100;
		float arg = atan(imaginary / real);	
		arg = round(arg * 100) / 100;
		cout << "z = " << mod << "e^" << arg << "i" << endl;
	}
};

void problem3()
{
	char res = '0';
	while (res == '0')
	{
		cout << "\tКомплексное число" << endl << endl;
		complex num;
		cout << "Введите действительную часть числа: ";
		cin >> num.real;
		cout << "Введите мнимую часть числа: ";
		cin >> num.imaginary;
		cout << "Алгебраическая форма: ";
		num.algebraic();
		cout << "Показательная форма: ";
		num.indicative();
		cout << endl << "Введите 0, если хотите запустить программу еще раз: ";
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
		system("cls");
	}
}