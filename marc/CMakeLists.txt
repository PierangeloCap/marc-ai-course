cmake_minimum_required(VERSION 3.14)
project(MARC_)

set(CMAKE_CXX_STANDARD 17)

set(MCPP_INCLUDE ./include/MCPP)
set(MARC_INCLUDE ./header)

set(HEADERS
        header/Modeling/Action.h
        header/Solving/Algorithms/Algorithm.h
        header/Modeling/HeuristicDrivenSearchProblem.h
        header/Modeling/InitialStateProblem.h
        header/Solving/Algorithms/LocalSearchAlgorithm.h
        header/Modeling/OptimizationProblem.h
        header/Modeling/Problem.h
        header/Modeling/RandomExplorationProblem.h
        header/Solving/SequentialSolver.h
        header/Solving/SolverMonitor.h
        header/Solving/MonitorAssoc.h
        header/Solving/Algorithms/SimulatedAnnealing.h
        header/Modeling/Solution.h
        header/Solving/Solver.h
        header/Modeling/State.h
        header/Modeling/ActionProblem.h
        header/Modeling/InitialStateLink.h
        header/Modeling/StateSolution.h
        header/Modeling/StateProblem.h
        header/Solving/SolvingOrder.h
        header/Solving/SolverProblem.h
        header/Solving/SolvingStep.h
        header/Solving/Algorithms/BestSolution.h
        header/Solving/Algorithms/OptimalSolution.h
        header/Solving/Algorithms/SimAnnTemperature.h
        header/Solving/Algorithms/FirstChoiceHillClimbing.h
        header/Solving/Algorithms/SteepestDescent.h
        header/Utils/Exceptions/NoRandomInterfaceFoundException.h
        header/Utils/Exceptions/NonZeroTemperatureException.h
        header/Utils/Exceptions/NoSearchStartingPointFound.h
        header/Utils/Exceptions/ViolatedPreconditionsException.h
        header/Utils/Exceptions/NullPointerException.h
        header/Utils/Exceptions/NoInitialStateFoundException.h
        header/Utils/Exceptions/NoHeuristicFunctionFoundException.h
        header/Utils/Exceptions/NoObjectiveFunctionFoundException.h
        header/Utils/Exceptions/NoSolutionFoundException.h
        header/Utils/Exceptions/ArrayIndexOutOfBoundsException.h
        header/Utils/Exceptions/IncompatibleStateTypeException.h
        header/Utils/Exceptions/NoApplicableActionException.h
        header/Utils/Exceptions/ImmutablePropertyException.h
        header/Utils/Exceptions/ViolatedPostconditionsException.h
        header/Utils/RunTimeTypeChecking/VirtualEnableSharedFromThis.h
   )

set(SOURCES
        src/Modeling/Action.cpp
        src/Solving/Algorithms/Algorithm.cpp
        src/Modeling/HeuristicDrivenSearchProblem.cpp
        src/Modeling/InitialStateProblem.cpp
        src/Solving/Algorithms/LocalSearchAlgorithm.cpp
        src/Modeling/OptimizationProblem.cpp
        src/Modeling/Problem.cpp
        src/Modeling/RandomExplorationProblem.cpp
        src/Solving/SequentialSolver.cpp
        src/Solving/SolverMonitor.cpp
        src/Solving/MonitorAssoc.cpp
        src/Solving/Algorithms/SimulatedAnnealing.cpp
        src/Modeling/Solution.cpp
        src/Solving/Solver.cpp
        src/Modeling/State.cpp
        src/Modeling/ActionProblem.cpp
        src/Modeling/InitialStateLink.cpp
        src/Modeling/StateSolution.cpp
        src/Modeling/StateProblem.cpp
        src/Solving/SolvingOrder.cpp
        src/Solving/SolverProblem.cpp
        src/Solving/SolvingStep.cpp
        src/Solving/Algorithms/BestSolution.cpp
        src/Solving/Algorithms/OptimalSolution.cpp
        src/Solving/Algorithms/SimAnnTemperature.cpp
        src/Solving/Algorithms/FirstChoiceHillClimbing.cpp
        src/Solving/Algorithms/SteepestDescent.cpp
   )

add_library(MARC SHARED ${SOURCES} ${HEADERS})

target_include_directories(MARC PUBLIC ${MARC_INCLUDE})
target_include_directories(MARC PUBLIC ${MCPP_INCLUDE})

