#pragma once

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include"Problem.h"

static constexpr char TSP_DIRECTORY[] = "../TSP_files/";

static class Loader 
{
public:
	static Problem loadData(const std::string& filename);

};