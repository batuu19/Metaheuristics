#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Problem.h"
#include "Algorithm.h"
#include "Utils.h"

static constexpr char TSP_DIRECTORY[] = "../TSP_files/";
static constexpr char LINE_NODES_BEGIN[] = "NODE_COORD_SECTION";
static constexpr char LINE_EOF[] = "EOF";

static class Loader
{
public:
	static Problem loadData(const std::string& filename);
	static std::vector<Config> loadConfigs(const std::string& filename);

	static std::vector<Point> debugLoadNodes(const std::string& filename);
};