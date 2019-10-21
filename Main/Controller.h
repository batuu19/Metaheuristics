#pragma once

#include <random>
#include <iostream>
//#include <random>
#include "Loader.h"

class Controller
{
public:
	Controller();

	void run();
private:
	std::random_device rd;
	std::mt19937 rng;
};
