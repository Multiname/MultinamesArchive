#include <iostream>
using namespace std;

const float MIN = -19.9;
const float MAX = 59.9;

enum MenuCommands
{
	CREATE,
	ADD,
	SHOW,
	CHECK,
	ERASE,
	SEARCH,
	CLEAR,
	EXIT
};

enum Mods
{
	FIRST,
	END,
	POS,
	KEY
};

struct element
{
	element* next = nullptr;
	float content{};
};

void commands(int& code);
void create(element*& head);
void add(element* &head);
void addfirst(element* &head);
void addend(element* head);
void addafterpos(element* head);
void addafterkey(element* head);
void show(element* head);
void check(element* head);
void erase(element*& head);
void erasefirst(element*& head);
void eraseend(element*& head);
void erasepos(element*& head);
void erasekey(element*& head);
void search(element* head);
void clear(element*& head);
float input();

int main()
{
	setlocale(LC_ALL, "Russian");
	element* head = nullptr;

	int code = -1;
	while (code != EXIT)
	{
		commands(code);
		switch (code)
		{
		case CREATE:
			system("cls");
			create(head);
			cout << endl;
			break;
		case ADD:
			system("cls");
			add(head);
			cout << endl;
			break;
		case SHOW:
			system("cls");
			show(head);
			cout << endl;
			break;
		case CHECK:
			system("cls");
			check(head);
			cout << endl;
			break;
		case ERASE:
			system("cls");
			erase(head);
			cout << endl;
			break;
		case SEARCH:
			system("cls");
			search(head);
			cout << endl;
			break;
		case CLEAR:
			system("cls");
			clear(head);
			break;
		}
	}

	return 0;
}

void commands(int &code)
{
	cout << "   " << CREATE << ". ������� ������" << endl;
	cout << "   " << ADD << ". �������� �������" << endl;
	cout << "   " << SHOW << ". �������� ������" << endl;
	cout << "   " << CHECK << ". ��������� ������" << endl;
	cout << "   " << ERASE << ". ������� �������" << endl;
	cout << "   " << SEARCH << ". ����� ������������� ��������" << endl;
	cout << "   " << CLEAR << ". ������� ������" << endl;
	cout << "   " << EXIT << ". �����" << endl;
	cout << "������� ���: ";
	cin >> code;
}

void create(element* &head)
{
	if (head == nullptr)
	{
		cout << "������� ���-�� ���������: ";
		int len{};
		cin >> len;

		if (len > 0)
		{
			head = new element{};
			element* temp = head;
			cout << "������� 0-� �������: ";
			float num{};
			num = input();
			temp->content = num;

			for (int i = 1; i < len; i++)
			{
				temp->next = new element{};
				temp = temp->next;
				cout << "������� " << i << "-� �������: ";
				num = input();
				temp->content = num;
			}
		}
		else
		{
			cout << "������������ ����� ���������" << endl;
		}
	}
	else
	{
		cout << "������ ��� ������" << endl;
	}
}

void add(element* &head)
{
	if (head != nullptr)
	{
		cout << "������" << endl;
		cout << FIRST << ". � ������ ������" << endl;
		cout << END << ". � ����� ������" << endl;
		cout << POS << ". ����� �������� ��� �������" << endl;
		cout << KEY << ". ����� �������� � ������" << endl;
		cout << "�������� �����: ";
		int mod{};
		cin >> mod;
		switch (mod)
		{
		case FIRST:
			addfirst(head);
			break;
		case END:
			addend(head);
			break;
		case POS:
			addafterpos(head);
			break;
		case KEY:
			addafterkey(head);
			break;
		}
		if (mod > KEY || mod < FIRST)
		{
			cout << "������������ �����" << endl;
		}
	}
	else
	{
		cout << "�������� ������" << endl;
	}
}

void addfirst(element* &head)
{
	element* temp = head;
	head = new element{};
	head->next = temp;
	cout << "������� �������: ";
	float num{};
	num = input();
	head->content = num;
}

void addend(element* head)
{
	element* temp = head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	temp->next = new element{};
	temp = temp->next;
	cout << "������� �������: ";
	float num{};
	num = input();
	temp->content = num;
}

void addafterpos(element* head)
{
	cout << "������� ����� ��������: ";
	int pos{};
	cin >> pos;
	if (pos >= 0)
	{
		element* temp = head;
		int i = 0;
		while (i < pos && temp != nullptr)
		{
			temp = temp->next;
			i++;
		}
		if (temp != nullptr)
		{
			element* link = temp->next;
			temp->next = new element{};
			temp = temp->next;
			temp->next = link;
			cout << "������� �������: ";
			float num{};
			num = input();
			temp->content = num;
		}
		else
		{
			cout << "������� �� ������" << endl;
		}
	}
	else
	{
		cout << "������������ ����� ��������" << endl;
	}
}

