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
		swapDist(0, problem.getDimension() * config.pm*2)
	{};
	float run(std::mt19937& rng) override;
private:
	std::normal_distribution<float> swapDist;
};