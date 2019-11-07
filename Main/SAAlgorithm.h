#pragma once

#include "MetaAlgorithm.h"
#include <cmath>
#include <fstream>

//
//constexpr size_t DEFAULT_NEIGHBORS_COUNT_W = 5;
//constexpr size_t DEFAULT_MAX_GENERATIONS_W = 1000;
//constexpr float DEFAULT_BEGIN_TEMPERATURE = 1500;

class SAAlgorithm : public MetaAlgorithm
{
public:
	SAAlgorithm(const Problem& problem, const Config& config) : MetaAlgorithm(problem, config) {};
	void run(std::mt19937& rng);
private:
	
};