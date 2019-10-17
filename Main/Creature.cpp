#include "Creature.h"

Creature::Creature(int citiesCount)
	:
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
}
