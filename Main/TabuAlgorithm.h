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
	TabuAlgorithm(const Problem& problem, const Config& config) : MetaAlgorithm(problem, config) {};
	float run(std::mt19937& rng) override;
private:
	TabuList tabuList;
};
