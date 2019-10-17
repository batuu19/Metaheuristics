#pragma once

#include <vector>
#include <random>

#include "Creature.h"

class Population
{
public:
	Population();

	void selection();

private:
	size_t size;
	std::vector<Creature> creatures;
};
