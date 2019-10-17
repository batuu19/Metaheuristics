#pragma once

#include<vector>
#include<random>
#include <algorithm>
#include <numeric>
class Creature
{
public:
	Creature(int citiesCount);
	void init(std::mt19937& rng);
	void mutate(std::mt19937& rng);
	void crossover(Creature& other, std::mt19937& rng);
private:
	std::vector<int> cities;
	int citiesCount;
	std::uniform_int_distribution<size_t> dist;

	void repairCrossover();
};
