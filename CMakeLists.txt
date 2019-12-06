cmake_minimum_required(VERSION 3.15)
project(Metaheuristics)

set(CMAKE_CXX_STANDARD 17)

file(GLOB meta_SRC
        "Main/*.h"
        "Main/*.cpp")

add_executable(Metaheuristics ${meta_SRC})