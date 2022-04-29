#pragma once
#include <exception>
#include <algorithm>

class Container
{
protected:
	float* m_data = nullptr;
	int m_size = 0;

public:
	Container();
	Container(int size);
	virtual ~Container();

	float get(int pos);
	void insert(float num, int pos);
	void resize(int size);

	int getSize();

	virtual void sort() = 0;
	virtual void foreach() = 0;
};

