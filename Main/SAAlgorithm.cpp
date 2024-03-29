#include "SAAlgorithm.h"

float SAAlgorithm::run(std::mt19937& rng)
{
	//CSV FILE
	std::ofstream csvFile;
	csvFile.open(config.filenamePrefix + ".csv");
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
	std::uniform_int_distribution<size_t> pointDist(0, citiesCount - 1);
	while (generation < config.maxIterations)
	{
		neighbors.clear();
		//neighbors = best.getPointNeighbors(pointDist(rng));
		//neighbors = best.getPointNeighbors(pointDist(rng));
		neighbors = best.getInvNeighbors(rng,config.neighborsCount);
		std::sort(neighbors.begin(), neighbors.end());



		if (neighbors[0] < best)
		{
			best = neighbors[0];
		}
		else
		{
			auto value = expf(
				(best.getFitness() - neighbors[0].getFitness()) / (float)temperature);
			//(neighbors[0].getFitness() - best.getFitness()) / (float)temperature);
			auto percentage = percentageDist(rng);
			if (percentage < value)
			{
				best = neighbors[0];
			}
		}
		bestFitness = std::min(bestFitness, best.getFitness());

		csvFile <<
			generation << "," <<
			best.getFitness() << "," <<
			(*neighbors.rbegin()).getFitness() << "," <<
			bestFitness << "," <<
			temperature <<
			std::endl;
		temperature *= static_cast<float>( config.coolingRate);
		//temperature -= beginTemp / DEFAULT_MAX_GENERATIONS_W;
		generation++;
	}
	csvFile.close();
	return bestFitness;
}
