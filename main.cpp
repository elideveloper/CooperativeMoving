#include <random>
#include <time.h>
#include <iostream>

#include "GA.h"
#include "Circle.h"

/*
перемещение N юнитов (в виде окружности) в целевые точки кратчайшим путем избегая пересечений
скорость от 0 до 1 ед/тик
*/

const unsigned NUM_UNITS = 4;

std::vector<Vec2D> targetPoints;
std::vector<Circle> units;

// определим функцию оценки
double fitnessFunction(const Individual* ind) {
	double sum = 0.0;
	std::vector<Vec2D> pos;
	for (int i = 0; i < ind->getGenotypeLength(); i++) {
		pos.push_back(units[i].getShifted(*static_cast<Vec2D*>(ind->genotype[i])).getPosition());
	}
	for (int i = 0; i < pos.size(); i++) sum += pos[i].getDistance(targetPoints[i]);
	for (int i = 0; i < pos.size() - 1; i++) {
		for (int j = i + 1; j < pos.size(); j++) {
			if (pos[i].getDistance(pos[j]) < units[0].getRadius() * 2.0) sum *= 10.0;
		}
	}
	return fabs(0.0 - sum);
}

const unsigned POP_SIZE = 40;
const unsigned GEN_LENGTH = NUM_UNITS;
const unsigned NUM_GENERAIONS = 80;
const double ELITE_PERC = 0.1;
const double PARENTS_PERC = 0.5;
const double NEWCOM_PERC = 0.3;
const double MUT_PROB = 0.05;
const double ACCEPTABLE_ERROR = 1.0;

int main() {
	srand(time(0));

	targetPoints.reserve(NUM_UNITS);
	targetPoints.push_back(Vec2D(10.0, 10.0));
	targetPoints.push_back(Vec2D(15.0, 15.0));
	targetPoints.push_back(Vec2D(25.0, 0.0));
	targetPoints.push_back(Vec2D(0.0, 25.0));

	units.reserve(NUM_UNITS);
	for (int i = 0; i < NUM_UNITS; i++) units.push_back(Circle(Vec2D(), Vec2D(), 0.5));

	for (int i = 0; i < 100; i++) {
		// units are represented as circles
		// genotype is collection of new states of units
		GA ga(POP_SIZE, GEN_LENGTH, new Vec2D(), ACCEPTABLE_ERROR, NUM_GENERAIONS, ELITE_PERC, PARENTS_PERC, NEWCOM_PERC, MUT_PROB);

		Individual* bestInd = ga.findBest();
		std::cout << "best: " << fitnessFunction(bestInd) << std::endl;

		if (fitnessFunction(bestInd) <= ACCEPTABLE_ERROR) {
			for (int i = 0; i < bestInd->getGenotype().size(); i++) units[i].getPosition().print();
			break;
		}

		for (int i = 0; i < bestInd->getGenotype().size(); i++) units[i] = units[i].getShifted(*static_cast<Vec2D*>(bestInd->getGenotype()[i]));
	}

	system("pause");

	return 0;
}