#include <unordered_set>

#include "../../../header/Solving/Algorithms/Algorithm.h"
#include "../../../header/Solving/Algorithms/BestSolution.h"
#include "../../../header/Solving/SolvingStep.h"

#include "../../../header/Modeling/Solution.h"

#include "../../../header/Utils/Exceptions/ViolatedPostconditionsException.h"

#include "../../../include/MCPP/MultiplicityConstraintException.h"

namespace Solving {

    namespace Algorithms {

        std::shared_ptr<Modeling::Solution> Algorithm::trustedGetNextSolution() {
            if (!this->isInstantiated()) 
                throw MultiplicityConstraintException("Algorithm", "solvingStep", this->StrongAssociationRole<SolvingStep, 1, STAR>::countLinks());
            std::shared_ptr<Modeling::Solution> result = this->getNextSolution();
            if (result->getSolutionProblem().lock().get() != this->getAlgorithmProblem().lock().get()) 
                throw ViolatedPostconditionsException("Algorithm", "getNextSolution");
            return result;
        }

        void Algorithm::reInit() {
            this->removeBestSolution();
            this->iterationCounter = 0;
        }

        void Algorithm::incrementIterationCounter() {
            this->iterationCounter++;
        }

        unsigned int Algorithm::getIterationCounter() const {
            return this->iterationCounter;
        }

        const std::weak_ptr<Modeling::Problem> Algorithm::getAlgorithmProblem() const {
            if (!this->isInstantiated()) 
                throw MultiplicityConstraintException("Algorithm", "solvingStep", this->StrongAssociationRole<SolvingStep, 1, STAR>::countLinks());
            return (*this->StrongAssociationRole<SolvingStep, 1, STAR>::cbeginLinks())->getSolverAlgorithm().lock()->getSolver().lock()->getSolverProblem();
        }

        const std::weak_ptr<Solving::Solver> Algorithm::getAlgorithmSolver() const {
            if (!this->isInstantiated()) 
                throw MultiplicityConstraintException("Algorithm", "solvingStep", this->StrongAssociationRole<SolvingStep, 1, STAR>::countLinks());
            return (*this->StrongAssociationRole<SolvingStep, 1, STAR>::cbeginLinks())->getSolverAlgorithm().lock()->getSolver();
        }

        void Algorithm::storeBestSolution(std::shared_ptr<BestSolution> sol) {
            if (this->StrongAssociationRole<BestSolution, 0, 1>::countLinks() == 0) this->StrongAssociationRole<BestSolution, 0, 1>::addLink(std::move(sol));
            else (*(this->StrongAssociationRole<BestSolution, 0, 1>::cbeginLinks()))->setSolution(sol->getSolution().lock());
        }

        void Algorithm::removeBestSolution() {
            if (this->StrongAssociationRole<BestSolution, 0, 1>::countLinks() > 0) {
                this->StrongAssociationRole<BestSolution, 0, 1>::removeLink(*(this->StrongAssociationRole<BestSolution, 0, 1>::cbeginLinks()));
            }
        }

        const std::weak_ptr<Modeling::Solution> Algorithm::getBestSolution() const {
            auto result = this->StrongAssociationRole<BestSolution, 0, 1>::cbeginLinks();
            if (result == this->StrongAssociationRole<BestSolution, 0, 1>::cendLinks()) return std::shared_ptr<Modeling::Solution>(nullptr);
            return (*result)->getSolution();
        }

        bool Algorithm::isInstantiated() const {
            return (this->StrongAssociationRole<SolvingStep, 1, STAR>::cbeginLinks() != this->StrongAssociationRole<SolvingStep, 1, STAR>::cendLinks());
        }

    }

}