
#include <random>
#include <iostream>
#include <cstdio>

#include "Loader.h"
#include "Problem.h"
#include "Loader.h"
#include "Utils.h"

#include "GAAlgorithm.h"
#include "TabuAlgorithm.h"
#include "SAAlgorithm.h"
#include "GreedyAlgorithm.h"
#include "Instance.h"

const static std::vector<Instance> instances = Instance::getInstances();


std::string getCSVLine(float* results, size_t count)
{
	double sum = std::accumulate(results, results + count, 0.0);
	double avg = sum / count;
	double standardDeviation = 0.0;
	for (size_t i = 0; i < count; i++)
	{
		standardDeviation += std::pow(results[i] - avg, 2);
	}

	standardDeviation = std::sqrt(standardDeviation / (double)count);
	std::sort(results, results + count);
	std::stringstream ss;
	ss << avg << "," << results[0] << "," << results[count - 1] << "," << standardDeviation;
	return ss.str();
}

void saveToFile(float*** results, size_t count)//[instance][algType][num]
{
	std::string fileName = "badania.csv";
	std::ofstream file;
	file.open(fileName);
	file << "name,optimum,randAvg,randMin,randMax,randSD,greedyAvg,greedyMin,greedyMax,greedySD,gaAvg,gaMin,gaMax,gaSD,tabuAvg,tabuMin,tabuMax,tabuSD,saAvg,saMin,saMax,saSD\n";
	for (size_t inst = 0; inst < Instance::count; inst++)
	{
		file << instances[inst].name << "," << instances[inst].optimumValue;
		size_t nexti = inst + 5;
		for (size_t alg = 0; alg < static_cast<int>(AlgorithmType::NONE); alg++)
		{
			file << "," << getCSVLine(results[inst][alg], count);
		}
		file << std::endl;

	}
}

int main()
{
	//null ptr exception somewhere
	const int runCount = 10;
	std::mt19937 rng(std::random_device{}());
	MetaAlgorithm* algorithm;
	float*** results = new float** [Instance::count];//[instance][algType][num]
	for (size_t inst = 0; inst < Instance::count; inst++)
	{
		results[inst] = new float* [static_cast<int>(AlgorithmType::NONE)];
		for (size_t alg = 0; alg < static_cast<int>(AlgorithmType::NONE); alg++)
		{
			results[inst][alg] = new float[runCount];
		}
	}
	for (auto instance : instances)
	{
		std::cout << instance.name << " ";
		Problem problem = Loader::loadData(TSP_DIRECTORY + instance.name + ".tsp");
		size_t totalCreatureCount = 100;
		for (size_t i = 0; i < runCount; i++)
		{
			std::cout << i << " ";
			Config greedyConfig = Config::getGreedyConfig(i, instance.name, totalCreatureCount);
			Config gaConfig = Config::getGAConfig(i, instance.name, 100, 100, 0.85, 0.02, 10, Mutation::SWAP, Crossover::PMX);
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
	saveToFile(results, runCount);
	for (size_t inst = 0; inst < Instance::count; inst++)
	{
		for (size_t alg = 0; alg < static_cast<int>(AlgorithmType::NONE); alg++)
		{
			delete results[inst][alg];
		}
		delete results[inst];
	}
	delete results;
}
