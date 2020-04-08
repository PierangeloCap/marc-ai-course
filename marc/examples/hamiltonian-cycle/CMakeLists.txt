cmake_minimum_required(VERSION 3.14)
project(MARCSolveHamiltonianCycle)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(MARCSolveHamiltonianCycle main.cpp
        RestartUntilGlobalOptimumSolver.cpp RestartUntilGlobalOptimumSolver.h
        temperature/InvLogTemperature.cpp temperature/InvLogTemperature.h temperature/GeometricTemperature.cpp temperature/GeometricTemperature.h temperature/ExponentialTemperature.cpp temperature/ExponentialTemperature.h HamiltonianCycle.cpp HamiltonianCycle.h SwapVisits.cpp SwapVisits.h HamiltonianCycleState.cpp HamiltonianCycleState.h utils/ParseELGraph.cpp GraphDimensionType.h utils/Using.h utils/ParseELGraph.h)

include(FindPkgConfig)
find_package(MARC REQUIRED)
target_include_directories(MARCSolveHamiltonianCycle PRIVATE ${MARC_INCLUDE})
target_link_libraries(MARCSolveHamiltonianCycle ${MARC_LIBRARY})

include(IncludeMCPP)
target_include_directories(MARCSolveHamiltonianCycle PRIVATE ${MCPP_INCLUDE})
