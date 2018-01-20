#include "Individual.h"

#include <random>
#include <algorithm>    
#include <set>
#include <iterator>
#include <unordered_map>
#include <iostream>
#include <string>

void Individual::getRecombinationOf(const Individual * mom, const Individual * dad, unsigned int point)
{
	for (int i = 0; i < this->genotype.size(); i++) {
		delete this->genotype[i];
		this->genotype[i] = (i < point) ? mom->genotype[i]->clone() : dad->genotype[i]->clone();
	}
}

Individual::Individual()
{}

Individual::Individual(const Genotype& genotype, bool hasOrderedGenotype)
{
	this->hasOrderedGenotype = hasOrderedGenotype;
	this->genotype.reserve(genotype.size());
	for (Attribute* a : genotype) this->genotype.push_back(a->clone());
}

Individual::~Individual()
{
	for (Attribute* a : this->genotype) delete a;
}

Individual::Individual(const Individual& ind)
{
	this->hasOrderedGenotype = ind.hasOrderedGenotype;
	this->genotype.reserve(ind.getGenotypeLength());
	for (Attribute* a : ind.genotype) this->genotype.push_back(a->clone());
}

Individual& Individual::operator=(const Individual& ind)
{
	this->hasOrderedGenotype = ind.hasOrderedGenotype;
	this->genotype.clear(); this->genotype.reserve(ind.getGenotypeLength());
	for (Attribute* a : ind.genotype) this->genotype.push_back(a->clone());
	return *this;
}

unsigned int Individual::getGenotypeLength() const
{
	return this->genotype.size();
}

Genotype Individual::getGenotype() const
{
	return this->genotype;
}

Individual* Individual::randomize()
{
	if (this->hasOrderedGenotype) std::random_shuffle(this->genotype.begin(), this->genotype.end());
	else for (Attribute* a : this->genotype) a->randomize();
	return this;
}

void Individual::mutate()
{
	if (this->hasOrderedGenotype) swapAttributes(this->genotype[rand() % this->genotype.size()], this->genotype[rand() % this->genotype.size()]);
	else this->genotype[rand() % this->genotype.size()]->randomize();
}

void Individual::turnToChildOf(const Individual* mom, const Individual* dad, double mutationProb)
{
	if (mom->genotype.size() > 1) {
		unsigned int point = (mom->genotype.size() == 2) ? 1 : rand() % (mom->genotype.size() - 1) + 1;
		if (this->hasOrderedGenotype) {
			std::set<std::string> setMom, setDad, setIntersec, sMom, sDad;
			std::unordered_map<std::string, Attribute*> dadMap;
			for (int i = 0; i < point; i++) {
				setMom.insert(mom->genotype[i]->getID());
				setDad.insert(dad->genotype[i]->getID());
				dadMap[dad->genotype[i]->getID()] = dad->genotype[i];
			}
			getRecombinationOf(mom, dad, point);
			std::set_intersection(setMom.begin(), setMom.end(), setDad.begin(), setDad.end(), std::inserter(setIntersec, setIntersec.begin()));
			if (setIntersec.size() < point) {
				std::set_difference(setMom.begin(), setMom.end(), setIntersec.begin(), setIntersec.end(), std::inserter(sMom, sMom.begin()));
				std::set_difference(setDad.begin(), setDad.end(), setIntersec.begin(), setIntersec.end(), std::inserter(sDad, sDad.begin()));
				for (int i = point; i < this->genotype.size(); i++) {
					if (sMom.erase(this->genotype[i]->getID()) > 0) {
						delete this->genotype[i];
						this->genotype[i] = dadMap.find(*sDad.begin())->second->clone();
						sDad.erase(sDad.begin());
					}
				}
			}
		}
		else getRecombinationOf(mom, dad, point);
	}
	if (this->genotype.size() > 0 && (rand() % (10000 + 1)) * 0.0001 <= mutationProb) this->mutate();
}


void Individual::print()
{
	for (Attribute* a : this->genotype) std::cout << (a->getID()) << std::endl;
}