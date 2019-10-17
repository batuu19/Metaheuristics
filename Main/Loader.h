#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Problem.h"
#include "Algorithm.h"

static constexpr char TSP_DIRECTORY[] = "../TSP_files/";

static class Loader
{
public:
	static Problem loadData(const std::string& filename);
	static std::vector<Config> loadConfigs(const std::string& filename);

};