#ifndef SOLVER_H
#define SOLVER_H

#include <memory>

#include <StrongAssociationRole.h>
#include <OrderedAssociationRole.h>
#include <WeakAssociationRole.h>


namespace Modeling {

    class Solution;

    class Problem;

}

namespace Solving {
    
    namespace Algorithms { class Algorithm; }

    class SolverProblem;

    class SolvingOrder;

    class SolvingStep;

    class MonitorAssoc;

    class SolverMonitor;

    class Solver : protected StrongAssociationRole<SolverProblem, 1, 1>, 
                   protected OrderedAssociationRole<SolvingOrder, 0, STAR>,
                   protected StrongAssociationRole<MonitorAssoc, 0, 1>,
                   public std::enable_shared_from_this<Solver> {
        
    public:
        class SolverAlgorithm;

        virtual std::shared_ptr<Modeling::Solution> solve() const = 0;
        
        std::shared_ptr<Modeling::Solution> trustedSolve() const;
        
        virtual std::shared_ptr<Modeling::Solution> getOptimalSolution() const;

        virtual std::shared_ptr<Modeling::Solution> getBestSolution() const;

        const std::weak_ptr<SolverMonitor> getMonitor() const;

        void setMonitor(std::shared_ptr<SolverMonitor> mon);

        bool isMonitored() const;

        const std::weak_ptr<Modeling::Problem> getSolverProblem() const;

        void setSolverProblem(const std::shared_ptr<Modeling::Problem>& p);

        unsigned int countSolvingSteps() const;

        const std::weak_ptr<SolverAlgorithm> getSolvingStep(unsigned int index) const;

        void scheduleAlgorithm(const std::shared_ptr<Algorithms::Algorithm>& alg, const unsigned int executions, const bool alwaysReInit);

        class SolverAlgorithm final : protected WeakAssociationRole<SolvingOrder, 1, 1>, protected WeakAssociationRole<SolvingStep, 1, 1>,
                                      public std::enable_shared_from_this<SolverAlgorithm> {

        private:
            const unsigned int executions;

            const bool reInit;

        public:
            const std::weak_ptr<Solver> getSolver() const;

            void setSolver(const std::shared_ptr<Solver>& solver);

            const std::weak_ptr<Algorithms::Algorithm> getAlgorithm() const;

            void setAlgorithm(const std::shared_ptr<Algorithms::Algorithm>& alg);

            const unsigned int getExecutions() const;

            const bool alwaysReInit() const;

            SolverAlgorithm(const unsigned int executions, const bool alwaysReInit);

        };
        
    };
    
}

#endif /* SOLVER_H */

