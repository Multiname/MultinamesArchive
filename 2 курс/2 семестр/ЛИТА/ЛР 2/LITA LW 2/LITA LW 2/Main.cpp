#include <vector>
#include <iostream>
#include <random>
#include <time.h>
#include <iomanip>
#include <fstream>

const int MinimumPossibleNumber = 0;
const int maximumPossibleNumber = 9;

using namespace std;

//vector<int> LCS_2(vector<int> a, vector<int> b)
//{
//	int* prev = new int[a.size()]{};
//	for (int i{}; i < a.size(); ++i)
//		prev[i] = -1;
//
//	int** d = new int* [a.size()] {};
//	for (int i{}; i < a.size(); ++i)
//		d[i] = new int[b.size()]{};
//
//	for (int i{}; i < a.size(); ++i)
//		for (int j{}; j < b.size(); ++j)
//			if (a[i] == b[j])
//			{
//				d[i][j] = 1;
//				for (int k{}; k < i; ++k)
//					for (int l{}; l < j; ++l)
//						if (a[k] == b[l] &&
//							a[k] < a[i] &&
//							d[i][j] < d[k][l] + 1)
//						{
//							d[i][j] = d[k][l] + 1;
//							prev[i] = k;
//						}
//			}
//
//	int b_i = 1;
//	int b_j = 1;
//	for (int i{}; i < a.size(); ++i)
//		for (int j{}; j < b.size(); ++j)
//			if (d[b_i][b_j] < d[i][j])
//			{
//				b_i = i;
//				b_j = j;
//			}
//
//	int pos = b_i;
//	vector<int> answer{};
//	while (pos != -1)
//	{
//		answer.push_back(a[pos]);
//		pos = prev[pos];
//	}
//
//	return answer;
//}
//
//struct Pair
//{
//	int i{};
//	int j{};
//};
//
//Pair** LCS(vector<int> x, vector<int> y)
//{
//	auto m = x.size();
//	auto n = y.size();
//
//	int** lcs = new int* [n] {};
//	Pair** prev = new Pair * [n] {};
//	for (int i{}; i < m; ++i)
//	{
//		lcs[i] = new int[m] {};
//		prev[i] = new Pair[m]{};
//	}
//
//	for (int i{}; i < m; ++i)
//		lcs[i][0] = 0;
//	for (int j{}; j < n; ++j)
//		lcs[0][j] = 0;
//
//	for (int i = 1; i < m; ++i)
//		for (int j = 1; j < n; ++j)
//			if (x[i] == y[j])
//			{
//				lcs[i][j] = lcs[i - 1][j - 1] + 1;
//				prev[i][j] = { i - 1, j - 1 };
//			}
//			else
//				if (lcs[i - 1][j] >= lcs[i][j - 1])
//				{
//					lcs[i][j] = lcs[i - 1][j];
//					prev[i][j] = { i - 1, j };
//				}
//				else
//				{
//					lcs[i][j] = lcs[i][j - 1];
//					prev[i][j] = { i, j - 1 };
//				}
//
//	return prev;
//}
//
//void printLCS(int i, int j, Pair** prev, vector<int> x)
//{
//	if (i == 0 || j == 0)
//		return;
//	if (prev[i][j].i == i - 1 && prev[i][j].j == j - 1)
//	{
//		printLCS(i - 1, j - 1, prev, x);
//		cout << x[i] << " ";
//	}
//	else
//		if (prev[i][j].i == i - 1 && prev[i][j].j == j)
//			printLCS(i - 1, j, prev, x);
//		else
//			printLCS(i, j - 1, prev, x);
//}

