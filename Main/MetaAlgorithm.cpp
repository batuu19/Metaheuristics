#include "MetaAlgorithm.h"

Config Config::getGAConfig(size_t popSize, size_t generations, float px, float pm, size_t tSize,
	Mutation mutation, Crossover crossover)
{
	Config cfg;
	cfg.filenamePrefix = "CSV\\ga";
	cfg.popSize = popSize;
	cfg.generations = generations;
	cfg.px = px;
	cfg.pm = pm;
	cfg.tSize = tSize;
	cfg.mutation = mutation;
	cfg.crossover = crossover;
	return cfg;
}

Config Config::getGAConfig(size_t id, size_t popSize, size_t generations, float px, float pm, size_t tSize,
	Mutation mutation, Crossover crossover)
{
	Config cfg = getGAConfig(popSize, generations, px, pm, tSize,mutation,crossover);
	std::stringstream ss;
	ss << cfg.filenamePrefix << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}

Config Config::getGAConfig(size_t id, std::string name, size_t popSize, size_t generations, float px, float pm, size_t tSize, Mutation mutation, Crossover crossover)
{
	Config cfg = getGAConfig(popSize, generations, px, pm, tSize, mutation, crossover);
	std::stringstream ss;
	ss << cfg.filenamePrefix << "_" << name << "_" << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}

Config Config::getTabuConfig(size_t neighborsCount, size_t maxIterations)
{
	Config cfg;
	cfg.filenamePrefix = "CSV\\tabu";
	cfg.popSize = 1;
	cfg.generations = maxIterations;
	cfg.neighborsCount = neighborsCount;
	cfg.maxIterations = maxIterations;
	return cfg;
}

Config Config::getTabuConfig(size_t id, size_t neighborsCount, size_t maxIterations)
{
	Config cfg = getTabuConfig(neighborsCount, maxIterations);
	std::stringstream ss;
	ss << cfg.filenamePrefix << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}

Config Config::getTabuConfig(size_t id, std::string name, size_t neighborsCount, size_t maxIterations)
{
	Config cfg = getTabuConfig(neighborsCount, maxIterations);
	std::stringstream ss;
	ss << cfg.filenamePrefix << "_" << name << "_" << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}

Config Config::getSAConfig(float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations)
{
	Config cfg;
	cfg.filenamePrefix = "CSV\\sa";
	cfg.popSize = 1;
	cfg.generations = maxIterations;
	cfg.beginTemperature = beginTemperature;
	cfg.coolingRate = coolingRate;
	cfg.neighborsCount = neighborsCount;
	cfg.maxIterations = maxIterations;
	return cfg;
}

Config Config::getSAConfig(size_t id, float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations)
{
	Config cfg = getSAConfig(beginTemperature, coolingRate, neighborsCount, maxIterations);
	std::stringstream ss;
	ss << cfg.filenamePrefix << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}

Config Config::getSAConfig(size_t id, std::string name, float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations)
{
	Config cfg = getSAConfig(beginTemperature, coolingRate, neighborsCount, maxIterations);
	std::stringstream ss;
	ss << cfg.filenamePrefix << "_" << name << "_" << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}

Config Config::getGreedyConfig()
{
	Config cfg;
	cfg.filenamePrefix = "CSV\\greedy";
	cfg.popSize = 1;
	return cfg;
}

Config Config::getGreedyConfig(size_t id)
{
	Config cfg = getGreedyConfig();
	std::stringstream ss;
	ss << cfg.filenamePrefix << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}

Config Config::getGreedyConfig(size_t id, std::string name)
{
	Config cfg = getGreedyConfig();
	std::stringstream ss;
	ss << cfg.filenamePrefix << "_" << name << "_" << id;
	cfg.filenamePrefix = ss.str();
	return cfg;
}




MetaAlgorithm::MetaAlgorithm(const Problem& problem, const Config& config)
	:
	config(config),
	pop(config.popSize),
	distanceMatrix(problem.getDistanceMatrix()),
	citiesCount(problem.getDimension())
{}

MetaAlgorithm::MetaAlgorithm(const MetaAlgorithm& other)
	:
	config(other.config),
	pop(config.popSize),
	distanceMatrix(other.distanceMatrix),
	citiesCount(other.citiesCount)
{}

MetaAlgorithm& MetaAlgorithm::operator=(const MetaAlgorithm& other)
{
	this->config = other.config;//good?
	this->pop = other.pop;//good?
	this->distanceMatrix = other.distanceMatrix;
	this->citiesCount = other.citiesCount;
	return *this;
}