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
    //������������
    Person(void);
    Person(string, int);
    Person(const Person&);

    //����������
    virtual ~Person(void);

    //������� ��� ��������� ��������� � ������� ���������
    void Show();

    //������� ��� ����� ���������
    void Input();

    //���������
    string Get_Name();
    int Get_Old();

    //������������
    void Set_Name(string);
    void Set_Old(int);

    //���������� �������� ������������
    Person& operator= (const Person&);

    virtual void HandleEvent(const TEvent&);
};

