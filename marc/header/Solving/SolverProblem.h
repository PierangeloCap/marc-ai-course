#ifndef SOLVERPROBLEM_H
#define SOLVERPROBLEM_H

#include <SingleOwnerAssociationLink.h>

namespace Modeling { class Problem; }

namespace Solving {

    class Solver;

    class SolverProblem : protected SingleOwnerAssociationLink<Solver, Modeling::Problem> {

    public:
        [[nodiscard]] const std::weak_ptr<Solver> getSolver() const;

        [[nodiscard]] const std::weak_ptr<Modeling::Problem> getProblem() const;

        SolverProblem(std::shared_ptr<Solver> solver, std::shared_ptr<Modeling::Problem> prob);

    };

}

#endif //SOLVERPROBLEM_H
