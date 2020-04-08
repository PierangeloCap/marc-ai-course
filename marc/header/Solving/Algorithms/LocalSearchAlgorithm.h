#ifndef LOCALSEARCHALGORITHM_H
#define LOCALSEARCHALGORITHM_H

#include <memory>
#include "Algorithm.h"
#include "../../Modeling/OptimizationProblem.h"
#include <StrongAssociationRole.h>


namespace Modeling {
    
    class Solution;

    class HeuristicDrivenSearchProblem;
    
    class RandomExplorationProblem;

    class State;
    
    class Action;
    
}

namespace Solving {
    
    class Solver;

    class SolvingStep;

    namespace Algorithms {

        class OptimalSolution;

        class LocalSearchAlgorithm : public Algorithm, protected StrongAssociationRole<OptimalSolution, 0, 1>,
                                     public std::enable_shared_from_this<LocalSearchAlgorithm> {

        private:
            mutable Modeling::HeuristicDrivenSearchProblem* cachedHeuristic = nullptr;

            mutable Modeling::OptimizationProblem* cachedOptimization = nullptr;

            mutable std::shared_ptr<Modeling::State> nextCache;

            mutable double nextHeurCache = -1;

            mutable double bestValueCache = -1;

        protected:
            const unsigned int maxIdleIterations;

            unsigned int bestIteration = 1;

            /* Caching methods */
            void cacheSuccessor(std::shared_ptr<Modeling::State> succ) const;

            void cacheSuccessorValue(const double val) const;

            void cacheBestValue(const double val) const;

            std::shared_ptr<Modeling::Solution> 
            getSuccessor(const std::shared_ptr<Modeling::Action>& act, const std::shared_ptr<Modeling::Solution>& curr) const;

            double getSuccessorValue(const std::shared_ptr<Modeling::Solution>& succ) const;

            double getBestValue() const;

            /* Characterizing methods */
            virtual std::shared_ptr<Modeling::Action> chooseAction(const std::shared_ptr<Modeling::Solution>& curr) = 0;

            virtual bool visitCandidate(const std::shared_ptr<Modeling::Solution>& cand, const std::shared_ptr<Modeling::Solution>& curr) = 0;

            virtual bool continueSearch() const;

            /* Association handling */
            void setBestIteration(unsigned int best);

            void storeOptimalSolution(std::shared_ptr<OptimalSolution> sol);

            void removeOptimalSolution();

            /* Problem interface methods */
            virtual std::shared_ptr<Modeling::Solution> getSearchStartingPoint() const;

            std::shared_ptr<Modeling::State> getInitialState(std::shared_ptr<Modeling::Problem>& prob) const;

            std::shared_ptr<Modeling::State> getRandomState(std::shared_ptr<Modeling::Problem>& prob) const;

            double heuristicFunction(std::shared_ptr<Modeling::Solution> sol) const;

            double objectiveFunction(std::shared_ptr<Modeling::Solution> sol) const;

            Modeling::direction getOptimizationDirection() const;

        public:
            /* API */
            virtual void reInit();

            virtual std::shared_ptr<Modeling::Solution> getNextSolution();

            unsigned int getMaxIdleIterations() const;

            unsigned int getBestIteration() const;

            const std::weak_ptr<Modeling::Solution> getOptimalSolution() const;

            LocalSearchAlgorithm(const unsigned int maxIdleIterations);

        };

    }

}


#endif /* LOCALSEARCHALGORITHM_H */

