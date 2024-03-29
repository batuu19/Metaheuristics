#pragma once

#include <fstream>
#include "Problem.h";
#include "Population.h"
#include "DistanceMatrix.h"

//template<typename T>
class Config
{
public:
	static Config getGAConfig(size_t popSize, size_t generations, float px, float pm, size_t tSize);
	static Config getGAConfig(size_t id, size_t popSize, size_t generations, float px, float pm, size_t tSize);
	static Config getGAConfig(size_t id, std::string name, size_t popSize, size_t generations, float px, float pm, size_t tSize);
	static Config getTabuConfig(size_t neighborsCount, size_t maxIterations);
	static Config getTabuConfig(size_t id, size_t neighborsCount, size_t maxIterations);
	static Config getTabuConfig(size_t id, std::string name, size_t neighborsCount, size_t maxIterations);
	static Config getSAConfig(float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations);
	static Config getSAConfig(size_t id, float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations);
	static Config getSAConfig(size_t id, std::string name, float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations);
	static Config getGreedyConfig();
	static Config getGreedyConfig(size_t id);
	static Config getGreedyConfig(size_t id, std::string name);

	static Config getGATSConfig(size_t popSize, size_t generations, float px, float pm, size_t tSize,
		size_t maxIterations, size_t neighborsCount);

public://temp public
	Config() = default;
	friend class MetaAlgorithm;
	std::string filenamePrefix;
	//GA
	size_t popSize;
	size_t generations;
	float px, pm;
	size_t tSize;
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
