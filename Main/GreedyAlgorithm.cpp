#include "GreedyAlgorithm.h"

float GreedyAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;
	csvFile.open(config.filenamePrefix + ".csv");
	csvFile << "generation,best\n";

	pop.init(rng, distanceMatrix);
	auto best = pop.getFirst();
	std::vector<Creature> neighbors;
	size_t generation = 0;
	bool end = false;
	while (!end || generation < config.maxIterations)
	{
		csvFile << generation << best.getFitness()<<std::endl;
		neighbors = best.getAllNeighbors();
		std::sort(neighbors.begin(), neighbors.end());
		if (neighbors[0] >= best)end = true;
		else
		{
			best = neighbors[0];
			generation++;
		}
	};
	csvFile.close();
	return best.getFitness();
	
}
