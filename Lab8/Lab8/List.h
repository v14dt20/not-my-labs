#pragma once
#include "Object.h"
#include <iostream>
#include <string>

using namespace std;

class List
{
protected:
	Object** beg;//��������� �� ������ ������� ������
	int size;//������ ������
	int cur;//������� ���������
public:
	//������������
	List(void);//��� ����������
	List(int);//c ����������
	List(const List&);//�����������

	//�����������
	~List(void);

	void Add();//��������
	void Del();//�������
	void Info_All();//���������� � ���� ������
	void Info_Elem(int);//���������� �� ����� ��������

	int operator() ();//���������� ������ ������

	virtual void HandleEvent(const TEvent& event);
};

