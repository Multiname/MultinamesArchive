//??? ???? ????? ?????, ?????????? ?? ?????? ???? ?????? ?????
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;

const char path1[] = "s1.dat";
const char path2[] = "s2.dat";
const char path3[] = "file1.txt";
const char path4[] = "file2.txt";
const int MAXLEN = 255;

void minusone(ifstream& in);

void m111ain()
{
	int n = 0;

	srand(time(0));
	
	cout << "size: ";
	int size = 0;
	cin >> size;

	cout << "rand: ";
	ofstream out(path1, ios::binary);
	fstream file3(path3, ios::out);
	for (int i = 0; i < size; i++)
	{
		n = rand();
		cout << n << " ";
		out.write((char*)&n, sizeof(n));
		file3 << n << " ";
	}
	out.close();
	file3.close();
	cout << endl;

	cout << "even: ";
	ifstream in(path1, ios::binary);
	out.open(path2, ios::binary);
	while (in.tellg() != -1)
	{
		in.read((char*)&n, sizeof(n));
		if (n % 2 == 0)
		{
			cout << n << " ";
			out.write((char*)&n, sizeof(n));
		}
		minusone(in);
	}
	out.close();
	in.close();
	cout << endl;

	cout << "output:";
	in.open(path2, ios::binary);
	minusone(in);
	while (in)
	{
		in.read((char*)&n, sizeof(n));
		cout << n << " ";
		minusone(in);
	}
	in.close();
	cout << endl;


	
	file3.open(path3);
	fstream file4(path4, ios::out);
	char* num = new char[MAXLEN] {};
	file3.getline(num, MAXLEN, ' ');
	while (!file3.eof())
	{
		if (atoi(num) % 2 == 0)
		{
			file4 << num << ' ';
		}
		file3.getline(num, MAXLEN, ' ');
	}
	delete[] num;
	
}

void minusone(ifstream &in)
{
	int n;
	in.read((char*)&n, sizeof(n));
	if (in.tellg() != -1)
	{
		int x = sizeof(n);
		in.seekg(-x, ios::cur);
	}
}