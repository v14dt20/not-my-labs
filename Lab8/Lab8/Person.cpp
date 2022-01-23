#include "Person.h"
#include "Event.h"
#include <iostream>
#include <string>

using namespace std;

//������������
Person::Person(void)//��� ����������
{
	name = "";
	old = 0;
}
Person::Person(string Name, int Old)//� �����������
{
	name = Name;
	old = Old;
}
Person::Person(const Person& p)//�����������
{
	name = p.name;
	old = p.old;
}

//����������
Person::~Person(void)
{
}

//���������
string Person::Get_Name() { return name; }
int Person::Get_Old() { return old; }

//������������
void Person::Set_Name(string Name) { name = Name; }
void Person::Set_Old(int Old) { old = Old; }

//���������� ��������� ������������
Person& Person::operator= (const Person& p)
{
	name = p.name;
	old = p.old;
	return *this;
}

//����� ��� ������ ���������
void Person::Show()
{
	cout << "NAME: " << name << "\n";
	cout << "OLD: " << old << "\n\n";
}

//����� ��� ����� ���������
void Person::Input()
{
	cout << "Enter name >> "; cin >> name;
	cout << "Enter old >> "; cin >> old;
	cout << "\n";
}

void Person::HandleEvent(const TEvent& event)
{
}