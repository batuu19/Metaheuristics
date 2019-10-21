
#include "Main.h"
#include "Problem.h"
#include "Loader.h"
#include "DistanceMatrix.h"

int main()
{
	std::mt19937 rng;

    std::cout << "Hello World!\n";
	std::string command = "ls " + std::string(TSP_DIRECTORY);
	std::string filename = "berlin11_modified.tsp";
	//Problem a = Loader::loadData(filename);

	std::vector<int> t = { 1,2,3,4,5,6,7,8 };

	auto nodes = Loader::debugLoadNodes("berlin11_modified.tsp");
	DistanceMatrix m = DistanceMatrix(nodes);


	system("pause");
}
