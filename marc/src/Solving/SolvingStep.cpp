#include "../../header/Solving/SolvingStep.h"

namespace Solving {

    const std::weak_ptr<Solver::SolverAlgorithm> SolvingStep::getSolverAlgorithm() const {
        return this->getRoleY();
    }

    const std::weak_ptr<Algorithms::Algorithm> SolvingStep::getAlgorithm() const {
        return this->getRoleX();
    }

    SolvingStep::SolvingStep( std::shared_ptr<Algorithms::Algorithm> alg, std::shared_ptr<Solver::SolverAlgorithm> sa)
            : SingleOwnerAssociationLink( std::move(alg), std::move(sa)) { }

}