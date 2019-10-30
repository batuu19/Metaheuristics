#pragma once

#include "Creature.h"
#include "Problem.h"
#include <cmath>


constexpr size_t DEFAULT_NEIGHBORS_COUNT_W = 30;
constexpr size_t DEFAULT_MAX_GENERATIONS_W = 100;

class WAlgorithm
{
public:
	WAlgorithm(Problem& problem);
	void run(std::mt19937& rng);
private:
	Creature best;
	size_t temperature = 0;
	
};