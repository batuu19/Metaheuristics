#pragma once

#include <vector>
#include <random>

#include "Creature.h"

class Population
{
public:
    void init(std::mt19937 &rng, DistanceMatrix* distanceMatrix);

    Creature selection(std::mt19937 &rng,size_t tSize);

	void addCreature(Creature& creature);
	size_t getCreaturesCount() const;

private:
    std::vector<Creature> creatures;

};
