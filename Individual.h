#pragma once

#include "Attribute.h"

class Individual {
	bool hasOrderedGenotype;
	Genotype genotype;
	void getRecombinationOf(const Individual* mom, const Individual* dad, unsigned int point);
public:
	Individual();
	Individual(const Genotype& genotype, bool hasOrderedGenotype);
	Individual(const Individual& ind);
	Individual& operator=(const Individual& ind);
	~Individual();
	unsigned int getGenotypeLength() const;
	Genotype getGenotype() const;
	Individual* randomize();
	void mutate();																// рандомизирует случайный параметр генома
	void turnToChildOf(const Individual* mom, const Individual* dad, double mutationProb);

	void print();

	friend double fitnessFunction(const Individual* ind);
};

typedef double(*individEvaluator)(const Individual&);
typedef std::vector<Individual*> Generation;