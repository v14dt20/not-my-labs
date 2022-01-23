#include "List.h"
#include "Person.h"
#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

//������������
List::List(void)
{
	beg = 0;
	size = 0;
	cur = 0;
}
List::List(int n)
{
	beg = new Object * [n];
	size = n;
	cur = 0;
}
List::List(const List& l)
{
	beg = l.beg;
	size = l.size;
	cur = l.cur;
}

//����������
List::~List(void)
{
}

//���������� ������� �� ������� ��������� ��������� � � ������
void List::Add()
{
	Object* p;
	//����� �� �������� 2 ��������� �������
	cout << "1.Person\n2.Student\nEnter num type >> ";
	int y;
	cin >> y; cout << "\n";

	if (y == 1)//���������� ������� ������ Person
	{
		Person* a = new (Person);
		a->Input();
		p = a;
		if (cur < size)
		{
			beg[cur] = p;
			cur++;
		}
	}
	else if (y == 2)//���������� ������� ������ Student
	{
		Student* b = new (Student);
		b->Input();
		p = b;
		if (cur < size)
		{
			beg[cur] = p;
			cur++;
		}
	}
	else return;
}

//�������� �������� �� ������, �� ��� ���� ������ �� �������������
void List::Del()
{
	if (cur == 0) return;
	cur--;
}

//�������� ������
void List::Info_All()
{
	if (cur == 0) cout << "Empty\n";
	Object** p = beg;//��������� �� ��������� ���� Object
	for (int i = 0; i < cur; i++)
	{
		(*p)->Show();//����� ������ Show() (������� ������������)
		++p;//����������� ��������� �� ���� ������
	}
}

//�������� �������� �� ������
void List::Info_Elem(int n)
{
	if (cur == 0) cout << "Empty\n";
	if (n < 0 && n > cur) cout << "Error, n[1, " << cur << "]\n";
	else beg[n - 1]->Show();
}

//�������� ������������ ������ ������
int List::operator() ()
{
	return cur;
}

void List::HandleEvent(const TEvent& event)
{
	if (event.what == evMessage)
	{
		Object** p = beg;
		for (int i = 0; i < cur; i++)
		{
			(*p)->Show();
			++p;
		}
	}
}