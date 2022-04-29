#include <iostream>
#include <conio.h>
#include "Calculator.h"

bool validate_action(int action)
{
	return action == '+' || action == '-' || action == '*' || action == '/';
}

int main()
{
	setlocale(LC_ALL, "ru");

	int action;
	Calculator calc;
	// 20 p. 63
	// 79 p. 67
	do
	{
		printf("�������� �������� (+-*/) ��� ������� 0 ��� ������: ");

		do {
			action = getchar();
		} while (action == '\n');

		if (!validate_action(action))
		{
			std::cerr << "�����-�� �������� ��������.. ���������� ��� ���." << std::endl;
			continue;
		}

		double num1, num2;
		printf("������ ����� >> ");
		std::cin >> num1;
		printf("������ ����� >> ");
		std::cin >> num2;

		Fraction res;
		switch (action)
		{
		case '+':
			res = calc.sum(Fraction(num1), Fraction(num2));
			break;
		case '-':
			res = calc.diff(Fraction(num1), Fraction(num2));
			break;
		case '*':
			res = calc.mult(Fraction(num1), Fraction(num2));
			break;
		case '/':
			res = calc.div(Fraction(num1), Fraction(num2));
			break;
		}

		printf("%f %c %f = %f\n", num1, action, num2, res.toDouble());

	} while (action != '0');

	return 0;
}