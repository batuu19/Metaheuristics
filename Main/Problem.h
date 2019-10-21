#pragma once

#include <iostream>
#include <vector>

#include "Math.h"
//#include "Creature.h"
#include "DistanceMatrix.h"

class Problem
{
public:
	Problem();//temp?
	Problem(std::string name, std::string type, std::string comment, std::string edgeWeightType,
		const std::vector<Point>& nodes);
	Problem(const std::vector<Point>& nodes);

	int getDimension() const;
	const DistanceMatrix& getDistanceMatrix() const;

private:
	std::string name;
	std::string type;
	std::string comment;
	int dimension;
	std::string edgeWeightType;
	std::vector<Point> nodes;
	DistanceMatrix distances;
};