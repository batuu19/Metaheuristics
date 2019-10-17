#pragma once

#include <iostream>
#include <vector>

#include "Math.h"

class Algorithm
{
public:
	Algorithm();//temp?
	Algorithm(std::string name, std::string type, std::string comment, std::string edgeWeightType,
		const std::vector<Point> &nodes);
private:
	std::string name;
	std::string type;
	std::string comment;
	//int dimension;
	std::string edgeWeightType;
	std::vector<Point> nodes;
};