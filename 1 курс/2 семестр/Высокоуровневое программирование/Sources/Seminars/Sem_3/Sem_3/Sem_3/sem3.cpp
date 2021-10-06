#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	cout << systemTime.wDay << '\n';
	return 0;
}

//#include <ostream>
//
//using namespace std;
//
////class Rub
////{
////public:
////	Rub(int rub)
////	{
////		m_rub = rub;
////	}
////
////	//Rub plus(Rub& rub)
////	//{
////	//	return Rub(m_rub + rub.m_rub);
////	//}
////
////	//Rub& plus(Rub& rub)
////	//{
////	//	operator+(Rub & a, Rub & b)
////	//	{
////	//		return a.plus(b);
////	//	}
////	//}
////
////	//friend Rub& operator+(Rub& a, Rub& b)
////	//{
////	//	Rub rub = Rub(a.m_rub + b.m_rub);
////	//	return rub;
////	//}
////
////	Rub& operator+(Rub& b)
////	{
////		Rub rub = Rub(this->m_rub + b.m_rub);
////		return rub;
////	}
////
////private:
////	int m_rub;
////};
//
//class String
//{
//public:
//	String();
//	explicit String(char* str);
//	String(String& string);
//	~String();
//
//	String& out(ostream& out, int a);
//
//	friend ostream& operator<<(ostream& out, String& string)
//	{
//		out << string.m_str;
//		return out;
//	}
//
//	String& operator++();
//	String& operator++(int num)
//	{
//		return *this;
//	}
//
//	bool operator==(String& string)
//	{
//		return m_length == strlen(string.m_str);
//	}
//
//	bool operator>(String& string)
//	{
//		return m_length > strlen(string.m_str);
//	}
//
//	String operator=(String& string)
//	{
//		if (this == &string)
//		{
//			return *this;
//		}
//		else
//		{
//			delete[] m_str;
//			m_str = string.m_str;
//			return *this;
//		}
//	}
//
//
//
//private:
//	char* m_str;
//	size_t m_length;
//};
//
//int main()
//{
//	//Rub a(200);
//	//Rub b(5);
//	//Rub c = a + b;
//
//
//
//	return 0;
//}