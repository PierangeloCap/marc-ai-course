#include <limits>

#include "../../header/Solving/Solver.h"
#include "../../header/Solving/SolverProblem.h"
#include "../../header/Solving/Algorithms/Algorithm.h"
#include "../../header/Solving/SolvingOrder.h"
#include "../../header/Solving/SolvingStep.h"
#include "../../header/Solving/MonitorAssoc.h"

#include "../../header/Modeling/Solution.h"
#include "../../header/Modeling/OptimizationProblem.h"
#include "../../header/Modeling/HeuristicDrivenSearchProblem.h"

#include "../../header/Utils/Exceptions/NoSolutionFoundException.h"
#include "../../header/Utils/Exceptions/NoObjectiveFunctionFoundException.h"
#include "../../header/Utils/Exceptions/NoHeuristicFunctionFoundException.h"
#include "../../header/Utils/Exceptions/ViolatedPostconditionsException.h"
#include "../../header/Utils/Exceptions/ViolatedPreconditionsException.h"
#include "../../header/Utils/Exceptions/ImmutablePropertyException.h"

#include "../../include/MCPP/MultiplicityConstraintException.h"

namespace Solving {

    std::shared_ptr<Modeling::Solution> Solver::trustedSolve() const {
        try {
            std::shared_ptr<Modeling::Solution> result = this->solve();
            if(result->getSolutionProblem().lock().get() != this->getSolverProblem().lock().get()) 
                throw ViolatedPostconditionsException("Solver", "solve");
            return result;
        }
        catch(NoSolutionFoundException& e){
            throw NoSolutionFoundException();
        }
    }

    const std::weak_ptr<Solver::SolverAlgorithm> Solver::getSolvingStep(unsigned int index) const {
        return this->getLink(index).lock()->getSolvingStep();
    }

    unsigned int Solver::countSolvingSteps() const {
        return this->OrderedAssociationRole<SolvingOrder, 0, STAR>::countLinks();
    }

    void Solver::scheduleAlgorithm(const std::shared_ptr<Algorithms::Algorithm>& alg,
                                   const unsigned int executions, const bool alwaysReInit) {
        try {
            auto other = alg->getAlgorithmSolver();
            if (other.lock().get() != this) throw ViolatedPreconditionsException("Solver", "scheduleAlgorithm");
        }
        catch (MultiplicityConstraintException &e) { 
            // alg still doesn't have a Solver: it's okay, I'm just about to schedule it
        }
        auto sa = std::make_shared<SolverAlgorithm>(executions, alwaysReInit);
        auto thisPtr = this->shared_from_this();
        sa->setSolver(thisPtr);
        sa->setAlgorithm(alg);
    }

