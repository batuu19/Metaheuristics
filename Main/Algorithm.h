#pragma once

#include <iostream>

static constexpr size_t DEFAULT_POPSIZE = 100;
static constexpr size_t DEFAULT_GENERATIONS = 100;
static constexpr float DEFAULT_PX = 0.01f;
static constexpr float DEFAULT_PX = 0.1f;


class Config
{
public:
	Config();
	Config(size_t popsize, size_t generations, float px, float pm);
	Config(std::string filename);

	bool isInitialized() { return initialized; };
private:
	bool initialized = false;
	size_t popSize;
	size_t generations;
	float px, pm;//crossover, mutation
	friend class Algorithm;
};

#include "Population.h"

class Algorithm
{
public:
	Config config;
private:
	Population pop;

};