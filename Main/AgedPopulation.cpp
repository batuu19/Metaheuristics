#include "AgedPopulation.h"

AgedCreature::AgedCreature(const Creature& creature, int age)
	:
	creature(creature),
	age(age)
{}

AgedCreature::AgedCreature(DistanceMatrix* distanceMatrix, int age)
	:
	creature{ distanceMatrix },
	age{ age }
{}

AgedPopulation::AgedPopulation(size_t size)
	:
	size(size),
	sizeDist(0, size - 1)
{}

void AgedPopulation::init(std::mt19937& rng, DistanceMatrix* distanceMatrix)
{
	creatures.reserve(size);

	for (size_t i = 0; i < size; ++i) {
		creatures.emplace_back(distanceMatrix);
	}
	for (auto& c : creatures)
		c.creature.init(rng);
}

AgedCreature AgedPopulation::selection(std::mt19937& rng, size_t tSize)
{
	AgedCreature* bestC;
	AgedCreature* c;

	bestC = &creatures[sizeDist(rng)];
	while (--tSize > 0)
	{
		c = &creatures[sizeDist(rng)];
		bestC = std::min(bestC, c, [this](AgedCreature* c1, AgedCreature* c2)
			{
				if (c1->creature < c2->creature && c1->age < maxAge)
					return true;
				else if (c2->creature < c1->creature && c2->age < maxAge)
					return false;
				else
					return c1->age < c2->age;
			});
	}
	bestC->age++;
	return *bestC;
}

void AgedPopulation::addCreature(AgedCreature& creature)
{
	creatures.push_back(creature);
}

size_t AgedPopulation::getCreaturesCount() const
{
	return creatures.size();
}

const std::vector<AgedCreature>& AgedPopulation::getSortedCreatures()
{
	std::sort(creatures.begin(), creatures.end(), [](const AgedCreature& c1, const AgedCreature& c2) 
		{return c1.creature < c2.creature; });
	return creatures;
}

int AgedPopulation::removeDuplicates()
{
	auto eraseBegin = std::unique(creatures.begin(), creatures.end(), [](const AgedCreature& c1, const AgedCreature& c2)
		{
			return c1.creature.getHash() == c2.creature.getHash();
		});
	int dCount = std::distance(eraseBegin, creatures.end());
	creatures.erase(eraseBegin,creatures.end());
	return dCount;
}
