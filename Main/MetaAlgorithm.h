#pragma once

#include "Problem.h";
#include "Population.h"
#include "DistanceMatrix.h"

//template<typename T>
class Config
{
public:
	static Config getGAConfig(size_t popSize, size_t generations, float px, float pm, size_t tSize);
	static Config getTabuConfig(size_t neighborsCount, size_t maxIterations);
	static Config getSAConfig(float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations);
public://temp public
	Config() = default;
	friend class MetaAlgorithm;
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
	MetaAlgorithm(const Problem& problem,const Config& config);
	MetaAlgorithm(const MetaAlgorithm&);
	MetaAlgorithm& operator=(const MetaAlgorithm&);
	virtual ~MetaAlgorithm();
	virtual void run(std::mt19937& rng) = 0;
protected:
	Config config;
	Population pop;
	DistanceMatrix* distanceMatrix;
	//need file here
	size_t citiesCount;
	std::uniform_real_distribution<float> percentageDist;
};
