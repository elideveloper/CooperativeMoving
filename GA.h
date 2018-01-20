#pragma once

#include "Individual.h"
#include "utility.h"

class GA {
	unsigned int populationSize;
	unsigned int genotypeLength;
	Individual* individualInstance;
	double acceptableError;
	unsigned int maxGenerations;
	double mutationProb;
	unsigned int numElite;
	unsigned int numParents;
	unsigned int numNewcomers;
	double sortAndGetMinError(Generation& generation);
public:
	GA();
	GA(unsigned int populationSize, unsigned int genotypeLength, Attribute* attrInstance, double acceptableError, unsigned int maxGenerations, double elitePercentage, double parentsPercentage, double newcomersPercentage, double mutationProb);
	GA(unsigned int populationSize, Individual* individInstance, double acceptableError, unsigned int maxGenerations, double elitePercentage, double parentsPercentage, double newcomersPercentage, double mutationProb);
	~GA();
	Generation createRandomGeneration();
	Individual* findBest();
};
