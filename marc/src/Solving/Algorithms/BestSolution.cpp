#include "../../../header/Solving/Algorithms/BestSolution.h"

namespace Modeling { class Solution; }

namespace Solving {

    namespace Algorithms {

        class Algorithm;

        const std::weak_ptr<Algorithm> BestSolution::getAlgorithm() const {
            return this->getRoleX();
        }

        const std::weak_ptr<Modeling::Solution> BestSolution::getSolution() const {
            return this->getRoleY();
        }

        void BestSolution::setSolution(std::shared_ptr<Modeling::Solution> sol) {
            this->setRoleY(std::move(sol));
        }

        BestSolution::BestSolution(std::shared_ptr<Algorithm> alg, std::shared_ptr<Modeling::Solution> prob)
            : SingleOwnerAssociationLink(std::move(alg), std::move(prob)) { }

    }

}