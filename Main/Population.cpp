#include "Population.h"
#include "Utils.h"
#include <algorithm>
#include <iterator>

Population::Population(size_t size)
	:
	size(size),
	sizeDist(0, size - 1)
{
}

void Population::init(std::mt19937& rng, DistanceMatrix* distanceMatrix)
{
	creatures.reserve(size);
	for (size_t i = 0; i < size; ++i) {
		creatures.emplace_back(distanceMatrix);
	}
	for (auto& c : creatures)
		c.init(rng,true);

}

Creature Population::selection(std::mt19937& rng, size_t tSize)
{
	/*std::set<Creature> out;
	std::sample(creatures.begin(), creatures.end(), std::inserter(out, out.begin()), tSize, rng);
	return *out.begin();*/

	Creature* bestC;
	Creature* c;

	bestC = &creatures[sizeDist(rng)];
	while (--tSize > 0)
	{
		c = &creatures[sizeDist(rng)];
		if (c->getFitness() < bestC->getFitness())
			bestC = c;
	}
	return *bestC;
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

const std::vector<Creature>& Population::getCreatures() const
{
	return creatures;
}

Creature& Population::getFirst()
{
	return creatures[0];
}

void Population::replaceFirst(const Creature& c)
{
	creatures[0] = c;
}
