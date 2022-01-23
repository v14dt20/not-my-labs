#pragma once
#include "Object.h"
#include "Event.h"
#include <iostream>
#include <string>

using namespace std;

class Person :
    public Object
{
protected:
    string name;
    int old;
public:
    //конструкторы
    Person(void);
    Person(string, int);
    Person(const Person&);

    //деструктор
    virtual ~Person(void);

    //функция для просмотра атрибутов с помощью указателя
    void Show();

    //функция для ввода атрибутов
    void Input();

    //селекторы
    string Get_Name();
    int Get_Old();

    //модификаторы
    void Set_Name(string);
    void Set_Old(int);

    //перегрузка операции присваивания
    Person& operator= (const Person&);

    virtual void HandleEvent(const TEvent&);
};

