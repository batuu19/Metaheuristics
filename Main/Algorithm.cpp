#include "Algorithm.h"

Config::Config()
	:Config(DEFAULT_POPSIZE,DEFAULT_GENERATIONS,DEFAULT_PX,DEFAULT_PM)
{}

Config::Config(size_t popsize, size_t generations, float px, float pm)
	:
	popSize(popSize),
	generations(generations),
	px(px),
	pm(pm)
{
}