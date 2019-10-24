#pragma once

#include <vector>
#include <random>

#include "Creature.h"

class Population
{
public:
    void init(std::mt19937 &rng, DistanceMatrix* distanceMatrix);

    Creature selection(std::mt19937 &rng,size_t tSize);

    bool isPopulationFilled();

private:
    size_t size = 0;
    std::vector<Creature> creatures;

};
