#include "GAAlgorithm.h"

void GAAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;

	csvFile.open("ga.csv");
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
				if (percentageDist(rng) < OX_TO_PMX_PROB)
				{
					auto c12 = c1.crossoverOX(c2, rng);
					auto c21 = c2.crossoverOX(c1, rng);
					c1 = c12;
					c2 = c21;
				}
				else
				{
					auto vec = c1.crossoverPMX(c2, rng);
					c1 = vec[0];
					c2 = vec[1];
				}

			}
			if (percentageDist(rng) < config.pm)
			{
				if (percentageDist(rng) < SWAP_TO_INV_PROB)
					c1.mutateSwap(rng);
				else
					c1.mutateInv(rng);
			}
			if (percentageDist(rng) < config.pm)
			{
				if (percentageDist(rng) < SWAP_TO_INV_PROB)
					c2.mutateSwap(rng);
				else
					c1.mutateInv(rng);
			}

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
}


