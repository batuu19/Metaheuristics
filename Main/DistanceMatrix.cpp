#include "DistanceMatrix.h"

DistanceMatrix::DistanceMatrix(const std::vector<Point>& nodes)
	:
	size(nodes.size())
{
	matrix = new float* [size];

	for (size_t i = 0; i < size; i++)
	{
		matrix[i] = new float[i];//what for j=0?
		for (size_t j = 0; j < i; j++)
		{
			matrix[i][j] = distance(nodes[i], nodes[j]);
		}
	}
}

DistanceMatrix::~DistanceMatrix()
{
	for (size_t i = 0; i < size; i++)
	{
		delete matrix[i];
	}
	delete matrix;
}

float DistanceMatrix::getDistance(int from, int to) const
{
	if (from == 0 && to == 0)
	{
		from = 0;
	}
	if (from < to)std::swap(from, to);//from bigger to smaller
	return matrix[from][to];
}

size_t DistanceMatrix::getSize() const
{
	return size;
}
