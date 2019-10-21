#pragma once

#include <vector>
#include <random>

#include "Creature.h"

class Population
{
public:
	void selection(std::mt19937 rng);

private:
	size_t size;
	std::vector<Creature> creatures;
};
