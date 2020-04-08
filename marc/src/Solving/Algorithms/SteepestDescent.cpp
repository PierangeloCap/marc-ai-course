#include <limits>

#include "../../../header/Solving/Algorithms/SteepestDescent.h"

#include "../../../header/Modeling/Action.h"
#include "../../../header/Modeling/Solution.h"

#include "../../../header/Utils/Exceptions/NoApplicableActionException.h"


namespace Solving {

    namespace Algorithms {

        std::shared_ptr<Modeling::Action> 
        SteepestDescent::chooseAction(const std::shared_ptr<Modeling::Solution>& sol) {
            double bestVal = std::numeric_limits<double>::infinity(), currVal;
            std::unordered_set<std::shared_ptr<Modeling::Action>> remaining = 
                this->getAlgorithmProblem().lock()->getPossibleActions(sol->getStateSolution().lock());
            std::shared_ptr<Modeling::Action> result;
            std::shared_ptr<Modeling::Solution> cand;
            for (auto itr = remaining.begin(); itr != remaining.end(); itr++) {
                cand = std::make_shared<Modeling::Solution>();
                cand->setStateSolution((*itr)->trustedEvaluateEffects(sol->getStateSolution().lock()));
                currVal = this->heuristicFunction(cand);
                if (currVal <= bestVal) {
                    this->cacheSuccessor(cand->getStateSolution().lock());
                    bestVal = currVal;
                    result = *itr;
                } 
            }
            this->cacheSuccessorValue(bestVal);
            if (!result) throw NoApplicableActionException();   
            return result;         
        }

        bool SteepestDescent::visitCandidate(const std::shared_ptr<Modeling::Solution>& candidate, 
                                             const std::shared_ptr<Modeling::Solution>& current) {
            return true;
        }

        bool SteepestDescent::continueSearch() const {
            return LocalSearchAlgorithm::continueSearch();
        }

        SteepestDescent::SteepestDescent() : LocalSearchAlgorithm(1) {}

    }

}