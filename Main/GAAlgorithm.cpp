#include "GAAlgorithm.h"

float GAAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;
	csvFile.open(config.filenamePrefix + ".csv");
	pop.init(rng, distanceMatrix);
	csvFile << CSV_FIRST_LINE;
	float best = std::numeric_limits<float>::max();
	int swapCount;
	auto lastSorted = pop.getSortedCreatures();
	for (size_t i = 0; i < config.generations; i++)
	{
		Population newPop = Population(config.popSize);
		size_t creaturesCount = 0;
		while (creaturesCount < config.popSize - 3)//because putting n 
		{
			//ruletka?
			auto c1 = std::move(pop.selection(rng, config.tSize));
			Creature c11 = Creature(c1);
			auto c2 = std::move(pop.selection(rng, config.tSize));
			if (percentageDist(rng) < config.px)
			{
				c1 = std::move(c1.crossoverPMX(c2, rng));
			}
			if (percentageDist(rng) < config.px)
			{
				c2 = std::move(c2.crossoverPMX(c11, rng));
			}

			if (percentageDist(rng) < config.pm)
			{
				c1.mutateInv(rng);
			}
			if (percentageDist(rng) < config.pm)
			{
				c2.mutateInv(rng);
			}
			newPop.addCreature(c1);
			newPop.addCreature(c2);
			creaturesCount += 2;
		}

		while (creaturesCount < config.popSize)
		{
			auto c = Creature(distanceMatrix);
			c.init(rng);
			newPop.addCreature(c);
			creaturesCount++;
		}

		//swap populations
		std::swap(pop, newPop);

		lastSorted = pop.getSortedCreatures();
		csvFile << i << ","
			<< lastSorted[config.popSize - 1].getFitness() << ","
			<< lastSorted[config.popSize / 2].getFitness() << ","
			<< lastSorted[0].getFitness()
			<< std::endl;
		best = std::min(best, lastSorted[0].getFitness());
	}
	csvFile.close();

	return best;
}


