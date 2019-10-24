#pragma once

#include<vector>
#include<random>
#include <algorithm>
#include <numeric>
#include <set>
#include <sstream>
#include "Problem.h"

class Creature
{
public:
	Creature(DistanceMatrix* distanceMatrix);
	Creature(const Creature&);
	Creature& operator=(const Creature&);
	~Creature();
	void init(std::mt19937& rng);
	void mutateSwap(std::mt19937& rng);
	void mutateInv(std::mt19937& rng);
	Creature crossoverOX(Creature& other, std::mt19937& rng);
	std::vector<Creature> crossoverPMX(Creature& other, std::mt19937& rng);
	float getFitness() const;
	std::string getInfo() const;
private:
    void calculateFitness();
	Creature(DistanceMatrix* distanceMatrix, const std::vector<int>& cities);
	size_t citiesCount;
	std::vector<int> cities;
	std::uniform_int_distribution<size_t> dist;

	void getRandomBeginEnd(size_t& begin, size_t& end, std::mt19937& rng);

	DistanceMatrix* distanceMatrix;

	float fitness=0.f;
};
