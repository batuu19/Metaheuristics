
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
	std::mt19937 rng(std::random_device{}());
	std::string instanceName = "kroA100";
	Problem problem = Loader::loadData(TSP_DIRECTORY + instanceName + ".tsp");
	GreedyAlgorithm gra = GreedyAlgorithm(problem, Config::getGreedyConfig(0, "test", 100));
	gra.run(rng);
}
