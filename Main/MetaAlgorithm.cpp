#include "MetaAlgorithm.h"

Config Config::getGAConfig(size_t popSize, size_t generations, float px, float pm, size_t tSize)
{
	Config cfg;
	cfg.popSize = popSize;
	cfg.generations = generations;
	cfg.px = px;
	cfg.pm = pm;
	cfg.tSize = tSize;
	return cfg;
}

Config Config::getTabuConfig(size_t neighborsCount, size_t maxIterations)
{
	Config cfg;
	cfg.popSize = 1;
	cfg.generations = maxIterations;
	cfg.neighborsCount = neighborsCount;
	cfg.maxIterations = maxIterations;
	return cfg;
}

Config Config::getSAConfig(float beginTemperature, double coolingRate, size_t neighborsCount, size_t maxIterations)
{
	Config cfg;
	cfg.popSize = 1;
	cfg.generations = maxIterations;
	cfg.beginTemperature = beginTemperature;
	cfg.coolingRate = coolingRate;
	cfg.neighborsCount = neighborsCount;
	cfg.maxIterations = maxIterations;
	return cfg;
}

Config::Config(){} //default;




MetaAlgorithm::MetaAlgorithm(const Problem& problem, const Config& config)
	:
	config(config),
	pop(config.popSize),
	distanceMatrix(problem.getDistanceMatrix())
{}

MetaAlgorithm::MetaAlgorithm(const MetaAlgorithm& other)
	:
	config(other.config),
	pop(config.popSize),
	distanceMatrix(other.distanceMatrix)
{}

MetaAlgorithm& MetaAlgorithm::operator=(const MetaAlgorithm& other)
{
	this->config = other.config;//good?
	this->pop = other.pop;//good?
	this->distanceMatrix = other.distanceMatrix;
	return *this;
}

MetaAlgorithm::~MetaAlgorithm()
{}

void MetaAlgorithm::run()
{
	//TODO
}
