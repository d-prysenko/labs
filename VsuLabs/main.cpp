#include <iostream>
#include "Hash.h"

void print_description()
{
	printf("#39\n");
}

int main()
{
	setlocale(LC_ALL, "ru");

	print_description();

	HashTable table;

	Cell c1;
	c1.data.fullname = "Ivanov Ivan";
	c1.data.number = "#123";
	c1.data.salary = 50000;

	Cell c2;
	c2.data.fullname = "Petrov Vasya";
	c2.data.number = "#333";
	c2.data.salary = 50001;

	table.AddElem(c1);
	table.AddElem(c2);

	printf("Человек с номером #123 есть? %s\n", table.FindElem("#123") ? "да" : "нет");
	printf("Человек с номером #122 есть? %s\n", table.FindElem("#122") ? "да" : "нет");

	system("pause");
	return 0;
}