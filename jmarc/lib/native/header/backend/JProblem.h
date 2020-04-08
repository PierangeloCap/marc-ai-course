#ifndef JPROBLEM_H
#define JPROBLEM_H

#include <Modeling/HeuristicDrivenSearchProblem.h>
#include <Modeling/RandomExplorationProblem.h>
#include <Modeling/OptimizationProblem.h>

#include "JNIWrap.h"


namespace JMARC {

    class JDimensionType;

    class JProblem : public Modeling::RandomExplorationProblem, public Modeling::HeuristicDrivenSearchProblem,
                     public Modeling::OptimizationProblem, public JNIWrap {

    private:
        mutable jmethodID objTest = NULL;

        mutable jmethodID heur = NULL;

        mutable jmethodID objFunction = NULL;

        mutable jmethodID getRandState = NULL;        

    public:
        bool objectiveTest(const std::shared_ptr<Modeling::State>& s) const;

        double heuristic(const std::shared_ptr<Modeling::State>& s) const;

        double objectiveFunction(const std::shared_ptr<Modeling::Solution>& sol) const;

        std::shared_ptr<Modeling::State> getRandomState() const;

        JProblem(const JDimensionType& dim, JNIEnv* env, jobject* ref, Modeling::direction opt);

    };

}

#endif