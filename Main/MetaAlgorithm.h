#pragma once

#include <fstream>
#include "Problem.h";
#include "Population.h"
#include "DistanceMatrix.h"

enum Mutation//TODO add and use
{
	SWAP,
	INVERSE,
};
enum Crossover
{
	OX,
	PMX,
};

//template<typename T>
class Config
{
public:
	static Config getGAConfig(size_t popSize, size_t generations, float px, float pm, size_t tSize, Mutation mutation, Crossover crossover);
	static Config getGAConfig(size_t id, size_t popSize, size_t generations, float px, float pm, size_t tSize, Mutation mutation, Crossover crossover);
	static Config getGAConfig(size_t id, std::string name, size_t popSize, size_t generations, float px, float pm, size_t tSize, Mutation mutation, Crossover crossover);
	static Config getTabuConfig(size_t neighborsCount, size_t maxIterations);
	static Config getTabuConfig(size_t id, size_t neighborsCount, size_t maxIterations);
	static Config getTabuConfig(size_t id, std::string name, size_t neighborsCount, size_t maxIterations);
	static Config getSAConfig(float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations);
	static Config getSAConfig(size_t id, float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations);
	static Config getSAConfig(size_t id, std::string name, float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations);
	static Config getGreedyConfig();
	static Config getGreedyConfig(size_t id);
	static Config getGreedyConfig(size_t id, std::string name);

public://temp public
	Config() = default;
	friend class MetaAlgorithm;
	std::string filenamePrefix;
	//GA
	size_t popSize;
	size_t generations;
	float px, pm;
	size_t tSize;
	Mutation mutation;
	Crossover crossover;
	//tabu
	size_t neighborsCount;
	size_t maxIterations;
	//SA
	float beginTemperature;
	double coolingRate;
};

class MetaAlgorithm
{
public:
	MetaAlgorithm(const Problem& problem, const Config& config);
	MetaAlgorithm(const MetaAlgorithm&);
	MetaAlgorithm& operator=(const MetaAlgorithm&);
	virtual ~MetaAlgorithm() = default;
	virtual float run(std::mt19937& rng) = 0;
protected:
	Config config;
	Population pop;
	DistanceMatrix* distanceMatrix;
	size_t citiesCount;
	std::uniform_real_distribution<float> percentageDist;
};
