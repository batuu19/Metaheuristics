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

void Creature::mutateSwap(std::mt19937& rng)
{
	int first = dist(rng);
	int second;
	do
	{
		second = dist(rng);
	} while (first == second);

	std::swap(cities[first], cities[second]);
}

void Creature::mutateInv(std::mt19937 & rng)
{
	int begin = dist(rng);
	int end;
	do
	{
		end = dist(rng);
	} while (begin == end);

	if (begin > end)
		std::swap(begin, end);

	std::reverse(cities.begin() + begin, cities.begin() + end);
}

Creature Creature::crossoverOX(Creature & other, std::mt19937 & rng)
{
	int begin = dist(rng);
	int end;
	do
	{
		end = dist(rng);
	} while (begin == end);

	if (begin > end)
		std::swap(begin, end);

	//std::vector<int> subVector(cities.begin() + i, cities.begin() + j);
	std::vector<int> newOrder(citiesCount, -1);

	for (size_t index = begin; index < end; index++)
		newOrder[index] = cities[index];
	
	auto sorted = std::set<int>(cities.begin() + begin, cities.begin() + end);
	auto otherSorted = std::set<int>(other.cities.begin(), other.cities.end());
	
	std::vector<int> toInsert;
	std::set_difference(sorted.begin(), sorted.end(), otherSorted.begin(), otherSorted.end(), std::back_inserter(toInsert));


	for (size_t i = 0; i < citiesCount; i++)
	{
		if (i < begin || i >= end) {
			newOrder[i] = toInsert.back();
			toInsert.pop_back();
		}
	}

	auto out = Creature(citiesCount);
	out.cities = std::vector<int>(newOrder);
}

Creature Creature::crossoverPMX(Creature & other, std::mt19937 & rng)
{
	return Creature(0);
}
