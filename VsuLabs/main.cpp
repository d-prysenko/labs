#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

// Backtracking

// 3. Напишите программу, которая выводит все перестановки длины N такие,
// что любые два соседних элемента отличаются как минимум на два.
// Например, если N = 4, то это 1324 и 2413.

void print_description()
{
	printf("3. Напишите программу, которая выводит все перестановки длины N такие,\n");
	printf("что любые два соседних элемента отличаются как минимум на два.\n");
	printf("Например, если N = 4, то это 1324 и 2413.\n\n");
}

void get_transposition(std::vector<int> start, std::list<int> free_numbers)
{
	if (free_numbers.size() == 0)
	{
		std::string res;

		for (const int& val : start)
		{
			res += std::to_string(val) + " ";
		}

		printf("%s\n", res.c_str());
		return;
	}

	for (const int& free_num : free_numbers)
	{	
		if (start.size() && abs(free_num - start.back()) < 2)
			continue;

		std::vector<int> new_start = start;
		new_start.push_back(free_num);

		std::list<int> new_free_numbers = free_numbers;
		new_free_numbers.remove(free_num);

		get_transposition(new_start, new_free_numbers);
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	print_description();

	int length;

	printf("Введите длину последовательности: ");
	std::cin >> length;

	std::list<int> numbers;
	for (int i = 1; i <= length; ++i)
		numbers.push_back(i);

	get_transposition({}, numbers);

	system("pause");
	return 0;
}
