#include <iostream>
#include "List.h"

int main()
{
	List<int> values;

	values.insert(1);
	values.insert(2);
	values.insert(3);
	values.insert(4);
	values.insert(5);

	printf("Initial list:\n");
	for (List<int>::iterator i = values.begin(); i != values.end(); ++i)
	{
		printf("%d\n", *i);
	}


	List<int>::iterator itr = values.begin();
	++itr;
	values.remove(itr);

	printf("After deletion:\n");
	for (List<int>::iterator i = values.begin(); i != values.end(); ++i)
	{
		printf("%d\n", *i);
	}

	itr = values.begin();
	++itr;
	++itr;
	values.insertAfter(66, itr);

	printf("After insertion:\n");
	for (List<int>::iterator i = values.begin(); i != values.end(); ++i)
	{
		printf("%d\n", *i);
	}

	system("pause");
	return 0;
}