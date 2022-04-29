#pragma once
#include "Container.h"

class Choice : public Container
{
public:
	Choice() : Container() {}
	Choice(int size) : Container(size) {}

	virtual void sort();
	virtual void foreach();
};

