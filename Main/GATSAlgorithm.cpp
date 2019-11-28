#include "GATSAlgorithm.h"

float GATSAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;
	csvFile.open(config.filenamePrefix + ".csv");
	csvFile << CSV_FIRST_LINE;
	bool tabu = false;
	pop.init(rng, distanceMatrix);
	for (size_t gen = 0; gen < config.generations; gen++)
	{
		Population newPop = Population(config.popSize);
		size_t creaturesCount = 0;
		if (gen % nTabu == 1)
			tabu = true;
		for (auto c : pop.getCreatures())
			tl.push(c);
		while (creaturesCount < config.popSize - 1)//because putting always 2 at back
		{
			auto c1 = pop.selection(rng, config.tSize);
			auto c2 = pop.selection(rng, config.tSize);
			if (tabu)
			{
				tabuRun(c1, rng);
				tabuRun(c2, rng);
			}
			if (percentageDist(rng) < config.px)
			{
				auto c12 = c1.crossoverPMX(c2, rng);
				auto c21 = c2.crossoverPMX(c1, rng);
				c1 = c12;
				c2 = c21;
			}

			int swapCount = std::abs(nDist(rng));//using pm here
			c1.mutateSwap(rng, swapCount);
			c2.mutateSwap(rng, swapCount);

			newPop.addCreature(c1);
			newPop.addCreature(c2);
			creaturesCount += 2;
			tl.push(c1);
			tl.push(c2);
		}

		if (creaturesCount == config.popSize - 1)
		{
			auto c = Creature(distanceMatrix);
			c.init(rng);
			newPop.addCreature(c);
		}
		//swap populations
		std::swap(pop, newPop);

		auto vec = pop.getSortedCreatures();
		csvFile << gen << ","
			<< vec[config.popSize - 1].getFitness() << ","
			<< vec[config.popSize / 2].getFitness() << ","
			<< vec[0].getFitness()
			<< std::endl;
	}
	csvFile.close();
	return pop.getSortedCreatures()[0].getFitness();
}

void GATSAlgorithm::tabuRun(Creature& c, std::mt19937& rng)
{
	std::vector<Creature> neighbors;
	std::set<Creature> sorted;
	size_t it = 1;
	while (it < config.maxIterations)
	{
		neighbors.clear();
		sorted.clear();
		neighbors = c.getRandomNeighbors(rng, config.neighborsCount);
		std::copy_if(neighbors.begin(), neighbors.end(), std::inserter(sorted, sorted.begin()),
			[this](const Creature& c)
			{return !tl.contains(c); });
		if (!sorted.empty())
			c = *sorted.begin();
		it++;
	}
}
