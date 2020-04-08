#ifndef BESTSOLUTION_H
#define BESTSOLUTION_H

#include <SingleOwnerAssociationLink.h>

namespace Modeling { class Solution; }

namespace Solving {

    namespace Algorithms {

        class Algorithm;

        class BestSolution : protected SingleOwnerAssociationLink<Algorithm, Modeling::Solution> {

        public:
            [[nodiscard]] const std::weak_ptr<Algorithm> getAlgorithm() const;

            [[nodiscard]] const std::weak_ptr<Modeling::Solution> getSolution() const;

            void setSolution(std::shared_ptr<Modeling::Solution> sol);

            BestSolution(std::shared_ptr<Algorithm> alg, std::shared_ptr<Modeling::Solution> prob);

        };

    }

}


#endif //BESTSOLUTION_H
