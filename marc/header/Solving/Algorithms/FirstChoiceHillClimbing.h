#ifndef FIRSTCHOICEHILCLIMBING_H
#define FIRSTCHOICEHILCLIMBING_H

#include "SimulatedAnnealing.h"
#include "Temperature.h"

namespace Solving {

    namespace Algorithms {

        class FirstChoiceHillClimbing : public SimulatedAnnealing {

        protected:
            virtual std::shared_ptr<Modeling::Action> chooseAction(const std::shared_ptr<Modeling::Solution>& sol);

            virtual bool visitCandidate(const std::shared_ptr<Modeling::Solution>& candidate, const std::shared_ptr<Modeling::Solution>& current);

            virtual bool continueSearch() const;

        public:
            class ZeroTemperature : public Temperature {

            protected:
                [[nodiscard]] double temperature(const unsigned int step) const override { return 0; }

            };

            virtual void setTemperature(std::shared_ptr<Temperature> temp);

            FirstChoiceHillClimbing(unsigned int maxIdleIterations);
        };
    }
}

#endif /* FIRSTCHOICEHILCLIMBING_H */

