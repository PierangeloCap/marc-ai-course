#include <iostream>
#include <memory>
#include <Solving/SequentialSolver.h>
#include "Solving/Algorithms/FirstChoiceHillClimbing.h"
#include "Utils/Exceptions/NoSolutionFoundException.h"
#include "Modeling/Solution.h"
#include "temperature/InvLogTemperature.h"
#include "temperature/GeometricTemperature.h"
#include "temperature/ExponentialTemperature.h"
#include "GraphDimensionType.h"
#include "HamiltonianCycle.h"
#include "SwapVisits.h"
#include "HamiltonianCycleState.h"
#include "utils/ParseELGraph.h"

int main(int argc, char** argv) { 

    /*
     * Very simple example of MARC modeling and solving: the Hamiltonian Cycle problem
     * Open README for documentation
     */

    auto G = parseELGraph(argv[1]);
    std::string tempName = argv[2];
    double alpha = std::stod(argv[3]);
    int T0 = std::stoi(argv[4]);
    const unsigned int timeout = std::stoi(argv[5]);
    const unsigned int maxIdle = std::stoi(argv[6]);

    std::cout << "MARC Solve: Hamiltonian Cycle\n";

    // Note 1. Use smart pointers for consistent memory management (memory.h header in stdlib)
    auto dim = std::make_unique<GraphDimensionType>(*G); 
    auto HC = std::make_shared<HamiltonianCycle>(*dim); //create the Problem instance with dimensionality G
    const unsigned int nodes = HC->countNodes();

    // Note 2. The basic MARC definition of Actions refers to *ground* Actions.
    //         Here, an example of Action grounding
    std::shared_ptr<Modeling::Action> act;
    std::string begin = "swap visit ";
    for (unsigned int i = 0; i < nodes; i++) {
        for (unsigned int j = i+1; j < nodes; j++) {
            act = std::make_shared<SwapVisits>(i,j,(begin+std::to_string(i)+" with visit "+std::to_string(j)));
            act->setProblem(HC); // Note 3. Handling ActionProblem association
        }
    }

    std::cout << "Solving with Simulated Annealing and random restarts\n";
    {
        auto solver = std::make_shared<Solving::SequentialSolver>();
        solver->setSolverProblem(HC); // Note 4. Handling SolverProblem association

        // Note 5. Picking an algorithm (i.e., Simulated Annealing) off-the-shelf
        auto simAnn = std::make_shared<Solving::Algorithms::SimulatedAnnealing>(maxIdle);

    	if(tempName == "inv-log"){
            auto tempLog = std::make_shared<InvLogTemperature>(T0, alpha); 
    	    simAnn->setTemperature(std::move(tempLog));
    	}
    	else if(tempName == "exp"){
                auto tempExp = std::make_shared<ExponentialTemperature>(T0, alpha, nodes);
    	    simAnn->setTemperature(std::move(tempExp));
    	}
    	else if(tempName == "geom"){
    	    auto tempGeom = std::make_shared<GeometricTemperature>(T0, alpha);
    	    simAnn->setTemperature(std::move(tempGeom));
	    }
        else {
            std::cerr << "ERR: Temperature function " << tempName << " undefined" << std::endl;
            exit(1);
        } 

        // Note 6. Handling Algorithm scheduling (note that SolverAlgorithm is *invisible*)
        solver->scheduleAlgorithm(simAnn, timeout, false);

        std::shared_ptr<Modeling::Solution> sol;
        clock_t time = clock();
        try {
            sol = solver->trustedSolve();
        }
        catch (NoSolutionFoundException &e) {
            std::cerr << e.what();
            exit(1);
        }
        time = clock()-time;

        auto solutionState = sol->getStateSolution();
        std::cout << "Solution state:\n";
        // Note 7. Extract solution State with downcasting (from State to HamiltonianCycleState)
        auto wbSolutionState = std::dynamic_pointer_cast<HamiltonianCycleState>(solutionState.lock());
        wbSolutionState->print();

        std::cout << "  With value: " << HC->heuristic(wbSolutionState) << "\n";
        std::cout << "  Found in: " << simAnn->getIterationCounter() << " iterations\n";
        std::cout << "  Computation time: " << (float)time/CLOCKS_PER_SEC << " seconds\n";

    }

    return 0;
}
