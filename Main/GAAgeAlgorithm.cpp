#include "GAAgeAlgorithm.h"

float GAAgeAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;

	csvFile.open(config.filenamePrefix + ".csv");
	agedPop.init(rng, distanceMatrix);
	csvFile << "generation, worst, medium, best\n";
	int swapCount;
	float best = std::numeric_limits<float>::max();
	for (size_t i = 0; i < config.generations; i++)
	{
		AgedPopulation newAgedPop = AgedPopulation(config.popSize);
		size_t creaturesCount = 0;
		while (creaturesCount < config.popSize - 1)//because putting always 2 at back
		{
			auto c1 = std::move(agedPop.selection(rng, config.tSize));
			auto c2 = std::move(agedPop.selection(rng, config.tSize));
			AgedCreature c11 = AgedCreature(c1);
			if (percentageDist(rng) < config.px)
			{
				c1 = std::move(c1.creature.crossoverPMX(c2.creature, rng));
			}
			if (percentageDist(rng) < config.px)
			{
				c2 = std::move(c2.creature.crossoverPMX(c11.creature, rng));
			}
			swapCount = swapDist(rng);
			if (swapCount > 0)
			{
				c1.creature.mutateSwap(rng, swapCount);
			}
			swapCount = swapDist(rng);
			if (swapCount > 0)
			{
				c2.creature.mutateSwap(rng, swapCount);
			}

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
		best = std::min(best, vec[0].creature.getFitness());
	}
	csvFile.close();

	return best;
}
