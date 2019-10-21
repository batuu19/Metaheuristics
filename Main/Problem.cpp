#include "Problem.h"


Problem::Problem()
	:Problem("unknown","","no comment","",std::vector<Point>())
{
}

Problem::Problem(
	std::string name, std::string type, std::string comment, std::string edgeWeightType, 
	const std::vector<Point>& nodes) :
	name(name),
	type(type),
	comment(comment),
	edgeWeightType(edgeWeightType),
	nodes(nodes)
{

}

Problem::Problem(const std::vector<Point>& nodes)
{
}

float Problem::calculateFitness(const Creature& c)
{
	return 0.0f;
}

void Problem::calculateDistances()
{
	int size = nodes.size();
	std::vector<float> line;
	if (!distances.empty())
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j <= i; j++)
			{
				line.push_back(distance(nodes[i], nodes[j]));
			}
			distances.push_back(line);
		}
	}
}
