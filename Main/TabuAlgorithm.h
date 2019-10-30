#pragma once

#include "Creature.h"
#include "TabuList.h"
#include "Problem.h"
#include <stack>
#include <fstream>

constexpr size_t DEFAULT_NEIGHBORS_COUNT = 3000;
constexpr size_t DEFAULT_MAX_GENERATIONS = 1000;


class TabuAlgorithm
{
public:
	TabuAlgorithm(const Problem& problem);

	void run(std::mt19937& rng);
private:
	Creature best;
	TabuList tabuList;
	size_t neighSize = 0;
	size_t citiesCount;
};