    void Solver::setSolverProblem(const std::shared_ptr<Modeling::Problem>& p) {
        try {
            auto thisPtr = this->shared_from_this();
            auto link = std::make_shared<SolverProblem>(thisPtr, p);
            this->StrongAssociationRole<SolverProblem, 1, 1>::addLink(std::move(link));
        }
        catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("Solver", "solverProblem"); }
    }

    const std::weak_ptr<Modeling::Problem> Solver::getSolverProblem() const {
        auto result = this->StrongAssociationRole<SolverProblem, 1, 1>::cbeginLinks();
        if (result == this->StrongAssociationRole<SolverProblem, 1, 1>::cendLinks()) 
            throw MultiplicityConstraintException("Solver", "SolverProblem", 
                this->StrongAssociationRole<SolverProblem, 1, 1>::countLinks());
        return (*result)->getProblem();
    }

    std::shared_ptr<Modeling::Solution> Solver::getOptimalSolution() const {
        const auto* thisWithObjectiveFunction = dynamic_cast<const Modeling::OptimizationProblem *>(this->getSolverProblem().lock().get());
        if (thisWithObjectiveFunction == nullptr) throw NoObjectiveFunctionFoundException("Solver::getOptimalSolution");

        double best, currentValue;
        bool min = (thisWithObjectiveFunction->getDirection() == Modeling::direction::MIN);
        if (min) best = std::numeric_limits<double>::infinity();
        else best = std::numeric_limits<double>::lowest();

        std::shared_ptr<Modeling::Solution> bestSolution, currentSol;
        std::shared_ptr<Solver::SolverAlgorithm> step;

        for (unsigned int i = 0; i < this->countSolvingSteps(); i++) {
            step = this->getSolvingStep(i).lock();
            currentSol = step->getAlgorithm().lock()->getBestSolution().lock();
            if (currentSol == nullptr) continue;
            currentValue = thisWithObjectiveFunction->trustedObjectiveFunction(currentSol);
            if ((min && currentValue < best) || (!min && currentValue > best)){
                best = currentValue;
                bestSolution = currentSol;
            }
        }

        if(!bestSolution) throw NoSolutionFoundException();
        else return bestSolution;
    }

    std::shared_ptr<Modeling::Solution> Solver::getBestSolution() const {
        const auto* thisWithHeuristic = dynamic_cast<const Modeling::HeuristicDrivenSearchProblem *>(this->getSolverProblem().lock().get());
        if (thisWithHeuristic == nullptr) 
            throw NoHeuristicFunctionFoundException("Solver::getBestSolution");

        double best = std::numeric_limits<double>::infinity(), currentValue;
        std::shared_ptr<Modeling::Solution> bestSolution, currentSol;
        std::shared_ptr<Solver::SolverAlgorithm> step;

        for (unsigned int i = 0; i < this->countSolvingSteps(); i++) {
            step = this->getSolvingStep(i).lock();
            currentSol = step->getAlgorithm().lock()->getBestSolution().lock();
            if (!currentSol) continue;
            currentValue = thisWithHeuristic->trustedHeuristic(currentSol->getStateSolution().lock());
            if (currentValue < best){
                best = currentValue;
                bestSolution = currentSol;
            }
        }
        if(!bestSolution) throw NoSolutionFoundException();
        else return bestSolution;
    }

    const std::weak_ptr<SolverMonitor> Solver::getMonitor() const {
        auto itr = this->StrongAssociationRole<MonitorAssoc, 0, 1>::cbeginLinks();
        if (itr == this->StrongAssociationRole<MonitorAssoc, 0, 1>::cendLinks()) 
            throw MultiplicityConstraintException("Solver", "monitorAssoc", 
                this->StrongAssociationRole<MonitorAssoc, 0, 1>::countLinks());
        return (*itr)->getMonitor();
    }

    void Solver::setMonitor(std::shared_ptr<SolverMonitor> mon) {
        if (this->isMonitored()) (*(this->StrongAssociationRole<MonitorAssoc, 0, 1>::cbeginLinks()))->setMonitor(mon);
        else {
            auto thisPtr = this->shared_from_this();
            auto nonConst = std::const_pointer_cast<Solver>(thisPtr);
            auto link = std::make_shared<MonitorAssoc>(nonConst, mon);
            this->StrongAssociationRole<MonitorAssoc, 0, 1>::addLink(std::move(link));  
        }      
    }

    bool Solver::isMonitored() const {
        return this->StrongAssociationRole<MonitorAssoc, 0, 1>::countLinks() == 1;
    }

    const unsigned int Solver::SolverAlgorithm::getExecutions() const {
        return this->executions;
    }

    const bool Solver::SolverAlgorithm::alwaysReInit() const {
        return this->reInit;
    }

    const std::weak_ptr<Solver> Solver::SolverAlgorithm::getSolver() const {
        auto result = this->WeakAssociationRole<SolvingOrder, 1, 1>::cbeginLinks();
        if (result == this->WeakAssociationRole<SolvingOrder, 1, 1>::cendLinks()) 
            throw MultiplicityConstraintException("SolverAlgorithm", "solvingOrder", 
                this->WeakAssociationRole<SolvingOrder, 1, 1>::countLinks());
        return (*result).lock()->getSolver();
    }

    const std::weak_ptr<Algorithms::Algorithm> Solver::SolverAlgorithm::getAlgorithm() const {
        auto result = this->WeakAssociationRole<SolvingStep, 1, 1>::cbeginLinks();
        if (result == this->WeakAssociationRole<SolvingStep, 1, 1>::cendLinks()) 
            throw MultiplicityConstraintException("SolverAlgorithm", "solvingStep",
                this->WeakAssociationRole<SolvingStep, 1, 1>::countLinks());
        return (*result).lock()->getAlgorithm();
    }

    void Solver::SolverAlgorithm::setSolver(const std::shared_ptr<Solver> &solver) {
        try {
            auto thisPtr = this->shared_from_this();
            auto link = std::make_shared<SolvingOrder>(solver, thisPtr);
            this->WeakAssociationRole<SolvingOrder, 1, 1>::addLink(link);
            solver->OrderedAssociationRole<SolvingOrder, 0, STAR>::addLink(link);
        }
        catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("SolverAlgorithm", "solvingOrder"); }
    }

    void Solver::SolverAlgorithm::setAlgorithm(const std::shared_ptr<Algorithms::Algorithm> &alg) {
        try {
            auto thisPtr = this->shared_from_this();
            auto link = std::make_shared<SolvingStep>(alg, thisPtr);
            this->WeakAssociationRole<SolvingStep, 1, 1>::addLink(link);
            alg->StrongAssociationRole<SolvingStep, 1, STAR>::addLink(link);
        }
        catch (MultiplicityConstraintException& e) { throw ImmutablePropertyException("SolverAlgorithm", "solvingStep"); }
    }

    Solver::SolverAlgorithm::SolverAlgorithm(const unsigned int executions, const bool alwaysReInit)
        : executions(executions), reInit(alwaysReInit) { }

}