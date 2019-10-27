#pragma once

#include "Creature.h"
#include "TabuList.h"
#include "Problem.h"
#include <stack>

constexpr size_t MAX_SWAPS_HISTORY = 20;

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

	bool endCondition();
};
