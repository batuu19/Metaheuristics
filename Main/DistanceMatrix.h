#pragma once

#include <vector>

#include "Math.h"

class DistanceMatrix
{
public:
	DistanceMatrix(const std::vector<Point>& nodes);
	//DistanceMatrix(const DistanceMatrix&) = delete;
	//DistanceMatrix& operator=(const DistanceMatrix&) = delete;//for sure?
	float getDistance(int from, int to) const;
	size_t getSize() const;
private:
	std::vector<std::vector<float>> matrix;

};