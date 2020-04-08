#include <iostream>
#include <Modeling/Solution.h>
#include <Modeling/HeuristicDrivenSearchProblem.h>
#include <Modeling/InitialStateProblem.h>
#include <MultiplicityConstraintException.h>
#include <Solving/Algorithms/Algorithm.h>
#include <Utils/Exceptions/NoHeuristicFunctionFoundException.h>
#include <Utils/Exceptions/NoSolutionFoundException.h>
#include <Utils/Exceptions/NoApplicableActionException.h>

#include "RestartUntilGlobalOptimumSolver.h"

std::shared_ptr<Modeling::Solution> RestartUntilGlobalOptimumSolver::solve() const {

    auto* heuristicProblem = dynamic_cast<Modeling::HeuristicDrivenSearchProblem *>(this->getSolverProblem().lock().get());
    if (heuristicProblem == nullptr) throw NoHeuristicFunctionFoundException("RestartUntilGlobalOptimumSolver::solve");
    auto* initStateProblem = dynamic_cast<Modeling::InitialStateProblem *>(this->getSolverProblem().lock().get());
    if (initStateProblem != nullptr) std::cout << "Initial state value: " << heuristicProblem->heuristic(initStateProblem->getInitialState().lock()) << "\n";

    std::shared_ptr<Modeling::Solution> sol;
    std::shared_ptr<Modeling::Solution> curr;
    std::shared_ptr<Modeling::State> state;
    std::shared_ptr<SolverAlgorithm> sa;

    int exec = 1;
    double solValue = -1, currValue;
    const unsigned int n = this->countSolvingSteps();
    std::cout << "SOLUTION VALUE == ITERATIONS == RUN ID \n";
    do { // while restarts are over or we found a solution
        for (unsigned int i = 0; i < n; i++) { // for each different scheduled algorithm
            sa = this->getSolvingStep(i).lock();
            sa->getAlgorithm().lock()->reInit();
            try { curr = sa->getAlgorithm().lock()->trustedGetNextSolution(); } // run the algorithm
            catch(NoSolutionFoundException& e) {
                this->e->addToIterations(sa->getAlgorithm().lock()->getIterationCounter());
                exec++;
                continue;
            }
            catch(NoApplicableActionException& e) { throw NoApplicableActionException(); }

            this->e->addToIterations(sa->getAlgorithm().lock()->getIterationCounter());
            currValue = heuristicProblem->trustedHeuristic(curr->getStateSolution().lock()); // compute current solution value
            if (solValue == -1 || currValue < solValue) { // if improving: new best solution
                sol = curr;
                solValue = currValue;
            }
        }
        std::cout << heuristicProblem->trustedHeuristic(curr->getStateSolution().lock()) << " - " << sa->getAlgorithm().lock()->getIterationCounter() << " - " << exec++ << "\n";
    } while (exec <= this->restarts && solValue != 0);

    if (sol) return sol;
    throw NoSolutionFoundException();

}

unsigned int RestartUntilGlobalOptimumSolver::getTotIterations() const {
    return this->e->totIterations;
}

RestartUntilGlobalOptimumSolver::RestartUntilGlobalOptimumSolver(const unsigned int res) : restarts(res) { }
