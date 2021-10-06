#include <iostream>
#include <ctime>
using namespace std;

const int BOT = 30;
const int UPP = 60;
const int ARR1 = 10;
const int ARR2 = 20;

void randarr(int arr[], int len);
int getmax(int arr[], int len);
int getmin(int arr[], int len);
float getmed(int arr[], int len);

void mai112n()
{
	long double num = 459.11;
	bool* ptr = (bool*)&num;
	for (int i = 0; i < 8; i++)
	{
		cout << *((bool*)&num + i) << endl;
	}
	cout << endl;

	srand(time(0));

	int A[ARR1]{};
	randarr(A, ARR1);
	for (int j = 0; j < ARR1; j++)
	{
		cout << A[j] << " ";
	}
	cout << endl;
	cout << getmax(A, ARR1) << endl;
	cout << getmin(A, ARR1) << endl;
	cout << getmed(A, ARR1) << endl;
}

void randarr(int arr[], int len)
{
	for (int i = 0; i < len; i++)
	{
		arr[i] = rand() % (UPP - BOT + 1) + BOT;
	}
}

int getmax(int arr[], int len)
{
	int max = 0;
	for (int i = 0;  i < len; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}

int getmin(int arr[], int len)
{
	int min = UPP + 1;
	for (int i = 0; i < len; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	return min;
}

float getmed(int arr[], int len)
{
	float sum = 0;
	for (int i = 0; i < len; i++)
	{
		sum += arr[i];
	}
	return sum / len;
}