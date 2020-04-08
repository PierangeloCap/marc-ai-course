#include <iostream>
#include <memory>
#include <Solving/SequentialSolver.h>
#include <Solving/SolverMonitor.h>
#include <Solving/Algorithms/SteepestDescent.h>
#include <Solving/Algorithms/SimulatedAnnealing.h>
#include <Utils/Exceptions/NoSolutionFoundException.h>
#include <Utils/Exceptions/NoApplicableActionException.h>
#include <Modeling/Solution.h>
#include "../header/InvLogTemperature.h"
#include "../header/GeometricTemperature.h"
#include "../header/ExponentialTemperature.h"
#include "../header/NQueens.h"
#include "../header/MoveQueen.h"
#include "../header/QueensBoard.h"


int main(int argc, char** argv) { 

    const unsigned int N = 128;
    const double alpha = 0.65;
    const int T0 = 100;
    const int D = 0.01;
    const unsigned int timeout = 1;
    const unsigned int maxIdle = 60;

    std::cout << "MARC usage example: " << N << "-Queens" << std::endl;

    /*
     * Note 1. I strongly advice to use smart pointers for consistent 
     *         memory management (memory.h header in stdlib)
     */
    auto problem = std::make_shared<NQueens>(N); //create the Problem instance with dimension N
    auto startBoard = std::make_unique<std::vector<unsigned int>>();
    for (unsigned int i = 0; i < N; i++) startBoard->push_back(0);
    auto initial = std::make_shared<QueensBoard>(std::move(startBoard));
    initial->setStateProblem(problem);
    problem->setInitialState(std::move(initial));

    /* 
     * Note 2. The basic MARC definition of Actions refers to *ground* Actions.
     *         Here, an example of Action grounding
     */
    std::shared_ptr<Modeling::Action> act;
    std::string begin = "move queen ";
    for (unsigned int i = 0; i < N; i++) {
        for (unsigned int j = 1; j < N; j++) {
            act = std::make_shared<MoveQueen>(i,j,(begin+std::to_string(i)+" down "+std::to_string(j) + " squares"));
            act->setProblem(problem); // Note 3. Handling ActionProblem association
        }
    }

    std::cout << "Running Simulated Annealing with various temperature functions" << std::endl;
    {
        auto solver = std::make_shared<Solving::SequentialSolver>();
        auto monitor = std::make_shared<Solving::SolverMonitor>("Sequential");

        solver->setSolverProblem(problem); // Note 4. Handling SolverProblem association
        solver->setMonitor(std::move(monitor)); // Note 5. Monitor Solver activity

        // Note 6. Picking an algorithm (i.e., Simulated Annealing) off-the-shelf
        auto simAnnInvLog = std::make_shared<Solving::Algorithms::SimulatedAnnealing>(maxIdle);
        auto tempLog = std::make_shared<InvLogTemperature>(T0, alpha); 
        simAnnInvLog->setTemperature(std::move(tempLog));

        auto simAnnExp = std::make_shared<Solving::Algorithms::SimulatedAnnealing>(maxIdle);
        auto tempExp = std::make_shared<ExponentialTemperature>(T0, alpha, D);
        simAnnExp->setTemperature(std::move(tempExp));

        auto simAnnGeom = std::make_shared<Solving::Algorithms::SimulatedAnnealing>(maxIdle);
        auto tempGeom = std::make_shared<GeometricTemperature>(T0, alpha);
        simAnnGeom->setTemperature(std::move(tempGeom));

        auto steepest = std::make_shared<Solving::Algorithms::SteepestDescent>();

        // Note 7. Handling Algorithms scheduling (note that SolverAlgorithm is *invisible*)
        solver->scheduleAlgorithm(simAnnInvLog, timeout, true);
        solver->scheduleAlgorithm(simAnnExp, timeout, true);
        solver->scheduleAlgorithm(simAnnGeom, timeout, true);
        solver->scheduleAlgorithm(steepest, timeout, true);


        std::shared_ptr<Modeling::Solution> sol;
        clock_t time = clock();
        try {
            sol = solver->trustedSolve();
        }
        catch (NoSolutionFoundException &e) {
            std::cerr << e.what();
            exit(1);
        }
        catch (NoApplicableActionException &e) {
            std::cerr << e.what();
            exit(1);
        }
        time = clock()-time;
        
        auto solutionState = sol->getStateSolution();
        std::cout << "Solution state:" << std::endl;

        // Note 8. Extract solution State with downcasting (from State to QueensBoard)
        auto wbSolutionState = std::dynamic_pointer_cast<QueensBoard>(solutionState.lock());
        wbSolutionState->print();

        std::cout << "With value: " << problem->heuristic(wbSolutionState) << std::endl;
        
    }

    return 0;
}
