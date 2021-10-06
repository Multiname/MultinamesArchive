#include <string>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

////class Point2D
////{
////public:
////	void SetPoint(int x, int y)
////	{
////		m_x = x;
////		m_y = y;
////	}
////
////	friend ostream& operator<<(ostream& out, Point2D& point)
////	{
////		out << point.m_x << " " << point.m_y;
////		return out;
////	}
////
////private:
////	size_t m_x{};
////	size_t m_y{};
////};
////
////class Creature
////{
////public:
////	void MoveTo(int x, int y)
////	{
////		m_coordinates.SetPoint(x, y);
////	}
////
////	friend ostream& operator<<(ostream& out, Creature& creature)
////	{
////		out << creature.m_name << " " << creature.m_coordinates;
////		return out;
////	}
////private:
////	Point2D m_coordinates{};
////	string m_name{};
////};
//
//class Number
//{
//public:
//	typedef long long Int;
//
//	Number() : m_value(0) {}
//	Number(Int value) : m_value(value) {}
//
//	void Print() const
//	{
//		cout << m_value;
//	}
//private:
//	Int m_value{};
//};
//
//class Fractional
//{
//public:
//	Fractional() :m_numerator(0), m_denominator(0) {}
//	Fractional(Number numerator, Number denominator) :m_numerator(numerator), m_denominator(denominator) {}
//
//	void Print() const
//	{
//		m_numerator.Print();
//		cout << " ";
//		m_denominator.Print();
//	}
//	
//private:
//	Number m_numerator{};
//	Number m_denominator{};
//};

//class Parent
//{
//public:
//	Parent(int value) : m_value(value) {}
//
//	virtual ~Parent() {}
//
//protected:
//	int m_value;
//};
//
//class Child : public Parent
//{
//public:
//	Child(int value, std::string name) : Parent(value), m_name(name) {}
//
//	const std::string& getName() { return m_name; }
//
//protected:
//	std::string m_name;
//};
//
//Parent* getObject(bool bReturnChild)
//{
//	if (bReturnChild)
//		return new Child(1, "Banana");
//	else
//		return new Parent(2);
//}
//
//int main()
//{
//	Parent* p = getObject(true);
//
//	Child* ch = dynamic_cast<Child*>(p); // используем dynamic_cast для конвертации указателя класса Parent в указатель класса Child
//
//	std::cout << "The name of the Child is: " << ch->getName() << '\n';
//
//	delete p;
//
//	return 0;
//}

//int main()
//{
//	//string a("12345");
//	//ofstream fileWrite("test.bin", std::ios::binary);
//	//size_t aSize = a.length() + 1;
//	//fileWrite.write((char*)&aSize, sizeof(size_t));
//	//fileWrite.write((char*)a.c_str(), aSize);
//	//fileWrite.close();
//
//	//string b{};
//	//ifstream fileRead("test.bin", std::ios::binary);
//	//size_t bSize{};
//	//fileRead.read((char*)&bSize, sizeof(size_t));
//	//char* str = new char[bSize] {};
//	//fileRead.read((char*)str, bSize);
//	//b = str;
//	//fileRead.close();
//
//	//cout << b << "\n";
//
//	string a("abcd");
//	string b("abcd");
//	cout << a[0] << " " << b[3] << " " << (a == b) << "\n";
//
//	return 0;
//}

class Foo
{
public:
	Foo(int& a)
	{
		m_a = a;
	}

	int GetA()
	{
		return m_a;
	}

	void IncreaseA()
	{
		++m_a;
	}

	void printA()
	{
		cout << m_a << endl;
	}

private:
	int m_a{};
};

int main()
{
	int b = 10;
	Foo foo = Foo(b);
	foo.IncreaseA();
	cout << b << " " << foo.GetA() << endl;

	return 0;
}