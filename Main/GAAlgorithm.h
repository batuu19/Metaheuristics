#pragma once

#include <iostream>
#include <fstream>
#include "MetaAlgorithm.h";


static constexpr size_t DEFAULT_POPSIZE = 100;
static constexpr size_t DEFAULT_GENERATIONS = 10;
static constexpr float DEFAULT_PX = 0.01f;
static constexpr float DEFAULT_PM = 0.1f;
static constexpr size_t DEFAULT_TSIZE = 10;

static constexpr float OX_TO_PMX_PROB = 0.5f;
static constexpr float SWAP_TO_INV_PROB = 0.9f;

static constexpr char CSV_FIRST_LINE[] = "generation, worst, medium, best\n";

class GAAlgorithm : public MetaAlgorithm
{
public:
	GAAlgorithm(const Problem& problem, const Config& config) : MetaAlgorithm(problem, config) {};
	float run(std::mt19937& rng) override;
private:
};