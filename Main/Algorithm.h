#pragma once

#include <iostream>
#include <vector>

#include "Math.h"

class Algorithm
{
public:

private:
	std::string name;
	std::string type;
	std::string comment;
	int dimension;
	std::string edgeWeightType;
	std::vector<Point> nodes;
};