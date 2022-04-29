#include "Container.h"

Container::Container()
{}

Container::Container(int size)
{
	m_data = new float[size];
	m_size = size;
}

Container::~Container()
{
	if (m_data != nullptr)
		delete[] m_data;
}

float Container::get(int pos)
{
	if (pos >= m_size)
		throw std::exception("Index out of bounds");

	if (m_data == nullptr)
		throw std::exception("Container is not initialized");

	return m_data[pos];
}

void Container::insert(float num, int pos)
{
	if (pos >= m_size)
		throw std::exception("Index out of bounds");

	if (m_data == nullptr)
		throw std::exception("Container is not initialized");

	m_data[pos] = num;
}

void Container::resize(int size)
{
	if (m_data != nullptr)
		delete[] m_data;

	m_data = new float[size];
	m_size = size;
}

int Container::getSize()
{
	return this->m_size;
}
