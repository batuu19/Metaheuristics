#include "Algorithm.h"

Config::Config()
        : Config(DEFAULT_POPSIZE, DEFAULT_GENERATIONS, DEFAULT_PX, DEFAULT_PM, DEFAULT_TSIZE)
{}

Config::Config(size_t popSize, size_t generations, float px, float pm, size_t tSize)
        :
        popSize(popSize),
        generations(generations),
        px(px),
        pm(pm),
        tSize(tSize)
{
}

Algorithm::Algorithm(Config config, DistanceMatrix* distanceMatrix)
        :
        config(config),
        distanceMatrix(distanceMatrix)
{}

Algorithm::Algorithm(const Algorithm& other)
	:
	config(other.config),
	pop(other.pop),
	distanceMatrix(other.distanceMatrix)
{
}

Algorithm& Algorithm::operator=(const Algorithm& other)
{
	this->config = other.config;
	this->pop = other.pop;
	this->distanceMatrix = other.distanceMatrix;
	return *this;
}

Algorithm::~Algorithm()
{}//do nothing, do not delete distance matrix

void Algorithm::run(std::mt19937 &rng)
{
    pop.init(rng,distanceMatrix);

    for (size_t i = 0; i < config.generations; i++)
    {
        //selekcja
        //pop.selection(rng);


        //crossover

        //mutation

    }
}


