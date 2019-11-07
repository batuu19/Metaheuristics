#pragma once

#include "Creature.h"
#include "TabuList.h"
#include "Problem.h"
#include <stack>
#include <fstream>
#include "MetaAlgorithm.h"
//
//constexpr size_t DEFAULT_NEIGHBORS_COUNT = 20;
//constexpr size_t DEFAULT_MAX_GENERATIONS = 400;
class TabuAlgorithm : public MetaAlgorithm
{
public:
	void run(std::mt19937& rng);
private:
	TabuList tabuList;
};
