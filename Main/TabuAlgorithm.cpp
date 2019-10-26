#include "TabuAlgorithm.h"

TabuAlgorithm::TabuAlgorithm(const Problem &problem)
        :
        best(problem.getDistanceMatrix()),
        citiesCount(problem.getDimension())
{
}

void TabuAlgorithm::run(std::mt19937 &rng)
{
    best.init(rng);

    auto bestFitness = best.getFitness();

    std::uniform_int_distribution<size_t> pointDist(0, citiesCount);
    std::vector<Creature> neighbors;
    while (!endCondition())
    {

        neighbors = best.getPointNeighbors(pointDist(rng));
//	    sorted = std::set<Creature>(neighbors.begin(),neighbors.end());
        auto comp = [](const Creature &c1, const Creature &c2)
        {
            return c1.getFitness() < c2.getFitness();
        };
        std::sort(neighbors.begin(), neighbors.end(), comp);

//        auto index = std::binary_search(neighbors.begin(), neighbors.end(), best, comp);
        auto bestNeighbor = neighbors[0];
        if(bestNeighbor.getFitness() >= best.getFitness())
            break;
        best = bestNeighbor;
        std::cout<<"best: "<<best.getFitness()<<std::endl;
    }
    std::cout<<"BEST: "<<best.getFitness()<<std::endl;
}

bool TabuAlgorithm::endCondition()
{
    return false;
}
