#include "../../header/Solving/SolvingOrder.h"

namespace Solving {

    const std::weak_ptr<Solver> SolvingOrder::getSolver() const {
        return this->getRoleX();
    }

    SolvingOrder::SolvingOrder(std::shared_ptr<Solver> solver, std::shared_ptr<Solver::SolverAlgorithm> step)
        : SingleOwnerAssociationLink(std::move(solver), std::move(step)){ }

    const std::weak_ptr<Solver::SolverAlgorithm> SolvingOrder::getSolvingStep() const {
        return this->getRoleY();
    }

}