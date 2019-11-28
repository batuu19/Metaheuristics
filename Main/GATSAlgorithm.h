#pragma once
#include "MetaAlgorithm.h"
#include "GAAlgorithm.h"
#include "TabuList.h"
//
//static constexpr char CSV_FIRST_LINE[] = "generation, worst, medium, best\n";

class GATSAlgorithm : public MetaAlgorithm
{
public:
	GATSAlgorithm(const Problem& problem, const Config& config) :
		MetaAlgorithm(problem, config),
		nDist(0, citiesCount* config.pm),//here
		nTabu(config.popSize * 0.1)
	{};
	float run(std::mt19937& rng) override;
private:
	void tabuRun(Creature& c, std::mt19937& rng);//work on c, not copy
private:
	std::normal_distribution<float> nDist;
	int nTabu;
	TabuList tl;

};
