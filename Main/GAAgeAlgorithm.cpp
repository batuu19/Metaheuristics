#include "GAAgeAlgorithm.h"

float GAAgeAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;

	csvFile.open(config.filenamePrefix + ".csv");
	agedPop.init(rng, distanceMatrix);
	csvFile << "generation, worst, medium, best\n";
	for (size_t i = 0; i < config.generations; i++)
	{
		AgedPopulation newAgedPop = AgedPopulation(config.popSize);
		size_t creaturesCount = 0;
		while (creaturesCount < config.popSize - 1)//because putting always 2 at back
		{
			auto c1 = agedPop.selection(rng, config.tSize);
			auto c2 = agedPop.selection(rng, config.tSize);
			if (percentageDist(rng) < config.px)
			{
				auto c12 = c1.creature.crossoverPMX(c2.creature, rng);
				auto c21 = c2.creature.crossoverPMX(c1.creature, rng);
				c1 = c12;
				c2 = c21;
			}

			int swapCount = std::abs(nDist(rng));//using pm here
			c1.creature.mutateSwap(rng, swapCount);
			c2.creature.mutateSwap(rng, swapCount);

			newAgedPop.addCreature(c1);
			newAgedPop.addCreature(c2);
			creaturesCount += 2;
		}
		creaturesCount -= newAgedPop.removeDuplicates();//remove duplicates and creaturesCount - duplicatesCount
		while (creaturesCount < config.popSize)
		{
			auto c = AgedCreature(distanceMatrix);
			c.creature.init(rng);
			newAgedPop.addCreature(c);
			creaturesCount++;
		}

		//swap populations
		std::swap(agedPop, newAgedPop);

		auto vec = agedPop.getSortedCreatures();
		csvFile << i << ","
			<< vec[config.popSize - 1].creature.getFitness() << ","
			<< vec[config.popSize / 2].creature.getFitness() << ","
			<< vec[0].creature.getFitness()
			<< std::endl;
		//std::cout << i << std::endl;
	}
	csvFile.close();

	return agedPop.getSortedCreatures()[0].creature.getFitness();
}
