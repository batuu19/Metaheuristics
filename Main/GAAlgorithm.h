#pragma once

#include <iostream>
#include <fstream>
#include "MetaAlgorithm.h";

static constexpr char CSV_FIRST_LINE[] = "generation, worst, medium, best\n";

class GAAlgorithm : public MetaAlgorithm
{
public:
	GAAlgorithm(const Problem& problem, const Config& config) :
		MetaAlgorithm(problem, config),
		nDist(0, config.popSize * config.pm)
	{};
	float run(std::mt19937& rng) override;
private:
	std::normal_distribution<float> nDist;
};