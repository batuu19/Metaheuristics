#include "Algorithm.h"

Config::Config()
	:Config(DEFAULT_POPSIZE,DEFAULT_GENERATIONS,DEFAULT_PX,DEFAULT_PM,DEFAULT_TSIZE)
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