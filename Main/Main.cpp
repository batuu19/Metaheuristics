
#include "Main.h"
#include "Problem.h"
#include "Loader.h"

int main()
{
	std::mt19937 rng;

    std::cout << "Hello World!\n";
	std::string command = "ls " + std::string(TSP_DIRECTORY);
	std::string filename = "berlin11_modified.tsp";
	//Problem a = Loader::loadData(filename);

	std::vector<int> t = { 1,2,3,4,5,6,7,8 };

	int x = t.back();
	t.pop_back();

	for (size_t i = 0; i < t.size(); i++)
	{
		std::cout << t[i];
	}



	system("pause");
}
