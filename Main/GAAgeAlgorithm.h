#pragma once
#include "MetaAlgorithm.h"
#include "AgedPopulation.h"

class GAAgeAlgorithm : public MetaAlgorithm
{
public:
	GAAgeAlgorithm(const Problem& problem, const Config& config) :
		MetaAlgorithm(problem, config),
		agedPop(config.popSize),
		nDist(0, citiesCount* config.pm)
	{};
	float run(std::mt19937 & rng) override;
private:
	AgedPopulation agedPop;
	std::normal_distribution<float> nDist;
};