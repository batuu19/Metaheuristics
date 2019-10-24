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
	distanceMatrix(distanceMatrix)
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
		Population newPop = Population();
		size_t creaturesCount = 0;
		while (creaturesCount < config.popSize - 1)//because putting always 2 at back
		{
			auto c1 = pop.selection(rng, config.tSize);
			auto c2 = pop.selection(rng, config.tSize);
			if (percentageDist(rng) < config.px)
			{
				auto c12 = c1.crossoverOX(c2, rng);
				auto c21 = c2.crossoverOX(c1, rng);
				c1 = std::move(c12);
				c2 = std::move(c21);
			}
			if (percentageDist(rng) < config.pm)
			{
				c1.mutateSwap(rng);
			}
			if (percentageDist(rng) < config.pm)
			{
				c1.mutateSwap(rng);
			}

			newPop.addCreature(c1);
			newPop.addCreature(c2);
		}

		if (creaturesCount == config.popSize - 1)
		{
			auto c = Creature(distanceMatrix);
			c.init(rng);
			newPop.addCreature(c);
		}

		//swap populations
		pop = std::move(newPop);
		/*
			dopóki nowa populacja nie jest pe³na
			losuj dwóch rodziców
			sprawdŸ czy crossover
			sprawdŸ czy mutacja
			dodaj osobników do nowej populacji
		*/

	}
}


