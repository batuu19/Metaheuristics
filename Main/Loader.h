#pragma once

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include"Algorithm.h"

static constexpr char TSP_DIRECTORY[] = "../TSP_files/";

static class Loader 
{
public:
	static Algorithm load(const std::string& filename);
};