#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <memory>
#include <limits>
#include <unordered_set>

#include "../Solver.h"

#include <StrongAssociationRole.h>


namespace Modeling {
    
    class InitialStateProblem;

    class HeuristicDrivenSearchProblem;

    class Problem;

    class Solution;
    
}

namespace Solving { 

    class Solver;

    class SolvingStep;
    
    namespace Algorithms {

        class BestSolution;

        class Algorithm : protected StrongAssociationRole<SolvingStep, 1, STAR>, protected StrongAssociationRole<BestSolution, 0, 1> {

            friend void Solver::SolverAlgorithm::setAlgorithm(const std::shared_ptr<Algorithms::Algorithm> &alg);

        protected:
            unsigned int iterationCounter = 0;

            virtual bool continueSearch() const = 0;

            bool isInstantiated() const;

            void storeBestSolution(std::shared_ptr<BestSolution> sol);

            void removeBestSolution();

            void incrementIterationCounter();

        public:
            virtual std::shared_ptr<Modeling::Solution> getNextSolution() = 0;

            std::shared_ptr<Modeling::Solution> trustedGetNextSolution();

            virtual void reInit();

            unsigned int getIterationCounter() const;

            const std::weak_ptr<Modeling::Problem> getAlgorithmProblem() const;

            const std::weak_ptr<Solving::Solver> getAlgorithmSolver() const;

            const std::weak_ptr<Modeling::Solution> getBestSolution() const;

        };

    }

}

#endif // ALGORITHM_H 

