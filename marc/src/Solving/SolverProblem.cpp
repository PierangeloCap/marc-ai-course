#include "../../header/Solving/SolverProblem.h"

namespace Solving {

    const std::weak_ptr<Solver> SolverProblem::getSolver() const {
        return this->getRoleX();
    }

    const std::weak_ptr<Modeling::Problem> SolverProblem::getProblem() const {
        return this->getRoleY();
    }

    SolverProblem::SolverProblem(std::shared_ptr<Solver> solver, std::shared_ptr<Modeling::Problem> prob)
        : SingleOwnerAssociationLink(std::move(solver), std::move(prob)) { }

}
