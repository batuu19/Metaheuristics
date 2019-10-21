#include "Population.h"

void Population::init(std::mt19937& rng)
{
	for (auto& c : creatures)
	{
		c.init(rng);
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
