#include "WAlgorithm.h"

void WAlgorithm::run(std::mt19937& rng)
{
	//CSV FILE
	std::ofstream csvFile;
	csvFile.open("sa.csv");
	csvFile << "generation,best,worst,bestEver,temperature\n";
	pop.init(rng, distanceMatrix);
	auto best = pop.getFirst();

	best.init(rng);
	float bestFitness = best.getFitness();
	std::uniform_real_distribution<float> percentageDist;

	float percentage = percentageDist(rng);
	std::vector<Creature> neighbors;
	neighbors.reserve(config.neighborsCount);
	auto temperature = config.beginTemperature;
	size_t generation = 1;
	while (generation < config.maxIterations)
	{
		neighbors.clear();
		neighbors = best.getRandomNeighbors(rng, config.neighborsCount);
		//neighbors = best.getPointNeighbors(pointDist(rng));

		std::sort(neighbors.begin(), neighbors.end());



		if (neighbors[0] < best)
		{
			best = neighbors[0];
		}
		else
		{
			auto value = std::expf(
				(best.getFitness() - neighbors[0].getFitness()) / (float)temperature);
			//(neighbors[0].getFitness() - best.getFitness()) / (float)temperature);
			auto percentage = percentageDist(rng);
			std::cout << percentage << " " << value << " " << temperature << std::endl;
			if (percentage < value)
			{
				best = neighbors[0];
			}
		}
		bestFitness = std::min(bestFitness, best.getFitness());

		//std::cout << temperature << std::endl;
		std::cout << "best: " << best.getFitness() << "\tBEST_EVER" << bestFitness << std::endl;
		csvFile <<
			generation << "," <<
			best.getFitness() << "," <<
			(*neighbors.rbegin()).getFitness() << "," <<
			bestFitness << "," <<
			temperature <<
			std::endl;
		temperature *= config.coolingRate;
		//temperature -= beginTemp / DEFAULT_MAX_GENERATIONS_W;
		generation++;
	}

	std::cout << "BEST: " << bestFitness << std::endl;
	csvFile.close();
}