void addafterkey(element* head)
{
	cout << "������� ����: ";
	float num{};
	num = input();
	element* temp = head;
	while (temp->content != num && temp->next != nullptr)
	{
		temp = temp->next;
	}
	if (temp->content == num)
	{
		element* link = temp->next;
		temp->next = new element{};
		temp = temp->next;
		temp->next = link;
		cout << "������� �������: ";
		num = input();
		temp->content = num;
	}
	else
	{
		cout << "������� �� ������" << endl;
	}
}

void show(element* head)
{
	int i = 0;
	element* temp = head;
	while (temp != nullptr)
	{
		cout << i << ". " << temp->content << endl;
		i++;
		temp = temp->next;
	}
	if (i == 0)
	{
		cout << "�������� ������" << endl;
	}
}

void check(element* head)
{
	if (head == nullptr)
	{
		cout << "������ �� ������" << endl;
	}
	else
	{
		cout << "������ ������" << endl;
	}
}

void erase(element* &head)
{
	if (head != nullptr)
	{
		cout << "������" << endl;
		cout << FIRST << ". ������ �������" << endl;
		cout << END << ". ��������� �������" << endl;
		cout << POS << ". ������� ��� �������" << endl;
		cout << KEY << ". ������� � ������" << endl;
		cout << "�������� �����: ";
		int mod{};
		cin >> mod;
		switch (mod)
		{
		case FIRST:
			erasefirst(head);
			break;
		case END:
			eraseend(head);
			break;
		case POS:
			erasepos(head);
			break;
		case KEY:
			erasekey(head);
			break;
		}
		if (mod > KEY || mod < FIRST)
		{
			cout << "������������ �����" << endl;
		}
	}
	else
	{
		cout << "�������� ������" << endl;
	}
}

void erasefirst(element* &head)
{
	element* temp = head;
	head = head->next;
	delete temp;
}

void eraseend(element* &head)
{
	if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		element* temp = head;
		while (temp->next->next != nullptr)
		{
			temp = temp->next;
		}
		delete temp->next;
		temp->next = nullptr;
	}
}

void erasepos(element* &head)
{
	cout << "������� ����� ��������: ";
	int pos{};
	cin >> pos;
	if (pos == 0)
	{
		erasefirst(head);
	}
	else if (pos > 0)
	{
		if (head->next != nullptr)
		{
			element* temp = head;
			int i = 1;
			while (i < pos && temp->next != nullptr)
			{
				temp = temp->next;
				i++;
			}
			if (temp->next != nullptr)
			{
				element* link = temp->next->next;
				delete temp->next;
				temp->next = link;
			}
			else
			{
				cout << "������� �� ������" << endl;
			}
		}
		else
		{
			cout << "������� �� ������" << endl;
		}
	}
	else
	{
		cout << "������������ ����� ��������" << endl;
	}
}

void erasekey(element* &head)
{
	cout << "������� ����: ";
	float num{};
	num = input();
	if (head->content == num)
	{
		erasefirst(head);
	}
	else if (head->next != nullptr)
	{
		element* temp = head;
		while (temp->next->content != num && temp->next->next != nullptr)
		{
			temp = temp->next;
		}
		if (temp->next->content == num)
		{
			element* link = temp->next->next;
			delete temp->next;
			temp->next = link;
		}
		else
		{
			cout << "������� �� ������" << endl;
		}
	}
	else
	{
		cout << "������� �� ������" << endl;
	}
}

void search(element* head)
{
	if (head != nullptr)
	{
		cout << "��������� ������������� ��������:" << endl;
		element* temp = head;
		while (temp != nullptr)
		{
			if (temp->content < 0)
			{
				cout << temp->content << endl;
			}
			temp = temp->next;
		}
	}
	else
	{
		cout << "�������� ������" << endl;
	}
}

void clear(element* &head)
{
	if (head != nullptr)
	{
		while (head != nullptr)
		{
			element* temp = head;
			head = head->next;
			delete temp;
		}
	}
	else
	{
		cout << "������ �� ������" << endl << endl;
	}
}

float input()
{
	float num{};
	do
	{
		cin >> num;
		if (num < MIN || num > MAX)
		{
			cout << "������������ �����. ���������� ��������: [" << MIN << "; " << MAX << "]" << endl;
			cout << "���������� ��� ���: ";
		}
	} while (num < MIN || num > MAX);
	return num;
}