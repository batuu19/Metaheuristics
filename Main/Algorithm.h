#pragma once

#include <iostream>
#include <fstream>


static constexpr size_t DEFAULT_POPSIZE = 100;
static constexpr size_t DEFAULT_GENERATIONS = 10;
static constexpr float DEFAULT_PX = 0.01f;
static constexpr float DEFAULT_PM = 0.1f;
static constexpr size_t DEFAULT_TSIZE = 10;

static constexpr float OX_TO_PMX_PROB = 0.5f;
static constexpr float SWAP_TO_INV_PROB = 0.9f;

class Config
{
public:
	Config();
	Config(size_t popSize, size_t generations, float px, float pm, size_t tSize);

	//bool isInitialized() { return initialized; };
private:
	//bool initialized = false;
	size_t popSize;
	size_t generations;
	float px, pm;//crossover, mutation
	size_t tSize;
	friend class Algorithm;
};

#include "Population.h"

class Algorithm
{
public:
    Algorithm(Config config,DistanceMatrix* distanceMatrix);
	Algorithm(const Algorithm&);
	Algorithm& operator=(const Algorithm&);
	~Algorithm();
	void run(std::mt19937& rng);
private:
	Config config;
	Population pop;
    DistanceMatrix* distanceMatrix;

	std::uniform_real_distribution<float> percentageDist;//default setting(0.f,1.f)
};