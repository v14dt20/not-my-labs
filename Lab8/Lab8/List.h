#pragma once
#include "Object.h"
#include <iostream>
#include <string>

using namespace std;

class List
{
protected:
	Object** beg;//указатель на первый элемент списка
	int size;//размер списка
	int cur;//текущее положение
public:
	//конструкторы
	List(void);//без параметров
	List(int);//c параметром
	List(const List&);//копирования

	//деструкторы
	~List(void);

	void Add();//добавить
	void Del();//удалить
	void Info_All();//информация о всем списке
	void Info_Elem(int);//информация об одном элементе

	int operator() ();//возвращает размер списка

	virtual void HandleEvent(const TEvent& event);
};

