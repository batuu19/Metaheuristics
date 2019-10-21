#pragma once

#include <vector>
#include <random>

#include "Creature.h"

class Population
{
public:
	void init(std::mt19937& rng,const DistanceMatrix& distanceMatrix);
	void selection(std::mt19937& rng);

private:
	size_t size;
	std::vector<Creature> creatures;
};
