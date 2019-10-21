#pragma once

#include <iostream>
#include <vector>

#include "Math.h"
#include "Creature.h"

class Problem
{
public:
	Problem();//temp?
	Problem(std::string name, std::string type, std::string comment, std::string edgeWeightType,
		const std::vector<Point>& nodes);
	Problem(const std::vector<Point>& nodes);
	float calculateFitness(const Creature& c);
private:
	std::string name;
	std::string type;
	std::string comment;
	//int dimension;
	std::string edgeWeightType;
	std::vector<Point> nodes;
	std::vector<std::vector<float>> distances;

	void calculateDistances();
};