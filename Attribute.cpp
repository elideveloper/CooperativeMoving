#include "Attribute.h"

void swapAttributes(Attribute * attr1, Attribute * attr2)
{
	Attribute* tmp = attr2;
	attr2 = attr1;
	attr1 = tmp;
}

Attribute::~Attribute()
{}
