cmake_minimum_required(VERSION 3.15)
project(Metaheuristics)

set(CMAKE_CXX_STANDARD 17)

add_executable(Metaheuristics
        Main/Main.cpp
        Main/GAAlgorithm.h Main/GAAlgorithm.cpp
        Main/TabuAlgorithm.h Main/TabuAlgorithm.cpp
        Main/TabuList.cpp Main/TabuList.h
        Main/Creature.h Main/Creature.cpp
        Main/DistanceMatrix.cpp Main/DistanceMatrix.h
        Main/Population.cpp Main/Population.h
        Main/Problem.cpp Main/Problem.h
        Main/Utils.cpp Main/Utils.h
        Main/Math.h
        Main/Loader.h Main/Loader.cpp )