#pragma once

#include <vector>
#include <random>

#include "Creature.h"

class Population
{
public:
	Population(size_t size);
	void init(std::mt19937& rng, DistanceMatrix* distanceMatrix);

	Creature selection(std::mt19937& rng, size_t tSize);

	void addCreature(Creature& creature);
	size_t getCreaturesCount() const;

	const std::vector<Creature>& getSortedCreatures();
	Creature& getFirst();
private:
	size_t size;
	std::vector<Creature> creatures;

};
