#include <iostream>
#include "Angle.h"
#include <io.h>
#include <fcntl.h>

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	Angle a1(5, 30);
	Angle a2(6, 30);

	if (a2 > a1) {
		std::wcout << a2 << " greater than " << a1 << std::endl;
	} else {
		std::wcout << a1 << " greater than " << a2 << std::endl;
	}

	Angle a3 = a1 + a2;

	std::wcout << a1 << " + " << a2 << " = " << a3 << std::endl;

	Angle a4;

	std::wcout << "Enter the angle(degrees and minutes): ";
	std::wcin >> a4;

	std::wcout << "You entered " << a4 << std::endl;

	system("pause");
	return 0;
}