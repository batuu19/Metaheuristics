#include "Population.h"
#include "Utils.h"
#include <algorithm>

void Population::init(std::mt19937& rng,DistanceMatrix* distanceMatrix)
{
    size = distanceMatrix->getSize();
    for (size_t i = 0; i < size; ++i) {
        creatures.emplace_back(distanceMatrix);
    }
}

Creature Population::selection(std::mt19937& rng,size_t tSize)
{
	std::shuffle(creatures.begin(),creatures.end(),rng);

	std::sort(creatures.begin(),creatures.begin() + tSize,
		[](const Creature& c1,const Creature& c2){
			return c1.getFitness() > c2.getFitness();
		});
	return creatures[0];
}

bool Population::isPopulationFilled()
{
    return creatures.size() == size;
}
