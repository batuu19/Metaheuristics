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

	cities.clear();

	for (size_t i = 0; i < citiesCount; i++)
		cities[i] = newOrder[i];

	repairCrossover();


}

void Creature::repairCrossover()
{
	std::vector<int> values(citiesCount, 0);
	std::vector<int> places;

	for (size_t i = 0; i < citiesCount; i++)
	{
		if (values[cities[i]] == 0)//first entry
		{
			values[cities[i]]++;
		}
		else
		{
			places.push_back(i);
			values[cities[i]]++;
		}
	}

	//auto needed = std::find_if(values.begin(), values.end(), [](int x) {return x == 0; });
	std::vector<int> missing;

	//get missing numbers
	for (size_t i = 0; i < citiesCount; i++)
	{
		if (values[i] == 0)
			missing.push_back(i);

	}

	//size_t placesCounter = 0;

	for (size_t i = 0; i < citiesCount; i++)
	{
		while (values[i] > 1)
		{
			cities[places.back()] = missing.back();
			places.pop_back();
			missing.pop_back();
		}
	}


}
