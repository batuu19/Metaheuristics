#include "Algorithm.h"

Config::Config()
	: Config(DEFAULT_POPSIZE, DEFAULT_GENERATIONS, DEFAULT_PX, DEFAULT_PM, DEFAULT_TSIZE)
{}

Config::Config(size_t popSize, size_t generations, float px, float pm, size_t tSize)
	:
	popSize(popSize),
	generations(generations),
	px(px),
	pm(pm),
	tSize(tSize)
{
}

Algorithm::Algorithm(Config config, DistanceMatrix* distanceMatrix)
	:
	config(config),
	distanceMatrix(distanceMatrix),
	pop(config.popSize)
{}

Algorithm::Algorithm(const Algorithm& other)
	:
	config(other.config),
	pop(other.pop),
	distanceMatrix(other.distanceMatrix)
{
}

Algorithm& Algorithm::operator=(const Algorithm& other)
{
	this->config = other.config;
	this->pop = other.pop;
	this->distanceMatrix = other.distanceMatrix;
	return *this;
}

Algorithm::~Algorithm()
{}//do nothing, do not delete distance matrix

void Algorithm::run(std::mt19937& rng)
{
	pop.init(rng, distanceMatrix);

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
		/*
			dopóki nowa populacja nie jest pe³na
			losuj dwóch rodziców
			sprawdŸ czy crossover
			sprawdŸ czy mutacja
			dodaj osobników do nowej populacji
		*/
	}
}


