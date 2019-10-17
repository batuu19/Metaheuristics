
#include "Main.h"
#include "Problem.h"
#include "Loader.h"

int main()
{
	std::mt19937 rng;

    std::cout << "Hello World!\n";
	std::string command = "ls " + std::string(TSP_DIRECTORY);
	std::string filename = "berlin11_modified.tsp";
	Problem a = Loader::loadData(filename);
	system("pause");
}
