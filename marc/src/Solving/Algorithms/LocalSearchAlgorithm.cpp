#include <memory>

#include "../../../header/Solving/Algorithms/LocalSearchAlgorithm.h"
#include "../../../header/Solving/Algorithms/OptimalSolution.h"
#include "../../../header/Solving/Algorithms/BestSolution.h"


#include "../../../header/Modeling/InitialStateProblem.h"
#include "../../../header/Modeling/RandomExplorationProblem.h"
#include "../../../header/Modeling/OptimizationProblem.h"
#include "../../../header/Modeling/HeuristicDrivenSearchProblem.h"
#include "../../../header/Modeling/Solution.h"

#include "../../../header/Utils/Exceptions/NoInitialStateFoundException.h"
#include "../../../header/Utils/Exceptions/NoRandomInterfaceFoundException.h"
#include "../../../header/Utils/Exceptions/NoSearchStartingPointFound.h"
#include "../../../header/Utils/Exceptions/NoApplicableActionException.h"
#include "../../../header/Utils/Exceptions/NoHeuristicFunctionFoundException.h"
#include "../../../header/Utils/Exceptions/NoObjectiveFunctionFoundException.h"
#include "../../../header/Utils/Exceptions/NoSolutionFoundException.h"

namespace Solving {

    namespace Algorithms {

        std::shared_ptr<Modeling::Solution> LocalSearchAlgorithm::getNextSolution() {
            std::shared_ptr<Modeling::Solution> current;
            try { 
                current = this->getSearchStartingPoint(); 
            } catch (NoSearchStartingPointFound &e) { 
                throw NoSearchStartingPointFound(); 
            }

            bool opt = false;
            try {
                double obj = this->objectiveFunction(current);
                bool opt = true;
            } catch (NoObjectiveFunctionFoundException& e) { }
            std::shared_ptr<Algorithm> thisPtr = this->shared_from_this();
            this->storeBestSolution(std::make_shared<BestSolution>(thisPtr, current)); //store best solution so far
            this->cacheBestValue(this->heuristicFunction(current));
            if (opt) this->storeOptimalSolution(std::make_shared<OptimalSolution>(thisPtr, current)); //store optimal solution so far

            std::shared_ptr<Modeling::Action> a;
            std::shared_ptr<Modeling::Solution> candidate;
            double diffH, diffOF;

            while (this->continueSearch()) {
                this->incrementIterationCounter();
                try { 
                    a = this->chooseAction(current); 
                } catch (NoApplicableActionException& e) { 
                    break; 
                }
                //candidate = std::make_shared<Modeling::Solution>();
                //candidate->setStateSolution(this->getAlgorithmProblem().lock()->doAction(current->getStateSolution().lock(), a));
                candidate = this->getSuccessor(a, current);
                
                if (this->visitCandidate(candidate, current)) {
                    current = candidate;
                    double currVal = this->getSuccessorValue(current);
                    //diffH = this->heuristicFunction(this->getBestSolution().lock()) - this->heuristicFunction(current);
                    diffH = this->getBestValue() - currVal;
                    if (diffH > 0) {
                        this->cacheBestValue(currVal);
                        this->setBestIteration(this->getIterationCounter());
                        this->storeBestSolution(std::make_shared<BestSolution>(thisPtr, current));
                        if (opt) {
                            diffOF = this->objectiveFunction(this->getOptimalSolution().lock()) - this->objectiveFunction(current);
                            if ((this->getOptimizationDirection() == Modeling::direction::MIN && diffOF >= 0) ||
                                (this->getOptimizationDirection() == Modeling::direction::MAX && diffOF <= 0))
                                this->storeOptimalSolution(std::make_shared<OptimalSolution>(thisPtr, current));
                        }
                    }
                }
            }
            auto result = this->getBestSolution().lock();
            if (!result) throw NoSolutionFoundException();
            return result;
        }

        bool LocalSearchAlgorithm::continueSearch() const {
            return (this->iterationCounter - this->bestIteration) < this->maxIdleIterations;
        }

        void LocalSearchAlgorithm::reInit() {
            this->iterationCounter = 0;
            this->bestIteration = 0;
            this->removeOptimalSolution();
            this->nextCache.reset();
            this->nextHeurCache = -1;
            this->bestValueCache = -1;
            Algorithm::reInit();
        }

        std::shared_ptr<Modeling::Solution> LocalSearchAlgorithm::getSearchStartingPoint() const {
            std::shared_ptr<Modeling::Problem> p = this->getAlgorithmProblem().lock();
            std::shared_ptr<Modeling::State> init;
            auto result = std::make_shared<Modeling::Solution>();
            if (this->getIterationCounter() > 0 && this->StrongAssociationRole<BestSolution, 0, 1>::countLinks() > 0) 
                return this->getBestSolution().lock();
            try { init = this->getInitialState(p); }
            catch (NoInitialStateFoundException &e) {
                try { init = this->getRandomState(p); }
                catch (NoRandomInterfaceFoundException &e) { throw NoSearchStartingPointFound(); }
            }

            result->setStateSolution(std::move(init));
            return result;
        }

        std::shared_ptr<Modeling::State> LocalSearchAlgorithm::getInitialState(std::shared_ptr<Modeling::Problem> &prob) const {
            auto *initProb = dynamic_cast<Modeling::InitialStateProblem *>(prob.get());
            if (initProb == nullptr) 
                throw NoInitialStateFoundException("LocalSearchAlgorithm::getInitialState");
            return initProb->getInitialState().lock();
        }

