#include "Persion.h"


Persion::Persion(void)
{
	this->name = "hello";
}


Persion::~Persion(void)
{
}

char * Persion::getName() const{
	return this->name;
}