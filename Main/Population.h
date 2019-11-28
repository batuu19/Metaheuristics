#pragma once

#include <vector>
#include <random>
#include <algorithm>

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
	//for Tabu and SA
	Creature& getFirst();
	void replaceFirst(const Creature& c);//needed?

private:
	size_t size;
	std::vector<Creature> creatures;
	std::uniform_int_distribution<size_t> sizeDist;
};
