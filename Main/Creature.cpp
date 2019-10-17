#include "Creature.h"

Creature::Creature(int citiesCount)
	:
	citiesCount(citiesCount),
	cities(citiesCount),
	dist(0, citiesCount)
{}

void Creature::init(std::mt19937& rng)
{
	std::iota(cities.begin(), cities.end(), 0);
	std::shuffle(cities.begin(), cities.end(), rng);
}

void Creature::mutate(std::mt19937& rng)
{
	int i = dist(rng);
	int j;
	do
	{
		j = dist(rng);
	} while (i == j);

	std::swap(cities[i], cities[j]);
}

void Creature::crossover(Creature& other, std::mt19937& rng)
{
	int x = dist(rng);
	std::vector<int> newOrder(citiesCount);
	for (int i = 0; i < x; i++)
		newOrder[i] = cities[i];
	for (int i = x; i < citiesCount; i++)
		newOrder[i] = other.cities[i];

	
	
}

void Creature::repairCrossover()
{
}
