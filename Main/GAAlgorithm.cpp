#include "GAAlgorithm.h"

float GAAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;

	csvFile.open(config.filenamePrefix + ".csv");
	pop.init(rng, distanceMatrix);
	csvFile << CSV_FIRST_LINE;
	for (size_t i = 0; i < config.generations; i++)
	{
		Population newPop = Population(config.popSize);
		size_t creaturesCount = 0;
		while (creaturesCount < config.popSize - 1)//because putting always 2 at back
		{
			auto c1 = pop.selection(rng, config.tSize);
			auto c2 = pop.selection(rng, config.tSize);
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
		csvFile << i << ","
			<< vec[config.popSize - 1].getFitness() << ","
			<< vec[config.popSize / 2].getFitness() << ","
			<< vec[0].getFitness()
			<< std::endl;
		//std::cout << i << std::endl;
	}
	csvFile.close();

	return pop.getSortedCreatures()[0].getFitness();
}


