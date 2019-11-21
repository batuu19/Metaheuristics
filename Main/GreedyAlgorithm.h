#pragma once
#include "MetaAlgorithm.h"

class GreedyAlgorithm : public MetaAlgorithm
{
public:
	GreedyAlgorithm(const Problem& problem, const Config& config) : MetaAlgorithm(problem, config) {};
	float run(std::mt19937& rng) override;
};