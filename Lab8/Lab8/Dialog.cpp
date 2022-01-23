#include "Dialog.h"
#include <iostream>
#include <string>

using namespace std;

//конструктор
Dialog::Dialog(void):List()
{
	EndState = 0;
}

//деструктор
Dialog::~Dialog(void)
{
}

//очищение события
void Dialog::ClearEvent(TEvent& event)
{
	event.what = evNothing;//пустое событие
}

//проверка EndState
int Dialog::Valid()
{
	if (EndState == 0) return 0;
	else return 1;
}

//конец работы
void Dialog::EndExec()
{
	EndState = 1;
}

//получения события
void Dialog::GetEvent(TEvent& event)
{
	string OpInt = "m+-s?q";//коды операций
	string s;
	string param;

	char code;
	cout << ">"; cin >> s;
	code = s[0];//первый символ команды

	if (OpInt.find(code) >= 0)//является ли символ кодом операции
	{
		event.what = evMessage;
		switch (code)
		{
		case 'm':
			event.command = cmMake; break;//создать группу
		case '+':
			event.command = cmAdd; break;//добавить объект
		case '-':
			event.command = cmDel; break;//удалить объект
		case 's':
			event.command = cmShow; break;//вывести список
		case '?':
			event.command = cmGet; break;//вывести атрибуты 1 объекта
		case 'q':
			event.command = cmQuit; break;//выход
		}

		//выделяем параметры команды если они есть
		if (s.length() > 1)
		{
			param = s.substr(1, s.length() - 1);
			int A = atoi(param.c_str());//преобразуем параметр в число
			event.a = A;//записываем параметр в сообщение
		}

	}else event.what = evNothing;//пустое событие
}

//обработчик событий
void Dialog::HandleEvent(TEvent& event)
{
	if (event.what == evMessage)
	{
		switch (event.command)
		{
		case cmMake:
			size = event.a;
			beg = new Object * [size];
			cur = 0;
			ClearEvent(event);
			break;
		case cmAdd:
			Add();
			ClearEvent(event);
			break;
		case cmDel:
			Del();
			ClearEvent(event);
			break;
		case cmShow:
			Info_All();
			ClearEvent(event);
			break;
		case cmGet:
			Info_Elem(event.a);
			ClearEvent(event);
			break;
		case cmQuit:
			EndExec();
			ClearEvent(event);
			break;
		default:
			List::HandleEvent(event);
		}
	}
}

//главный цикл обработки событий
int Dialog::Execute()
{
	TEvent event;
	do
	{
		EndState = 0;
		GetEvent(event);
		HandleEvent(event);
	} while (!Valid());
	return EndState;
}