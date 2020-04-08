#include "../../header/backend/JProblem.h"
#include "../../header/backend/JState.h"
#include "../../header/backend/JStateInternal.h"
#include "../../header/backend/JSolution.h"
#include "../../header/backend/JDimensionType.h"

#include <Utils/Exceptions/NoHeuristicFunctionFoundException.h>
#include <Utils/Exceptions/NoRandomInterfaceFoundException.h>
#include <Utils/Exceptions/NoObjectiveFunctionFoundException.h>


namespace JMARC {

    bool JProblem::objectiveTest(const std::shared_ptr<Modeling::State>& s) const {
        auto ref = this->getRef();
        auto env = this->getEnv();

        const jobject* sRef;
        auto js = std::dynamic_pointer_cast<JStateInternal>(s);
        if (js) sRef = js->getRef();
        else {
            auto normal = std::dynamic_pointer_cast<JState>(s);
            sRef = normal->getRef();
        }

        if (this->objTest == NULL) {
            jclass thisClass = this->getClass();
            this->objTest = env->GetMethodID(thisClass, "objectiveTest", "(Ljmarc/modeling/MARCState;)Z");
            env->DeleteLocalRef(thisClass);
        }
        jboolean res = env->CallBooleanMethod(*ref, this->objTest, *sRef);
    
        return (bool)res;        
    }

    double JProblem::heuristic(const std::shared_ptr<Modeling::State>& s) const {
        auto ref = this->getRef();
        auto env = this->getEnv();

        const jobject* sRef;
        auto js = std::dynamic_pointer_cast<JStateInternal>(s);
        if (js) sRef = js->getRef();
        else {
            auto normal = std::dynamic_pointer_cast<JState>(s);
            sRef = normal->getRef();
        }

        if (this->heur == NULL) {
            jclass thisClass = this->getClass();
            this->heur = env->GetMethodID(thisClass, "heuristic", "(Ljmarc/modeling/MARCState;)D");
            env->DeleteLocalRef(thisClass);
            if (this->heur == NULL) {
                env->ExceptionClear(); 
                throw NoHeuristicFunctionFoundException("JProblem::heuristic");
            }
        }
        jdouble res = env->CallDoubleMethod(*ref, this->heur, *sRef);

        env->ExceptionDescribe();

        return (double)res;             
    }

    double JProblem::objectiveFunction(const std::shared_ptr<Modeling::Solution>& sol) const {
        auto ref = this->getRef();
        auto env = this->getEnv();

        const jobject* solRef;
        auto jsol = std::dynamic_pointer_cast<JSolution>(sol);
        if (!jsol) {
            const jobject* sRef;
            auto js = std::dynamic_pointer_cast<JStateInternal>(sol->getStateSolution().lock());
            if (js) sRef = js->getRef();
            else {
                auto normal = std::dynamic_pointer_cast<JState>(sol->getStateSolution().lock());
                if (!normal) throw "Incompatible types: given Solution is not a JMARC object";
                sRef = normal->getRef();
            }

            jclass marcSol = env->FindClass("jmarc/modeling/MARCSolution");
	        jmethodID ctor = env->GetMethodID(marcSol, "<init>", "(Ljmarc/modeling/MARCState;)V");
            jobject result = env->NewObject(marcSol, ctor, *sRef);
            auto newSol = *(reinterpret_cast<std::shared_ptr<JSolution> *>(JNIWrap::getHandleField(env, &result)));
            solRef = newSol->getRef();
            env->DeleteLocalRef(result);
            env->DeleteLocalRef(marcSol);
        }
        else solRef = jsol->getRef();

        if (this->objFunction == NULL) {
            jclass thisClass = this->getClass();
            this->objFunction = env->GetMethodID(thisClass, "objectiveFunction", "(Ljmarc/modeling/MARCSolution;)D");
            env->DeleteLocalRef(thisClass);
            if (this->objFunction == NULL) {
                env->ExceptionClear(); 
                throw NoObjectiveFunctionFoundException("JProblem::objectiveFunction()");
            }
        }
        jdouble res = env->CallDoubleMethod(*ref, this->objFunction, *solRef);

        return (double)res;               
    }

    std::shared_ptr<Modeling::State> JProblem::getRandomState() const {
        auto ref = this->getRef();
        auto env = this->getEnv();

        if (this->getRandState == NULL) {
            jclass thisClass = this->getClass();
            this->getRandState = env->GetMethodID(thisClass, "getRandomState", "()Ljmarc/modeling/MARCState;");
            env->DeleteLocalRef(thisClass);
            if (this->getRandState == NULL) {
                env->ExceptionClear();
                throw NoRandomInterfaceFoundException("JProblem::getRandomState()");
            }
        }
        jobject res = env->CallObjectMethod(*ref, this->getRandState);
        std::shared_ptr<JStateInternal> nativeRes = std::make_shared<JStateInternal>(env, res);
        env->DeleteLocalRef(res);

        return nativeRes;
    }

    JProblem::JProblem(const JDimensionType& dim, JNIEnv* env, jobject* ref, Modeling::direction opt) :
        Modeling::RandomExplorationProblem(std::make_unique<JDimensionType>(dim.getDim())), 
        Modeling::HeuristicDrivenSearchProblem(std::make_unique<JDimensionType>(dim.getDim())),
        Modeling::OptimizationProblem(std::make_unique<JDimensionType>(dim.getDim()), opt), 
        Modeling::Problem(std::make_unique<JDimensionType>(dim.getDim())), 
        JNIWrap(env, ref) {}

}