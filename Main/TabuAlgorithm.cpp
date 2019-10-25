#include "TabuAlgorithm.h"

TabuAlgorithm::TabuAlgorithm(const Problem& problem)
	:
	best(problem.getDistanceMatrix()),
	citiesCount(problem.getDimension())
{
}

void TabuAlgorithm::run(std::mt19937 & rng)
{
	best.init(rng);

	auto bestFitness = best.getFitness();

	std::uniform_int_distribution<size_t> pointDist(0,citiesCount);
	std::vector<Creature> neighbors;
	while (!endCondition())
	{
		neighbors = best.getPointNeighbors(pointDist(rng));
		std::sort(neighbors.begin(),neighbors.begin(),
			[](const Creature& c1, const Creature& c2) {
			return c1.getFitness() < c2.getFitness();
		});

	}
}

bool TabuAlgorithm::endCondition()
{
	return false;
}
