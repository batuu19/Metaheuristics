#include "DistanceMatrix.h"

DistanceMatrix::DistanceMatrix(const std::vector<Point>& nodes)
{
	auto size = nodes.size();
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

float DistanceMatrix::getDistance(int from, int to) const
{
    if(from ==0 && to == 0)
    {
        from = 0;
    }
	if (from < to)std::swap(from, to);//from bigger to smaller
	return matrix[from][to];
}

size_t DistanceMatrix::getSize() const
{
	return matrix.size();
}
