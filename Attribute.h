#pragma once

#include <vector>

struct Attribute {
	virtual ~Attribute();
	virtual Attribute* randomize() = 0;
	virtual Attribute* clone() = 0;
	virtual std::string getID() = 0;

	//virtual void print() = 0;
};

void swapAttributes(Attribute* attr1, Attribute* attr2);

typedef std::vector<Attribute*> Genotype;
