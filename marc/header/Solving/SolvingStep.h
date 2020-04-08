#ifndef SOLVINGSTEP_H
#define SOLVINGSTEP_H

#include <memory>
#include <SingleOwnerAssociationLink.h>
#include "Solver.h"

namespace Solving {

    namespace Algorithms { class Algorithm; }

    class SolvingStep : protected SingleOwnerAssociationLink<Algorithms::Algorithm, Solver::SolverAlgorithm> {

    public:
        [[nodiscard]] const std::weak_ptr<Solver::SolverAlgorithm> getSolverAlgorithm() const;

        [[nodiscard]] const std::weak_ptr<Algorithms::Algorithm> getAlgorithm() const;

        SolvingStep(std::shared_ptr<Algorithms::Algorithm> alg, std::shared_ptr<Solver::SolverAlgorithm> sa);

    };

}

#endif //SOLVINGSTEP_H
