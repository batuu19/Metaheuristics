#pragma once

#include<vector>
#include<random>
#include <algorithm>
#include <numeric>
#include <set>
class Creature
{
public:
	Creature(int citiesCount);
	void init(std::mt19937& rng);
	void mutateSwap(std::mt19937& rng);
	void mutateInv(std::mt19937& rng);
	Creature crossoverOX(Creature& other, std::mt19937& rng);
	Creature crossoverPMX(Creature& other, std::mt19937& rng);
private:
	std::vector<int> cities;
	int citiesCount;
	std::uniform_int_distribution<size_t> dist;

};
