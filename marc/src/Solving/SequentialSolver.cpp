#include <memory>

#include "../../header/Solving/SequentialSolver.h"
#include "../../header/Solving/SolverProblem.h"
#include "../../header/Solving/SolverMonitor.h"
#include "../../header/Solving/Algorithms/Algorithm.h"

#include "../../header/Modeling/Solution.h"
#include "../../header/Modeling/Problem.h"

#include "../../header/Utils/Exceptions/NoSolutionFoundException.h"
#include "../../header/Utils/Exceptions/NoApplicableActionException.h"

namespace Modeling { class Problem; }

namespace Solving {

    std::shared_ptr<Modeling::Solution> SequentialSolver::solve() const {
        bool mon = this->isMonitored();
        std::shared_ptr<SolverMonitor> monitor;
        if (mon) {
            monitor = this->getMonitor().lock();
            monitor->begin();
        }
        std::shared_ptr<Modeling::Solution> sol;
        std::shared_ptr<SolverAlgorithm> sa;

        const unsigned int n = this->countSolvingSteps();
        unsigned int m;
        bool reInit;
        for (unsigned int i = 0; i < n; i++) {
            if (mon) monitor->logRunBegin(i, n);
            sa = this->getSolvingStep(i).lock();
            sa->getAlgorithm().lock()->reInit();
            m = sa->getExecutions();
            reInit = sa->alwaysReInit();
            for (unsigned int j = 0; j < m; j++) {
                if (mon) monitor->logRestartBegin(j, m, reInit);
                try { 
                    sol = sa->getAlgorithm().lock()->trustedGetNextSolution(); 
                } catch(NoSolutionFoundException& e) { 
                    if (mon) monitor->logRestartCompletion("No solution found, restarting");
                    continue; 
                } catch(NoApplicableActionException& e) { 
                    if (mon) monitor->failure("Encountered a sink state. Check your transition model");
                    throw NoApplicableActionException(); 
                }
                if (this->getSolverProblem().lock()->trustedObjectiveTest(sol->getStateSolution().lock())) {
                    if (mon) monitor->logRestartCompletion("Algorithm returned a globally optimal solution!");
                    return std::move(sol);
                } else {
                    if (mon) monitor->logRestartCompletion("Algorithm result is not optimal, retrying...");
                }
                if (reInit && j != m-1) sa->getAlgorithm().lock()->reInit();
            }
            if (mon) monitor->logRunCompletion();
        }
        if (!sol) {
            if (mon) monitor->failure("No solution was found");
            throw NoSolutionFoundException();
        } 
        if (mon) monitor->end();
        else return sol;
    }

}