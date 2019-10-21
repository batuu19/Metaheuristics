#include "DistanceMatrix.h"

DistanceMatrix::DistanceMatrix(const std::vector<Point>& nodes)
{
	int size = nodes.size();
	std::vector<float> line;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			line.push_back(distance(nodes[i], nodes[j]));
		}
		matrix.push_back(line);
		line.clear();
	}
}

float DistanceMatrix::getDistance(int from, int to)
{
	if (from > to)std::swap(from, to);
	return matrix[from][to];
}
