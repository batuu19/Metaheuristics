
#include "Main.h"
#include "Algorithm.h"
#include "Loader.h"

int main()
{
    std::cout << "Hello World!\n";
	std::string command = "ls " + std::string(TSP_DIRECTORY);
	std::string filename = "berlin11_modified.tsp";
	Algorithm a = Loader::load(filename);
	system("pause");
}
