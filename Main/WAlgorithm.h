#pragma once

#include "Creature.h"
#include "Problem.h"
#include <cmath>
#include <fstream>


constexpr size_t DEFAULT_NEIGHBORS_COUNT_W = 5;
constexpr size_t DEFAULT_MAX_GENERATIONS_W = 1000;
constexpr float DEFAULT_BEGIN_TEMPERATURE = 1500;

class WAlgorithm
{
public:
	WAlgorithm(Problem& problem);
	void run(std::mt19937& rng);
private:
	Creature best;
	float temperature = DEFAULT_BEGIN_TEMPERATURE;
	double coolingRate = 0.995f;
	
};