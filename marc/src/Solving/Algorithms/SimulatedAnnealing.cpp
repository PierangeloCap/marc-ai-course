#include <random>
#include <cmath>

#include "../../../header/Solving/Algorithms/SimulatedAnnealing.h"
#include "../../../header/Solving/Algorithms/SimAnnTemperature.h"
#include "../../../header/Solving/Algorithms/Temperature.h"

#include "../../../header/Modeling/RandomExplorationProblem.h"
#include "../../../header/Modeling/Solution.h"

#include "../../../header/Utils/Exceptions/NoRandomInterfaceFoundException.h"
#include "../../../header/Utils/Exceptions/ImmutablePropertyException.h"
#include "../../../header/Utils/Exceptions/NoApplicableActionException.h"


namespace Solving {

    namespace Algorithms {

        double SimulatedAnnealing::temperature(const unsigned int step) const {
            auto itr = this->StrongAssociationRole<SimAnnTemperature, 1, 1>::cbeginLinks();
            if (itr == this->StrongAssociationRole<SimAnnTemperature, 1, 1>::cendLinks()) 
                throw MultiplicityConstraintException("SimulatedAnnealing", "simAnnTemperature", 
                    this->StrongAssociationRole<SimAnnTemperature, 1, 1>::countLinks());
            std::shared_ptr<Temperature> temp = (*itr)->getTemperatureFunctor().lock();
            return (*temp)[step];
        }

        void SimulatedAnnealing::setTemperature(std::shared_ptr<Temperature> temp) {
            try {
                auto thisPtr = std::dynamic_pointer_cast<SimulatedAnnealing>(this->shared_from_this());
                auto link = std::make_shared<SimAnnTemperature>(thisPtr, temp);
                this->StrongAssociationRole<SimAnnTemperature, 1, 1>::addLink(std::move(link));
            }
            catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("SimulatedAnnealing", "temperature"); }
        }

        std::shared_ptr<Modeling::Action> SimulatedAnnealing::chooseAction(const std::shared_ptr<Modeling::Solution> &sol) {
            try { return this->getRandomApplicableAction(sol); }
            catch (NoApplicableActionException& e) { throw NoApplicableActionException(); }
        }

        std::shared_ptr<Modeling::Action> SimulatedAnnealing::getRandomApplicableAction(const std::shared_ptr<Modeling::Solution> &sol) {
            if (this->cachedRandom == nullptr) {
                auto *randomProblem = dynamic_cast<Modeling::RandomExplorationProblem *>(this->getAlgorithmProblem().lock().get());
                if (randomProblem == nullptr) throw NoRandomInterfaceFoundException("SimulatedAnnealing::getRandomApplicableAction");
                this->cachedRandom = randomProblem;
            }
            auto result =  this->cachedRandom->getRandomApplicableAction(sol->getStateSolution().lock());
            if (!result) throw NoApplicableActionException();
            return result;
        }

        bool SimulatedAnnealing::visitCandidate(const std::shared_ptr<Modeling::Solution>& candidate,
                                                const std::shared_ptr<Modeling::Solution>& current) {
            double diff = this->heuristicFunction(candidate) - this->heuristicFunction(current);
            double temp = this->temperature(this->getIterationCounter());
            if (temp == 0) return diff < 0;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::bernoulli_distribution flipCoin(std::exp(-std::abs(diff)/temp));
            return diff < 0 || flipCoin(gen);
        }

        bool SimulatedAnnealing::continueSearch() const {
            return LocalSearchAlgorithm::continueSearch() && this->temperature(this->getIterationCounter()+1) > 0;
        }

        SimulatedAnnealing::SimulatedAnnealing(unsigned int maxIdleIterations) : LocalSearchAlgorithm(maxIdleIterations) { }

    }

}