#pragma once

#include <iostream>
#include <vector>

#include "Math.h"
//#include "Creature.h"
#include "DistanceMatrix.h"

class Problem
{
public:
	Problem(std::string name, std::string type, std::string comment, std::string edgeWeightType,
		const std::vector<Point>& nodes);
	Problem(const std::vector<Point>& nodes);
	Problem(const Problem&);
	Problem& operator=(const Problem&);
	~Problem();

	size_t getDimension() const;
	DistanceMatrix* getDistanceMatrix();

private:
	std::string name;
	std::string type;
	std::string comment;
	size_t dimension;
	std::string edgeWeightType;
	std::vector<Point> nodes;
	DistanceMatrix* distanceMatrix;
};