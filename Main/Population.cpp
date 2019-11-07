#include "Population.h"
#include "Utils.h"
#include <algorithm>

Population::Population(size_t size)
	:
	size(size)
{
}

void Population::init(std::mt19937& rng,DistanceMatrix* distanceMatrix)
{
    for (size_t i = 0; i < size; ++i) {
        creatures.emplace_back(distanceMatrix);
    }
	for (auto& c : creatures)
		c.init(rng);

}

Creature Population::selection(std::mt19937& rng,size_t tSize)
{
	std::shuffle(creatures.begin(),creatures.end(),rng);

	std::sort(creatures.begin(),creatures.begin() + tSize,
		[](const Creature& c1,const Creature& c2){
			return c1.getFitness() < c2.getFitness();
		});
	return creatures[0];
}


void Population::addCreature(Creature& creature)
{
	creatures.push_back(creature);
}

size_t Population::getCreaturesCount() const
{
	return creatures.size();
}

const std::vector<Creature>& Population::getSortedCreatures()
{
	std::sort(creatures.begin(), creatures.end(),
		[](const Creature& c1, const Creature& c2) {
			return c1.getFitness() < c2.getFitness();
		});

	return creatures;
}

Creature& Population::getFirst()
{
	return creatures[0];
}
