cmake_minimum_required(VERSION 3.15)
project(Metaheuristics)

set(CMAKE_CXX_STANDARD 17)

add_executable(Metaheuristics Main/Main.cpp Main/Main.h Main/Algorithm.h Main/Algorithm.cpp Main/Creature.cpp Main/Creature.h Main/DistanceMatrix.cpp Main/DistanceMatrix.h Main/Population.cpp Main/Population.h Main/Problem.cpp Main/Problem.h Main/Utils.cpp Main/Utils.h Main/Math.h Main/Controller.h Main/Loader.h Main/Loader.cpp Main/Controller.cpp)