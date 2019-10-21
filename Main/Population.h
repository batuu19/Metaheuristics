#pragma once

#include <vector>
#include <random>

#include "Creature.h"

class Population
{
public:
    void init(std::mt19937 &rng, const DistanceMatrix &distanceMatrix);

    Creature selection(std::mt19937 &rng,size_t tSize);

    bool isPopulationFilled();

private:
    size_t size;
    std::vector<Creature> creatures;

};
