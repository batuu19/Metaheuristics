#pragma once

#include <vector>

#include "Math.h"

class DistanceMatrix
{
public:
	DistanceMatrix(const std::vector<Point>& nodes);
	float getDistance(int from, int to) const;
private:
	std::vector<std::vector<float>> matrix;

};