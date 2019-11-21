#include "TabuAlgorithm.h"

float TabuAlgorithm::run(std::mt19937 &rng)
{
	//csv file
	std::ofstream csvFile;
	csvFile.open(config.filenamePrefix + ".csv");
	csvFile << "generation,best,worst,bestEver\n";
	//csv file
	pop.init(rng,distanceMatrix);
	auto best = pop.getFirst();

	auto bestFitness = best.getFitness();
	csvFile << 0 << "," << best.getFitness() << "," << bestFitness << std::endl;
	auto comp = [this](const Creature& c1, const Creature& c2)
	{
		bool containsC1, containsC2;
		containsC1 = tabuList.contains(c1);
		containsC2 = tabuList.contains(c2);
		if (!(containsC1 ^ containsC2))//!xor - 00 11 is true
			return c1.getFitness() < c2.getFitness();
		else
		{
			if (containsC1)
				return true;
			if (containsC2)
				return true;
		}
	};
	std::uniform_int_distribution<size_t> pointDist(0, citiesCount - 1);
	std::vector<Creature> neighbors;
	std::set<Creature> sorted;
	size_t generation = 1;
	while (generation < config.maxIterations)
	{
		neighbors.clear();
		sorted.clear();

		neighbors = best.getRandomNeighbors(rng, config.neighborsCount);

		std::copy_if(neighbors.begin(), neighbors.end(), std::inserter(sorted, sorted.begin()),
			[this](const Creature& c)
		{return !tabuList.contains(c); });

		tabuList.push(best);


		if (best < *sorted.begin())
		{
			best = *sorted.begin();
		}
		//didn't find better 
		else
		{
			best = *(std::next(sorted.begin(), 1));//get second best
		}

		//if improvement
		if (best.getFitness() < bestFitness)
		{
			bestFitness = best.getFitness();
		}

		generation++;


		csvFile << generation << "," <<
			best.getFitness() << "," <<
			bestFitness << "," <<
			(*sorted.rbegin()).getFitness() <<
			std::endl;
	}
	return bestFitness;
}
