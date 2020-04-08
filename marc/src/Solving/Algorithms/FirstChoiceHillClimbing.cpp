#include <algorithm>
#include <random>
#include "../../../header/Solving/Algorithms/FirstChoiceHillClimbing.h"
#include "../../../header/Solving/Algorithms/SimulatedAnnealing.h"

#include "../../../header/Modeling/Solution.h"

#include "../../../header/Utils/Exceptions/NonZeroTemperatureException.h"
#include "../../../header/Utils/Exceptions/NoApplicableActionException.h"

namespace Solving {

    namespace Algorithms {

        FirstChoiceHillClimbing::FirstChoiceHillClimbing(unsigned int maxIdleIterations) : SimulatedAnnealing(maxIdleIterations) {}

        bool FirstChoiceHillClimbing::continueSearch() const {
            return (this->iterationCounter - this->bestIteration) < this->maxIdleIterations;
        }

        std::shared_ptr<Modeling::Action> FirstChoiceHillClimbing::chooseAction(const std::shared_ptr<Modeling::Solution> &sol) {
            double currVal = this->heuristicFunction(sol), newVal;
            std::unordered_set<std::shared_ptr<Modeling::Action>> remaining = this->getAlgorithmProblem().lock()->getPossibleActions(sol->getStateSolution().lock());
            std::vector<std::shared_ptr<Modeling::Action>> rnd(remaining.begin(), remaining.end());
            std::shared_ptr<Modeling::Action> a;
            std::shared_ptr<Modeling::Solution> cand;
            std::shuffle(rnd.begin(), rnd.end(), std::mt19937(std::random_device()()));
            for (const auto& itr : rnd) {
                cand = std::make_shared<Modeling::Solution>();
                cand->setStateSolution(itr->trustedEvaluateEffects(sol->getStateSolution().lock()));
                newVal = this->heuristicFunction(cand);
                if (newVal <= currVal) {
                    this->cacheSuccessor(cand->getStateSolution().lock());
                    this->cacheSuccessorValue(newVal);
                    return itr;
                } 
            }
            throw NoApplicableActionException();
        }

        void FirstChoiceHillClimbing::setTemperature(std::shared_ptr<Temperature> temp) {
            auto ptr = std::dynamic_pointer_cast<ZeroTemperature>(temp);
            if(!ptr) throw NonZeroTemperatureException();
            SimulatedAnnealing::setTemperature(std::move(ptr));
        }

        bool FirstChoiceHillClimbing::visitCandidate(const std::shared_ptr<Modeling::Solution> &candidate,
                                                     const std::shared_ptr<Modeling::Solution> &current) {
            return true;
        }

    }

}
