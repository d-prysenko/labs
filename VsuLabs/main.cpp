#include <iostream>
#include "Vector3D.h"

int main()
{
	setlocale(LC_ALL, "ru");

	float x, y, z, num;

	printf(" ласс Triad\n");

	printf("¬ведите тройку чисел:\n");
	printf(">> ");

	std::cin >> x >> y >> z;

	Triad tr1(x, y, z);

	printf("¬ведите число: ");
	std::cin >> num;

	Triad res1 = tr1 + num;
	Triad res2 = tr1 * num;

	printf("(%.2f; %.2f; %.2f) + %.2f = (%.2f; %.2f; %.2f)\n", tr1.getX(), tr1.getY(), tr1.getZ(), num, res1.getX(), res1.getY(), res1.getZ());
	printf("(%.2f; %.2f; %.2f) * %.2f = (%.2f; %.2f; %.2f)\n", tr1.getX(), tr1.getY(), tr1.getZ(), num, res2.getX(), res2.getY(), res2.getZ());
	printf("(%.2f; %.2f; %.2f) и (%.2f; %.2f; %.2f) %s\n", res1.getX(), res1.getY(), res1.getZ(), res2.getX(), res2.getY(), res2.getZ(), res1 == res2 ? "равны" : "не равны");
	printf("(%.2f; %.2f; %.2f) и (%.2f; %.2f; %.2f) %s\n", res1.getX(), res1.getY(), res1.getZ(), res2.getX(), res2.getY(), res2.getZ(), res1 == res1 ? "равны" : "не равны");

	printf("\n ласс Vector3D\n");

	Vector3D vec1(x, y, z);

	printf("¬ведите тройку чисел:\n");
	printf(">> ");

	std::cin >> x >> y >> z;

	Vector3D vec2(x, y, z);

	Vector3D res3 = vec1 + vec2;

	printf("(%.2f; %.2f; %.2f) + (%.2f; %.2f; %.2f) = (%.2f; %.2f; %.2f)\n", vec1.getX(), vec1.getY(), vec1.getZ(), vec2.getX(), vec2.getY(), vec2.getZ(), res3.getX(), res3.getY(), res3.getZ());
	printf("(%.2f; %.2f; %.2f) * (%.2f; %.2f; %.2f) = %.2f\n", vec1.getX(), vec1.getY(), vec1.getZ(), vec2.getX(), vec2.getY(), vec2.getZ(), vec1 * vec2);

	system("pause");
	return 0;
}