//int LCIS(vector<int> arr1, vector<int> arr2)
//{
//	int n = arr1.size();
//	int m = arr2.size();
//
//	// table[j] is going to store length of LCIS
//	// ending with arr2[j]. We initialize it as 0,
//	int *table = new int[m];
//	for (int j = 0; j < m; j++)
//		table[j] = 0;
//
//	// Traverse all elements of arr1[]
//	for (int i = 0; i < n; i++)
//	{
//		// Initialize current length of LCIS
//		int current = 0;
//
//		// For each element of arr1[], traverse all
//		// elements of arr2[].
//		for (int j = 0; j < m; j++)
//		{
//			// If both the array have same elements.
//			// Note that we don't break the loop here.
//			if (arr1[i] == arr2[j])
//				if (current + 1 > table[j])
//					table[j] = current + 1;
//
//			/* Now seek for previous smaller common
//			   element for current element of arr1 */
//			if (arr1[i] > arr2[j])
//				if (table[j] > current)
//					current = table[j];
//		}
//	}
//
//	// The maximum value in table[] is out result
//	int result = 0;
//	for (int i = 0; i < m; i++)
//		if (table[i] > result)
//			result = table[i];
//
//	return result;
//}

void LCS(vector<int> X, vector<int> Y, char**& s)
{
	int n = X.size();
	int m = Y.size();

	int** c = new int* [n + 1]{};
	int** v = new int* [n + 1]{};
	for (int i{}; i < n + 1; ++i)
	{
		c[i] = new int[m + 1]{};
		v[i] = new int[m + 1]{ MinimumPossibleNumber - 1 };
	}
	for (int i{}; i < m; ++i)
		v[0][i + 1] = MinimumPossibleNumber - 1;

	s = new char* [n] {};
	for (int i{}; i < n; ++i)
		s[i] = new char[m] {};

	for (int i = 1; i < n + 1; ++i)
		for (int j = 1; j < m + 1; ++j)
		{
			if (X[i - 1] == Y[j - 1] && v[i - 1][j - 1] <= X[i - 1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				v[i][j] = X[i - 1];
				s[i - 1][j - 1] = '\\';
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				v[i][j] = v[i - 1][j];
				s[i - 1][j - 1] = '|';
			}
			else
			{
				c[i][j] = c[i][j - 1];
				v[i][j] = v[i][j - 1];
				s[i - 1][j - 1] = '-';
			}
		}

	for (int i{}; i < n + 1; ++i)
	{
		delete[] c[i];
		delete[] v[i];
	}
	delete[] c;
	delete[] v;
}

int LCS(vector<int> X, vector<int> Y, int i, int j,
	int**& c, char**& s, int& prev)
{
	if (i < 0 || j < 0)
	{
		prev = MinimumPossibleNumber - 1;
		return 0;
	}

	bool isReached = false;
	if (X[i] == Y[j])
	{
		int prevToReturn{};
		int temp = LCS(X, Y, i - 1, j - 1, c, s, prevToReturn) + 1;
		if (prevToReturn <= X[i])
		{
			c[i][j] = temp;
			s[i][j] = '\\';
			prev = X[i];
			isReached = true;
		}
	}

	if (!isReached)
	{
		int prev_1 = prev;
		int m_1 = LCS(X, Y, i - 1, j, c, s, prev_1);

		int prev_2 = prev;
		int m_2 = LCS(X, Y, i, j - 1, c, s, prev_2);

		if (m_1 >= m_2)
		{
			c[i][j] = m_1;
			prev = prev_1;
			s[i][j] = '|';
		}
		else
		{
			c[i][j] = m_2;
			prev = prev_2;
			s[i][j] = '-';
		}
	}

	return c[i][j];
}

void Recursion()
{
	vector<vector<clock_t>> times{};

	for (int n = 7; n < 12; ++n)
	{
		vector<clock_t> subtimes{};
		for (int m = 7; m < 12; ++m)
		{
			vector<int> a{};
			vector<int> b{};
			int** c = new int* [n] {};
			char** s = new char* [n] {};
			for (int i{}; i < n; ++i)
			{
				a.push_back(MinimumPossibleNumber + rand() % (maximumPossibleNumber - MinimumPossibleNumber + 1));
				c[i] = new int[m] {};
				s[i] = new char[m] {};
				for (int j{}; j < m; ++j)
					s[i][j] = ' ';
			}
			for (int i{}; i < m; ++i)
				b.push_back(MinimumPossibleNumber + rand() % (maximumPossibleNumber - MinimumPossibleNumber + 1));

			int maxNum = maximumPossibleNumber + 1;
			clock_t start = clock();
			LCS(a, b, n - 1, m - 1, c, s, maxNum);
			clock_t end = clock();

			cout << "1st sequence: ";
			for (int i{}; i < n; ++i)
				cout << a[i] << " ";

			cout << "\n2nd sequence: ";
			for (int i{}; i < m; ++i)
				cout << b[i] << " ";

			vector<int> subsequence{};
			int i = a.size() - 1;
			int j = b.size() - 1;
			while (i >= 0 && j >= 0)
			{
				if (s[i][j] == '\\')
				{
					subsequence.push_back(a[i]);
					--i;
					--j;
				}
				else if (s[i][j] == '|')
					--i;
				else if (s[i][j] == '-')
					--j;
			}

			cout << "\nSubsequence: ";
			for (int i = subsequence.size() - 1; i >= 0; --i)
				cout << subsequence[i] << " ";

			cout << "\nTime: " << (end - start) / (CLOCKS_PER_SEC / 1000) << "\n";
			subtimes.push_back((end - start) / (CLOCKS_PER_SEC / 1000));

			for (int i{}; i < a.size(); ++i)
			{
				delete[] c[i];
				delete[] s[i];
			}
			delete[] c;
			delete[] s;
		}
		times.push_back(subtimes);
	}

	ofstream file("recursion.csv");
	for (int i{}; i < times.size(); ++i)
	{
		for (int j{}; j < times[i].size(); ++j)
		{
			cout << setw(5) << times[i][j] << " ";
			file << times[i][j];
			if (j != times[i].size() - 1)
				file << ',';
		}
		cout << "\n";
		file << '\n';
	}
	file.close();
}

void Iteration()
{
	vector<vector<clock_t>> times{};

	for (int n = 500; n < 3000; n += 500)
	{
		vector<clock_t> subtimes{};
		for (int m = 500; m < 3000; m += 500)
		{
			vector<int> a{};
			vector<int> b{};
			for (int i{}; i < n; ++i)
				a.push_back(MinimumPossibleNumber + rand() % (maximumPossibleNumber - MinimumPossibleNumber + 1));
			for (int i{}; i < m; ++i)
				b.push_back(MinimumPossibleNumber + rand() % (maximumPossibleNumber - MinimumPossibleNumber + 1));

			//cout << "1st sequence: ";
			//for (int i{}; i < n; ++i)
			//	cout << a[i] << " ";

			//cout << "\n2nd sequence: ";
			//for (int i{}; i < m; ++i)
			//	cout << b[i] << " ";

			char** s{};
			clock_t start = clock();
			LCS(a, b, s);
			clock_t end = clock();

			vector<int> subsequence{};
			int i = a.size() - 1;
			int j = b.size() - 1;
			while (i >= 0 && j >= 0)
			{
				if (s[i][j] == '\\')
				{
					subsequence.push_back(a[i]);
					--i;
					--j;
				}
				else if (s[i][j] == '|')
					--i;
				else if (s[i][j] == '-')
					--j;
			}

			//cout << "\nSubsequence: ";
			//for (int i = subsequence.size() - 1; i >= 0; --i)
			//	cout << subsequence[i] << " ";

			//cout << "\nTime: " << (end - start) / (CLOCKS_PER_SEC / 1000) << "\n\n";
			subtimes.push_back((end - start) / (CLOCKS_PER_SEC / 1000));

			for (int i{}; i < a.size(); ++i)
				delete[] s[i];
			delete[] s;
		}
		times.push_back(subtimes);
	}

	ofstream file("iteration.csv");
	for (int i{}; i < times.size(); ++i)
	{
		for (int j{}; j < times[i].size(); ++j)
		{
			cout << setw(5) << times[i][j] << " ";
			file << times[i][j];
			if (j != times[i].size() - 1)
				file << ',';
		}
		cout << "\n";
		file << '\n';
	}
	file.close();
}

int main()
{
	unsigned int seed = time(NULL);
	srand(seed);
	Recursion();

	srand(seed);
	//Iteration();

	return 0;
}

//cout << "\n";
			//for (int i{}; i < a.size(); ++i)
			//{
			//	for (int j{}; j < b.size(); ++j)
			//		cout << setw(4) << s_2[i][j] << c_2[i + 1][j + 1] << " ";
			//	cout << "\n";
			//}