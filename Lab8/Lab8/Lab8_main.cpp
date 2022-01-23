#include "Dialog.h"
#include "Person.h"
#include "Student.h"
#include "List.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	cout << "Command:\n+: add\n-: delete\nm<num>: make list\ns: show\n?<num>: show info about num\nq: exit\n\n";
	Dialog D;
	D.Execute();

	return 0;
}