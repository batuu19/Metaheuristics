#pragma once
#include "Creature.h"
#include <vector>
#include <random>
#include <algorithm>

struct AgedCreature
{
public:
	AgedCreature(const Creature& creature, int age = 0);
	AgedCreature(DistanceMatrix* distanceMatrix, int age = 0);
	Creature creature;
	int age;
};

class AgedPopulation
{
public:
	AgedPopulation(size_t size);
	void init(std::mt19937& rng, DistanceMatrix* distanceMatrix);

	AgedCreature selection(std::mt19937& rng, size_t tSize);
	void addCreature(AgedCreature& creature);
	size_t getCreaturesCount() const;

	const std::vector<AgedCreature>& getSortedCreatures();

	int removeDuplicates();
private:
	size_t size;
	std::vector<AgedCreature> creatures;
	std::uniform_int_distribution<size_t> sizeDist;
	float percentBase = 0.1;
};
