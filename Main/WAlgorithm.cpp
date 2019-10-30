#include "WAlgorithm.h"

WAlgorithm::WAlgorithm(Problem& problem)
	:
	best(problem.getDistanceMatrix())
{
}

void WAlgorithm::run(std::mt19937& rng)
{
	best.init(rng);
	float bestFitness = best.getFitness();
	std::uniform_real_distribution<float> percentageDist;

	float percentage = percentageDist(rng);
	std::vector<Creature> neighbors;
	neighbors.reserve(DEFAULT_NEIGHBORS_COUNT_W);
	size_t generation = 1;
	while (generation < DEFAULT_MAX_GENERATIONS_W)
	{
		neighbors.clear();
		neighbors = best.getRandomNeighbors(rng, DEFAULT_NEIGHBORS_COUNT_W);

		std::sort(neighbors.begin(), neighbors.end());
		if (neighbors[0] < best)
		{
			best = neighbors[0];
			bestFitness = best.getFitness();
		}
		else {
			if (percentageDist(rng) < std::expf(
				(neighbors[0].getFitness() - best.getFitness()) / (float)temperature
			))
			{
				best = neighbors[0];
			}
		}

		std::cout << "best: " << best.getFitness() << "\tBEST_EVER" << bestFitness << std::endl;

		temperature++;
		generation++;
	}

	std::cout << "BEST: " << bestFitness << std::endl;

}
