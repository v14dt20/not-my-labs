#pragma once

const int evNothing = 0; //������ �������
const int evMessage = 100; //�������� �������
const int cmAdd = 1; //�������� ������ � ������
const int cmDel = 2; //������� ������ �� ������
const int cmGet = 3; //������� ������� 1 ������a
const int cmShow = 4; //������� ��� ������
const int cmMake = 5; //������� ������
const int cmQuit = 101; //�����

//����� �������
struct TEvent
{
	int what; //��� �������
	union
	{
		int command; //��� �������
		struct
		{
			int message;
			int a; //�������� �������
		};
	};
};