        std::shared_ptr<Modeling::State> LocalSearchAlgorithm::getRandomState(std::shared_ptr<Modeling::Problem> &prob) const {
            auto *randProb = dynamic_cast<Modeling::RandomExplorationProblem *>(prob.get());
            if (randProb == nullptr) throw NoRandomInterfaceFoundException("LocalSearchAlgorithm::getRandomState");
            return randProb->trustedGetRandomState();
        }

        double LocalSearchAlgorithm::heuristicFunction(std::shared_ptr<Modeling::Solution> sol) const {
            if (this->cachedHeuristic == nullptr) {
                auto *heuristicProblem = dynamic_cast<Modeling::HeuristicDrivenSearchProblem *>(this->getAlgorithmProblem().lock().get());
                if (heuristicProblem == nullptr) 
                    throw NoHeuristicFunctionFoundException("LocalSearchAlgorithm::heuristicFunction");
                this->cachedHeuristic = heuristicProblem;
            }
            return this->cachedHeuristic->trustedHeuristic(sol->getStateSolution().lock());
        }

        double LocalSearchAlgorithm::objectiveFunction(std::shared_ptr<Modeling::Solution> sol) const {
            if (this->cachedOptimization == nullptr) {
                auto *optimizationProblem = dynamic_cast<Modeling::OptimizationProblem *>(this->getAlgorithmProblem().lock().get());
                if (optimizationProblem == nullptr) 
                    throw NoObjectiveFunctionFoundException("LocalSearchAlgorithm::objectiveFunction");
                this->cachedOptimization = optimizationProblem;
            }
            return this->cachedOptimization->trustedObjectiveFunction(sol);
        }

        Modeling::direction LocalSearchAlgorithm::getOptimizationDirection() const {
            if (this->cachedOptimization == nullptr) {
                auto *optimizationProblem = dynamic_cast<Modeling::OptimizationProblem *>(this->getAlgorithmProblem().lock().get());
                if (optimizationProblem == nullptr) 
                    throw NoObjectiveFunctionFoundException("LocalSearchAlgorithm::getOptimizationDirection");
                this->cachedOptimization = optimizationProblem;
            }
            return this->cachedOptimization->getDirection();
        }

        unsigned int LocalSearchAlgorithm::getMaxIdleIterations() const {
            return this->maxIdleIterations;
        }

        unsigned int LocalSearchAlgorithm::getBestIteration() const {
            return this->bestIteration;
        }

        void LocalSearchAlgorithm::setBestIteration(unsigned int best) {
            this->bestIteration = best;
        }

        const std::weak_ptr<Modeling::Solution> LocalSearchAlgorithm::getOptimalSolution() const {
            auto result = this->StrongAssociationRole<OptimalSolution, 0, 1>::cbeginLinks();
            if (result == this->StrongAssociationRole<OptimalSolution, 0, 1>::cendLinks()) return std::shared_ptr<Modeling::Solution>(nullptr);
            return (*result)->getSolution();
        }

        void LocalSearchAlgorithm::storeOptimalSolution(std::shared_ptr<OptimalSolution> sol) {
            if (this->StrongAssociationRole<OptimalSolution, 0, 1>::countLinks() == 0)
                this->StrongAssociationRole<OptimalSolution, 0, 1>::addLink(std::move(sol));
            else (*(this->StrongAssociationRole<OptimalSolution, 0, 1>::cbeginLinks()))->setSolution(sol->getSolution().lock());
        }

        LocalSearchAlgorithm::LocalSearchAlgorithm(const unsigned int maxIdleIterations) : maxIdleIterations(maxIdleIterations) { }

        void LocalSearchAlgorithm::removeOptimalSolution() {
            if (this->StrongAssociationRole<OptimalSolution, 0, 1>::countLinks() > 0) {
                this->StrongAssociationRole<OptimalSolution, 0, 1>::removeLink(*(this->StrongAssociationRole<OptimalSolution, 0, 1>::cbeginLinks()));
            }
        }

        void LocalSearchAlgorithm::cacheSuccessor(std::shared_ptr<Modeling::State> succ) const {
            this->nextCache = succ;
        }

        void LocalSearchAlgorithm::cacheSuccessorValue(const double val) const {
            this->nextHeurCache = val;
        }

        void LocalSearchAlgorithm::cacheBestValue(const double val) const {
            this->bestValueCache = val;
        }

        std::shared_ptr<Modeling::Solution> 
        LocalSearchAlgorithm::getSuccessor(const std::shared_ptr<Modeling::Action>& act, 
                                           const std::shared_ptr<Modeling::Solution>& curr) const {
            std::shared_ptr<Modeling::State> next;
            std::shared_ptr<Modeling::Solution> res = std::make_shared<Modeling::Solution>();
            if (this->nextCache) next = this->nextCache;
            else next = act->trustedEvaluateEffects(curr->getStateSolution().lock());
            
            res->setStateSolution(std::move(next));
            return res;
        }

        double LocalSearchAlgorithm::getSuccessorValue(const std::shared_ptr<Modeling::Solution>& succ) const {
            if (this->nextHeurCache != -1) return this->nextHeurCache;
            else return this->heuristicFunction(succ);
        }

        double LocalSearchAlgorithm::getBestValue() const {
            if (this->bestValueCache == -1) 
                this->bestValueCache = this->heuristicFunction(this->getBestSolution().lock());
            return this->bestValueCache;
        }

    }

}