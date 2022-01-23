#pragma once
#include "Person.h"
#include <iostream>
#include <string>

using namespace std;

class Student :
    public Person
{
protected:
    float rating;
public:
    //конструкторы
    Student(void);//без параметров
    Student(string, int, int);//с параметрами
    Student(const Student& s);//копирования

    //деструктор
    ~Student(void);

    //селекторы
    int Get_Rating();

    //модификатор
    void Set_Rating(int);

    //перегрузка оператора присваивания
    Student& operator=(const Student& s);

    //метод для вывода атрибутов
    void Show();

    //метод для ввода атрибутов
    void Input();
};