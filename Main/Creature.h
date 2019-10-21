#pragma once

#include<vector>
#include<random>
#include <algorithm>
#include <numeric>
#include <set>

#include "Problem.h"

class Creature
{
public:
	Creature(const DistanceMatrix& distanceMatrix);
	void init(std::mt19937& rng);
	void mutateSwap(std::mt19937& rng);
	void mutateInv(std::mt19937& rng);
	Creature crossoverOX(Creature& other, std::mt19937& rng);
	std::vector<Creature> crossoverPMX(Creature& other, std::mt19937& rng);
	float getFitness() const;
private:
    void calculateFitness();
	Creature(const DistanceMatrix& distanceMatrix, const std::vector<int>& cities);
	int citiesCount;
	std::vector<int> cities;
	std::uniform_int_distribution<size_t> dist;

	void getRandomBeginEnd(int& begin, int& end, std::mt19937& rng);

	const DistanceMatrix& distanceMatrix;

	float fitness=-1.f;
};
