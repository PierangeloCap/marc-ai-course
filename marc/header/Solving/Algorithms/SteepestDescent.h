#ifndef STEEPESTDESCENT_H
#define STEEPESTDESCENT_H

#include "LocalSearchAlgorithm.h"


namespace Modeling {

    class Action;

    class Solution;

}

namespace Solving {

    namespace Algorithms {

        class SteepestDescent : public LocalSearchAlgorithm {

        protected:
            std::shared_ptr<Modeling::Action> chooseAction(const std::shared_ptr<Modeling::Solution>& sol) override;

            bool visitCandidate(const std::shared_ptr<Modeling::Solution>& candidate, const std::shared_ptr<Modeling::Solution>& current) override;

            bool continueSearch() const override;

        public:
            SteepestDescent();

        };

    }

}



#endif /* STEEPESTDESCENT_H */