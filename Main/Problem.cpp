#include "Problem.h"


Problem::Problem()
	:Problem("unknown","","","",std::vector<Point>())
{
}

Problem::Problem(
	std::string name, std::string type, std::string comment, std::string edgeWeightType,
	const std::vector<Point>& nodes) :
	name(name),
	type(type),
	comment(comment),
	dimension(nodes.size()),
	edgeWeightType(edgeWeightType),
	nodes(nodes),
	distances(nodes)
{

}

Problem::Problem(const std::vector<Point>& nodes)
	:
	nodes(nodes),
	dimension(nodes.size()),
	distances(nodes)
{
}

float Problem::calculateFitness(const std::vector<int>& cities) const
{
	float fitness = 0.f;
	size_t i = 1;
	while (i < cities.size())
	{
		fitness += distances.getDistance(cities[i], cities[i - 1]);
		i++;
	}
	return fitness;
}

int Problem::getDimension() const
{
	return dimension;
}

const DistanceMatrix& Problem::getDistanceMatrix() const
{
	return distances;
}

