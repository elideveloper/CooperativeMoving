#include "GA.h"

#include <algorithm>
#include <iostream>
//#include <unordered_map>

double GA::sortAndGetMinError(Generation& generation)
{
	/*std::unordered_map<Individual*, double> scores;
	for (Individual* i : generation) {
		scores.insert({ i, fitnessFunction(i) });
	}
	std::sort(generation.begin(), generation.end(), [scores](Individual* ind1, Individual* ind2)->bool {
		return scores.find(ind1)->second < scores.find(ind2)->second;
	});*/
	
	std::sort(generation.begin(), generation.end(), [](const Individual* ind1, const Individual* ind2)->bool {
		return fitnessFunction(ind1) < fitnessFunction(ind2);
	});
	return fitnessFunction(generation[0]);
}

GA::GA() : populationSize(0), genotypeLength(0), individualInstance(nullptr), acceptableError(0.0), maxGenerations(0), numElite(0), numNewcomers(0), mutationProb(0.0)
{}

GA::GA(unsigned int populationSize, unsigned int genotypeLength, Attribute* attrInstance, double acceptableError, unsigned int maxGenerations, double elitePercentage, double parentsPercentage, double newcomersPercentage, double mutationProb)
	: populationSize(populationSize), genotypeLength(genotypeLength), acceptableError(acceptableError), maxGenerations(maxGenerations),
	numElite(populationSize * boundBetween(0.0, 1.0, elitePercentage)), numParents(populationSize * boundBetween(0.0, 1.0, parentsPercentage)),
	numNewcomers(populationSize * boundBetween(0.0, 1.0, newcomersPercentage)), mutationProb(boundBetween(0.0, 1.0, mutationProb))
{
	Genotype genotype; genotype.reserve(genotypeLength);
	for (int i = 0; i < genotypeLength; i++) genotype.push_back(attrInstance->clone());
	this->individualInstance = new Individual(genotype, false);
}

GA::GA(unsigned int populationSize, Individual* individInstance, double acceptableError, unsigned int maxGenerations, double elitePercentage, double parentsPercentage, double newcomersPercentage, double mutationProb)
	: populationSize(populationSize), genotypeLength(individInstance->getGenotypeLength()), acceptableError(acceptableError), maxGenerations(maxGenerations), individualInstance(individInstance),
	numElite(populationSize * boundBetween(0.0, 1.0, elitePercentage)), numParents(populationSize * boundBetween(0.0, 1.0, parentsPercentage)),
	numNewcomers(populationSize * boundBetween(0.0, 1.0, newcomersPercentage)), mutationProb(boundBetween(0.0, 1.0, mutationProb))
{}

GA::~GA()
{
	delete this->individualInstance;
}

Generation GA::createRandomGeneration()
{
	Generation generation; generation.reserve(this->populationSize);
	for (int j = 0; j < this->populationSize; j++) generation.push_back((new Individual(*this->individualInstance))->randomize());
	this->sortAndGetMinError(generation);
	return generation;
}

Individual* GA::findBest()
{
	Generation gen = createRandomGeneration();
	int j;
	std::vector<Individual*> parents; parents.reserve(this->numParents);
	for (int i = 0; i < this->maxGenerations; i++) {
		parents.clear();
		for (j = 0; j < this->numParents; j++) parents.push_back(new Individual(*gen[j]));
		for (j = this->numElite; j < this->populationSize - this->numNewcomers; j++) gen[j]->turnToChildOf(parents[rand() % this->numParents], parents[rand() % this->numParents], this->mutationProb);
		for (Individual* ind : parents) delete ind;
		for (j; j < this->populationSize; j++) gen[j]->randomize();
		if (this->sortAndGetMinError(gen) <= this->acceptableError) break;
	}
	for (int i = 1; i < this->populationSize; i++) delete gen[i];
	return gen[0];
}
