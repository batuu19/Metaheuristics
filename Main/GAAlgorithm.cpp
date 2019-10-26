#include "GAAlgorithm.h"

Config::Config()
	: Config(-1, DEFAULT_POPSIZE, DEFAULT_GENERATIONS, DEFAULT_PX, DEFAULT_PM, DEFAULT_TSIZE)
{}

Config::Config(int id, size_t popSize, size_t generations, float px, float pm, size_t tSize)
	:
	id(id),
	popSize(popSize),
	generations(generations),
	px(px),
	pm(pm),
	tSize(tSize)
{
	if (tSize > popSize)
		this->tSize = (size_t)((float)popSize * 0.1f);
}

std::string Config::getFileName()
{
	std::stringstream ss;
	ss << "CSV\\configID" << id;
	return ss.str();
}

void Config::saveToFile()
{
	std::ofstream cfgFile;
	cfgFile.open(getFileName() + ".cfg");
	cfgFile << "POPSIZE: " << popSize << std::endl;
	cfgFile << "GENERATIONS: " << generations << std::endl;
	cfgFile << "PX: " << px << std::endl;
	cfgFile << "PM: " << pm << std::endl;
	cfgFile << "TSIZE: " << tSize << std::endl;
	cfgFile.close();
}

GAAlgorithm::GAAlgorithm(Config config, DistanceMatrix* distanceMatrix)
	:
	config(config),
	distanceMatrix(distanceMatrix),
	pop(config.popSize)
{}

GAAlgorithm::GAAlgorithm(const GAAlgorithm& other)
	:
	config(other.config),
	pop(other.pop),
	distanceMatrix(other.distanceMatrix)
{
}

GAAlgorithm& GAAlgorithm::operator=(const GAAlgorithm& other)
{
	this->config = other.config;
	this->pop = other.pop;
	this->distanceMatrix = other.distanceMatrix;
	return *this;
}

GAAlgorithm::~GAAlgorithm()
{}//do nothing, do not delete distance matrix

std::pair<int, std::string> GAAlgorithm::run(std::mt19937& rng)
{
	std::ofstream csvFile;

	csvFile.open(config.getFileName() + ".csv");
	pop.init(rng, distanceMatrix);
	csvFile << CSV_FIRST_LINE;

	std::pair<int, std::string> out;
	out.second = config.getFileName();

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

	out.first = pop.getSortedCreatures()[0].getFitness();

	return out;
}


