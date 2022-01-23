#include "Person.h"
#include "Event.h"
#include <iostream>
#include <string>

using namespace std;

//конструкторы
Person::Person(void)//без параметров
{
	name = "";
	old = 0;
}
Person::Person(string Name, int Old)//с параметрами
{
	name = Name;
	old = Old;
}
Person::Person(const Person& p)//копирования
{
	name = p.name;
	old = p.old;
}

//деструктор
Person::~Person(void)
{
}

//селекторы
string Person::Get_Name() { return name; }
int Person::Get_Old() { return old; }

//модификаторы
void Person::Set_Name(string Name) { name = Name; }
void Person::Set_Old(int Old) { old = Old; }

//перегрузка оператора присваивания
Person& Person::operator= (const Person& p)
{
	name = p.name;
	old = p.old;
	return *this;
}

//метод для вывода атрибутов
void Person::Show()
{
	cout << "NAME: " << name << "\n";
	cout << "OLD: " << old << "\n\n";
}

//метод для ввода атрибутов
void Person::Input()
{
	cout << "Enter name >> "; cin >> name;
	cout << "Enter old >> "; cin >> old;
	cout << "\n";
}

void Person::HandleEvent(const TEvent& event)
{
}