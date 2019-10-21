#include "Population.h"

void Population::init(std::mt19937& rng,const DistanceMatrix& distanceMatrix)
{
    size = distanceMatrix.getSize();
    for (size_t i = 0; i < size; ++i) {
        creatures.emplace_back(distanceMatrix);
    }
}

void Population::selection(std::mt19937& rng)
{
	//calculate fitness for each creature
	for (auto& c : creatures) 
	{
		c.calculateFitness();
	}
	//make tournament for population

	//
}
