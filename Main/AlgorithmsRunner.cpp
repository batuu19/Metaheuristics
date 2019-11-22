#include "AlgorithmsRunner.h"

AlgorithmsRunner::AlgorithmsRunner(size_t runCount, std::vector<AlgorithmType> types)
{
}

AlgorithmsRunner::AlgorithmsRunner(size_t runCount)
{
}

float *** AlgorithmsRunner::run(std::mt19937 & rng)
{
	MetaAlgorithm* algorithm;
	float*** results = new float**[Instance::count];//[instance][algType][num]
	for (size_t inst = 0; inst < Instance::count; inst++)
	{
		results[inst] = new float*[static_cast<int>(AlgorithmType::NONE)];
		for (size_t alg = 0; alg < static_cast<int>(AlgorithmType::NONE); alg++)
		{
			results[inst][alg] = new float[runCount];
		}
	}for (auto instance : instances)
	{
		std::cout << instance.name << " ";
		Problem problem = Loader::loadData(TSP_DIRECTORY + instance.name + ".tsp");
		size_t totalCreatureCount = 100;
		for (size_t i = 0; i < runCount; i++)
		{
			std::cout << i << " ";
			Config greedyConfig = Config::getGreedyConfig(i, instance.name, totalCreatureCount);
			Config gaConfig = Config::getGAConfig(i, instance.name, 100, 100, 0.85, 0.02, 10, Mutation::SWAP, Crossover::OX);
			Config tsConfig = Config::getTabuConfig(i, instance.name, 4, totalCreatureCount);
			Config saConfig = Config::getSAConfig(i, instance.name, 1500.f, 0.995, 5, totalCreatureCount);

			results[instance.id][0][i] = Creature::getRandomCreature(problem, rng).getFitness();

			algorithm = new GreedyAlgorithm(problem, greedyConfig);
			results[instance.id][1][i] = algorithm->run(rng);
			delete algorithm;

			algorithm = new GAAlgorithm(problem, gaConfig);
			results[instance.id][2][i] = algorithm->run(rng);
			delete algorithm;

			algorithm = new TabuAlgorithm(problem, tsConfig);
			results[instance.id][3][i] = algorithm->run(rng);
			delete algorithm;

			algorithm = new SAAlgorithm(problem, saConfig);
			results[instance.id][4][i] = algorithm->run(rng);
			delete algorithm;
		}
		std::cout << std::endl;

	}
	saveResultsToFile(results, runCount);
	return results;//remember delete
}

void AlgorithmsRunner::run(std::mt19937 & rng, std::string filename)
{
}

std::string AlgorithmsRunner::getCSVLine(float * results, size_t runCount)
{
	return std::string();
}

void AlgorithmsRunner::saveResultsToFile(float *** results, size_t runCount)
{
}
