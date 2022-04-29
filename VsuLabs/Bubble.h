#pragma once
#include "Container.h"

class Bubble : public Container
{
public:
	Bubble() : Container() {}
	Bubble(int size) : Container(size) {}

	virtual void sort();
	virtual void foreach();
};

