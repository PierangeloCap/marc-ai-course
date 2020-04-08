#include "../../../header/Solving/Algorithms/OptimalSolution.h"

namespace Modeling { class Solution; }

namespace Solving {

    namespace Algorithms {

        class Algorithm;

        const std::weak_ptr<Algorithm> OptimalSolution::getAlgorithm() const {
            return this->getRoleX();
        }

        const std::weak_ptr<Modeling::Solution> OptimalSolution::getSolution() const {
            return this->getRoleY();
        }

        void OptimalSolution::setSolution(std::shared_ptr<Modeling::Solution> sol) {
            this->setRoleY(std::move(sol));
        }

        OptimalSolution::OptimalSolution(std::shared_ptr<Algorithm> alg, std::shared_ptr<Modeling::Solution> prob)
                : SingleOwnerAssociationLink(std::move(alg), std::move(prob)) { }

    }

}