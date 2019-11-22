#pragma once
#include "Instance.h"
#include "MetaAlgorithm.h"
#include "GAAlgorithm.h"
#include "GreedyAlgorithm.h"
#include "SAAlgorithm.h"
#include "TabuAlgorithm.h"
#include "Loader.h"
#include <random>

const static std::vector<Instance> instances = Instance::getInstances();
class AlgorithmsRunner
{
public:
	AlgorithmsRunner(size_t runCount, std::vector<AlgorithmType> types);
	AlgorithmsRunner(size_t runCount);
	float*** run(std::mt19937& rng);
	void run(std::mt19937& rng, std::string filename);
	static std::string getCSVLine(float* results, size_t runCount);
	static void saveResultsToFile(float*** results, size_t runCount);
	
private:
	size_t runCount;
};
