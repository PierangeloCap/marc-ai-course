#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include "LocalSearchAlgorithm.h"

#include <StrongAssociationRole.h>

namespace Modeling {

    class Action;

    class RandomExplorationProblem;

    class Solution;

}

namespace Solving {
    
    class Solver;

    namespace Algorithms {

        class Temperature;

        class SimAnnTemperature;

        class SimulatedAnnealing : public LocalSearchAlgorithm, protected StrongAssociationRole<SimAnnTemperature, 1, 1> {

        private:
            Modeling::RandomExplorationProblem* cachedRandom = nullptr;

        protected:        
            std::shared_ptr<Modeling::Action> chooseAction(const std::shared_ptr<Modeling::Solution>& sol) override;

            bool visitCandidate(const std::shared_ptr<Modeling::Solution>& candidate, const std::shared_ptr<Modeling::Solution>& current) override;

            bool continueSearch() const override;

            std::shared_ptr<Modeling::Action> getRandomApplicableAction(const std::shared_ptr<Modeling::Solution>& sol);

        public:
            double temperature(const unsigned int step) const;

            virtual void setTemperature(std::shared_ptr<Temperature> temp);

            SimulatedAnnealing(unsigned int maxIdleIterations);

        };

    }

}


#endif /* SIMULATEDANNEALING_H */

