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
    //������������
    Student(void);//��� ����������
    Student(string, int, int);//� �����������
    Student(const Student& s);//�����������

    //����������
    ~Student(void);

    //���������
    int Get_Rating();

    //�����������
    void Set_Rating(int);

    //���������� ��������� ������������
    Student& operator=(const Student& s);

    //����� ��� ������ ���������
    void Show();

    //����� ��� ����� ���������
    void Input();
};