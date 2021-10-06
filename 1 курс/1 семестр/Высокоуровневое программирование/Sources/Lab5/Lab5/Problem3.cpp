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
		cout << "\t����������� �����" << endl << endl;
		complex num;
		cout << "������� �������������� ����� �����: ";
		cin >> num.real;
		cout << "������� ������ ����� �����: ";
		cin >> num.imaginary;
		cout << "�������������� �����: ";
		num.algebraic();
		cout << "������������� �����: ";
		num.indicative();
		cout << endl << "������� 0, ���� ������ ��������� ��������� ��� ���: ";
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