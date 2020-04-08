#include "../../header/Solving/ORBSolver.h"
#include "../../header/Solving/Algorithms/Algorithm.h"
#include "../../header/Solving/SolverMonitor.h"

#include "../../header/Modeling/InitialStateProblem.h"
#include "../../header/Modeling/Solution.h"

#include "../../header/Utils/Exceptions/NoHeuristicFunctionFoundException.h"
#include "../../header/Utils/Exceptions/NoRandomInterfaceFoundException.h"
#include "../../header/Utils/Exceptions/NoInitialStateFoundException.h"
#include "../../header/Utils/Exceptions/NoSolutionFoundException.h"
#include "../../header/Utils/Exceptions/NoApplicableActionException.h"


namespace Solving {

    std::shared_ptr<Modeling::State> ORBSolver::getRandomState() const {
        if (this->randCache == nullptr) {
            this->randCache = dynamic_cast<Modeling::RandomExplorationProblem *>(this->getSolverProblem().lock().get());
            if (this->randCache == nullptr) 
                throw NoRandomInterfaceFoundException("ORBSolver::getRandomState");
        }
        return this->randCache->trustedGetRandomState();
    }

    double ORBSolver::heuristic(const std::shared_ptr<Modeling::State>& state) const {
        if (this->heuristicCache == nullptr) {
            this->heuristicCache = dynamic_cast<Modeling::HeuristicDrivenSearchProblem *>(this->getSolverProblem().lock().get());
            if (this->heuristicCache == nullptr) 
                throw NoHeuristicFunctionFoundException("ORBSolver::heuristicFunction");
        }
        return this->heuristicCache->trustedHeuristic(state);
    }

    void ORBSolver::bootstrap() {

        for (unsigned int i = 0; i < this->samples; i++) {
            auto state = this->getRandomState();
            this->addBootstrapState(state);
        }
    }

    std::vector<std::shared_ptr<Modeling::State>> ORBSolver::getBootstrap() const {
        return this->sources;
    }

    void ORBSolver::addBootstrapState(const std::shared_ptr<Modeling::State>& state) {
        if (this->sources.size() == 0) this->sources.push_back(state);
        else {
            auto pos = this->sources.begin() + this->findSourcePosition(state, 0, this->sources.size()-1);
            this->sources.insert(pos, state);
        }
    }

    unsigned int ORBSolver::findSourcePosition(const std::shared_ptr<Modeling::State>& state,
                                               unsigned int min, unsigned int max) const { 
        double searchVal = this->heuristic(state);
        double bound = this->heuristic(this->sources[(min+max)/2]); 
        while (max != min) {
            unsigned int m = (min+max)/2;
            double pred = this->heuristic(this->sources[m]); 
            double next = this->heuristic(this->sources[m+1]);
            if (searchVal <= next && searchVal >= pred) return m+1;
            else if (searchVal < pred) {
                max = m;
                bound = pred;
            } else if (searchVal > next) {
                min = m+1;
                bound = next;
            }
        }
        if (bound >= searchVal) return max;
        else return max+1;
    }

    std::shared_ptr<Modeling::Solution> ORBSolver::solve() const {
        bool mon = this->isMonitored();
        std::shared_ptr<SolverMonitor> monitor;
        if (mon) {
            monitor = this->getMonitor().lock();
            monitor->begin();
        }

        auto problem = this->getSolverProblem().lock();
        auto initStateProblem = std::dynamic_pointer_cast<Modeling::InitialStateProblem>(problem);
        if (!initStateProblem) throw NoInitialStateFoundException("ORBSolver::solve");

        std::shared_ptr<Modeling::Solution> sol;
        std::shared_ptr<Modeling::Solution> best;
        std::shared_ptr<SolverAlgorithm> sa;
        double bestVal = std::numeric_limits<double>::infinity();

        unsigned int N = this->countSolvingSteps();
        for (unsigned int i = 0; i < N; i++) {
            if (mon) monitor->logRunBegin(i, N);
            sa = this->getSolvingStep(i).lock();
            auto alg = sa->getAlgorithm().lock();
            double currVal;
            unsigned int M = this->sources.size();
            for (unsigned int j = 0; j < M; j++) {
                if (mon) monitor->logRestartBegin(j, M, true);
                alg->reInit();
                initStateProblem->setInitialState(this->sources[j]);
                try {
                    sol = alg->trustedGetNextSolution();
                    currVal = this->heuristic(sol->getStateSolution().lock());
                    if (mon) monitor->logRestartCompletion("heuristic function value: " + std::to_string(currVal));
                    if (currVal == 0) return std::move(sol);
                    else if (currVal < bestVal) {
                        best = sol;
                        bestVal = currVal;
                    } 
                } catch(NoSolutionFoundException& e) {
                    if (mon) monitor->logRestartCompletion("No solution found, restarting");
                    continue;
                } catch(NoApplicableActionException& e) {
                    if (mon) monitor->failure("Encountered a sink state. Check your transition model");
                    throw NoApplicableActionException();
                }
            }
            if (mon) monitor->logRunCompletion();
        }        
        if (!best) {
            if (mon) monitor->failure("No solution was found");
            throw NoSolutionFoundException();
        }
        if (mon) monitor->end();
        return std::move(best);
    }

    ORBSolver::ORBSolver(unsigned int samples) :
        samples(samples), sources(), Solver() {}

}