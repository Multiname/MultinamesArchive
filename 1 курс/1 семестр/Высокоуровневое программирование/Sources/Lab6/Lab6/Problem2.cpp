#include <iostream>
#include <fstream>
#include "MinusOne.h"
using namespace std;

const char path[]{"prob2.dat"};

void addarr();
void readarr(bool mode);

void problem2()
{
	cout << "\t�������" << endl << endl;

	int code = 0;
	while (code != 3)
	{
		cout << "   0. �������� ������" << endl
			<< "   1. ������ ����� �������" << endl
			<< "   2. ������ ���������� �������" << endl
			<< "   3. �����" << endl << endl
			<< "������� ���: ";
		cin >> code;
		system("cls");
		cout << "\t�������" << endl << endl;
		switch (code)
		{
		case 0:
			addarr();
			break;
		case 1:
			readarr(false);
			break;
		case 2:
			readarr(true);
			break;
		}
	}
}

void addarr()
{
	int len{};
	ofstream file(path, ios::binary | ios::app);
	cout << "������� ����� �������: ";
	cin >> len;
	file.write((char*)&len, sizeof(len));

	cout << "������� ��������:" << endl;
	for (int i = 0; i < len; i++)
	{
		int num{};
		cout << i << ". ";
		cin >> num;
		file.write((char*)&num, sizeof(num));
	}
	cout << endl;
	file.close();
}

void readarr(bool mode)
{
	cout << "������� ���������� ����� �������: ";
	int num{};
	cin >> num;
	if (num < 0)
	{
		cout << "������������ �����" << endl;
	}
	else
	{
		ifstream file(path, ios::binary);
		int i = 0;
		minusone(file);
		while (file.tellg() != -1 && i < num)
		{
			int len{};
			file.read((char*)&len, sizeof(len));
			file.seekg(len*sizeof(int), ios_base::cur);
			i++;
			minusone(file);
		}
		if (file.tellg() != -1 && i == num)
		{
			int len{};
			file.read((char*)&len, sizeof(len));
			if (mode == false)
			{
				cout << "����� " << i << "-�� �������: " << len << endl;
			}
			else
			{
				for (int j = 0; j < len; j++)
				{
					int elem{};
					file.read((char*)&elem, sizeof(elem));
					cout << j << ". " << elem << endl;
				}
			}
		}
		else
		{
			cout << "������ �� ������" << endl;
		}
		cout << endl;
		file.close();
	}
}