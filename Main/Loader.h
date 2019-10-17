#pragma once

#include<fstream>
#include"Algorithm.h"

static class Loader 
{
	static bool load(const std::string& filename, Algorithm& out);
};