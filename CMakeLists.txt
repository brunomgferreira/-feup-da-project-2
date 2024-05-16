cmake_minimum_required(VERSION 3.28)
project(FEUP_DA_Project_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(FEUP_DA_Project_2 main.cpp
        App.cpp
        Data.cpp
        Graph.cpp
        States/State.cpp
        States/MainMenuState.cpp
        States/Utils/TryAgainState.cpp
        States/Utils/GetEdgesFilePathState.cpp
        States/Utils/GetNodesFilePathState.cpp
        States/Utils/GetNodesFileMenuState.cpp
        MutablePriorityQueue.h
        States/Utils/GetStartingVertexState.cpp)
