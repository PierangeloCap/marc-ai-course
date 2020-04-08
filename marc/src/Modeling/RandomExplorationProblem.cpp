#include <unordered_set>
#include <random>
#include "../../header/Modeling/RandomExplorationProblem.h"
#include "../../header/Modeling/HeuristicDrivenSearchProblem.h"
#include "../../header/Modeling/State.h"
#include "../../header/Modeling/Action.h"
#include "../../header/Utils/Exceptions/ViolatedPostconditionsException.h"
#include "../../header/Utils/Exceptions/ViolatedPreconditionsException.h"
#include "../../header/Utils/Exceptions/NoApplicableActionException.h"
#include "../../header/Utils/Exceptions/NoHeuristicFunctionFoundException.h"


namespace Modeling {
    
    std::shared_ptr<Action> RandomExplorationProblem::getRandomApplicableAction(const std::shared_ptr<State>& s) const {
        if (s->getStateProblem().lock().get() != this) 
            throw ViolatedPreconditionsException("RandomExplorationProblem", "getRandomApplicableAction");
        std::unordered_set<std::shared_ptr<Action>> possible = this->getPossibleActions(s);
        if (possible.empty()) return nullptr;
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, possible.size()-1);
        return *(std::next(possible.begin(), dist(rd)));
    }

    std::shared_ptr<Action> RandomExplorationProblem::getRandomBestAction(unsigned int samples, const std::shared_ptr<State>& s) const {
        if (s->getStateProblem().lock().get() != this) 
            throw ViolatedPreconditionsException("RandomExplorationProblem", "getRandomBestAction");
        const auto* thisWithHeuristic = dynamic_cast<const HeuristicDrivenSearchProblem *>(this);
        if (thisWithHeuristic == nullptr) 
            throw NoHeuristicFunctionFoundException("RandomExplorationProblem::getRandomBestAction");
        double best, curr;
        std::shared_ptr<Action> result, a;
        best = std::numeric_limits<double>::infinity();
        for (unsigned int i = 0; i < samples; i++){
            try{
                a = this->getRandomApplicableAction(s);
                if (a == nullptr) break;
                curr = thisWithHeuristic->trustedHeuristic(a->trustedEvaluateEffects(s));
                if(curr < best) {
                    best = curr;
                    result = a;
                }
            }
            catch(NoApplicableActionException& e){
                throw NoApplicableActionException();
            }
        }
        return result;
    }

    std::shared_ptr<State> RandomExplorationProblem::trustedGetRandomState() const {
        std::shared_ptr<State> result = this->getRandomState();
        try {
            if (result->getStateProblem().lock().get() != this) 
                throw ViolatedPostconditionsException("RandomExplorationProblem", "getRandomState");
        }
        catch (MultiplicityConstraintException& e) {
            auto thisPtr = this->shared_from_this();
            auto nonConst = std::const_pointer_cast<RandomExplorationProblem>(thisPtr);
            auto problem = std::dynamic_pointer_cast<Problem>(nonConst);
            result->setStateProblem(std::move(problem));
        }
        return result;
    }

    std::shared_ptr<State> RandomExplorationProblem::getRandomNeighbor(const std::shared_ptr<State>& s) const {
        try { return this->getRandomApplicableAction(s)->trustedEvaluateEffects(s); }
        catch (NoApplicableActionException& e) { throw NoApplicableActionException(); }
    }

    std::shared_ptr<State> RandomExplorationProblem::getBestRandomSampledNeighbor(unsigned int samples, const std::shared_ptr<State>& s) const {
        try { return this->getRandomBestAction(samples, s)->trustedEvaluateEffects(s); }
        catch (NoApplicableActionException& e) { throw NoApplicableActionException(); }
    }
    
    RandomExplorationProblem::RandomExplorationProblem(std::unique_ptr<ProblemDimensionType> dim) : Problem(std::move(dim)) { }

}
