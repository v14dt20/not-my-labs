#include "Student.h"
#include <iostream>
#include <string>

using namespace std;

//конструкторы
Student::Student(void) : Person()
{
	rating = 0;
}
Student::Student(string N, int O, int R) : Person(N, O)
{
	rating = R;
}
Student::Student(const Student& s)
{
	name = s.name;
	old = s.old;
	rating = s.rating;
}

//деструктор
Student::~Student(void)
{
}

//селектор
int Student::Get_Rating() { return rating; }

//модификатор
void Student::Set_Rating(int Rating) { rating = Rating; }

//перегрузка оператора присваивания
Student& Student::operator=(const Student& s)
{
	name = s.name;
	old = s.old;
	rating = s.rating;
	return *this;
}

//метод для вывода атрибутов
void Student::Show()
{
	cout << "NAME: " << name << "\n";
	cout << "OLD: " << old << "\n";
	cout << "RATING: " << rating << "\n\n";
}

//метод для ввода атрибутов
void Student::Input()
{
	cout << "Enter name >> "; cin >> name;
	cout << "Enter old >> "; cin >> old;
	cout << "Enter rating >> "; cin >> rating;
	cout << "\n";
}
