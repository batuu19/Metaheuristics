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

static constexpr char CSV_FIRST_LINE[] = "generation, worst, medium, best\n";

class Config
{
public:
	Config();
	Config(int id, size_t popSize, size_t generations, float px, float pm, size_t tSize);

	void saveToFile();
private:
	int id;
	size_t popSize;
	size_t generations;
	float px, pm;//crossover, mutation
	size_t tSize;
	friend class GAAlgorithm;

	std::string getFileName();
};

#include "Population.h"

class GAAlgorithm
{
public:
	GAAlgorithm(Config config, DistanceMatrix* distanceMatrix);
	GAAlgorithm(const GAAlgorithm&);
	GAAlgorithm& operator=(const GAAlgorithm&);
	~GAAlgorithm();
	std::pair<int, std::string> run(std::mt19937& rng);
private:
	Config config;
	Population pop;
	DistanceMatrix* distanceMatrix;

	std::uniform_real_distribution<float> percentageDist;//default setting(0.f,1.f)
};