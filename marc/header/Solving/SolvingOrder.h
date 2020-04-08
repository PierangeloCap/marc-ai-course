#ifndef SOLVINGORDER_H
#define SOLVINGORDER_H

#include <memory>
#include <SingleOwnerAssociationLink.h>
#include "Solver.h"

namespace Solving {

    class SolvingOrder : SingleOwnerAssociationLink<Solver, Solver::SolverAlgorithm> {

    public:
        [[nodiscard]] const std::weak_ptr<Solver> getSolver() const;

        [[nodiscard]] const std::weak_ptr<Solver::SolverAlgorithm> getSolvingStep() const;

        SolvingOrder(std::shared_ptr<Solver> solver, std::shared_ptr<Solver::SolverAlgorithm> step);

    };

}

#endif //SOLVINGORDER_H
