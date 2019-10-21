#pragma once

#include <iostream>
#include <fstream>

static constexpr size_t DEFAULT_POPSIZE = 100;
static constexpr size_t DEFAULT_GENERATIONS = 10;
static constexpr float DEFAULT_PX = 0.01f;
static constexpr float DEFAULT_PM = 0.1f;
static constexpr int DEFAULT_TSIZE = 10;


class Config
{
public:
	Config();
	Config(size_t popsize, size_t generations, float px, float pm,int tSize);

	bool isInitialized() { return initialized; };
private:
	bool initialized = false;
	size_t popSize;
	size_t generations;
	float px, pm;//crossover, mutation
	int tSize;
	friend class Algorithm;
};

#include "Population.h"

class Algorithm
{
public:

private:
	Config config;
	Population pop;

};