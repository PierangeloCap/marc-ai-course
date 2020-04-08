#include "../../header/jni/jmarc_solving_MARCSequentialSolver.h"
#include <Solving/SequentialSolver.h>
#include <Modeling/Solution.h>
#include <Utils/Exceptions/NoSolutionFoundException.h>
#include <Utils/Exceptions/NoApplicableActionException.h>
#include "../../header/backend/JSolution.h"
#include "../../header/backend/JState.h"
#include "../../header/backend/JStateInternal.h"
#include "../../header/jni/Handle.h"

#include <iostream>
#include <cassert>


JNIEXPORT jlong JNICALL Java_jmarc_solving_MARCSequentialSolver_createNativeObject(JNIEnv* env, jobject thiz) {
    auto solver = new std::shared_ptr<Solving::SequentialSolver>(new Solving::SequentialSolver());
    return (jlong)solver;
}


JNIEXPORT jobject JNICALL Java_jmarc_solving_MARCSequentialSolver_solve(JNIEnv* env, jobject thiz) {
    auto solv = HandleManager<std::shared_ptr<Solving::SequentialSolver>>::getHandle(env, thiz);
    try {
        std::shared_ptr<Modeling::Solution> s = (*solv)->trustedSolve();
        auto state = s->getStateSolution().lock();
        
        const jobject* sRef;
        auto js = std::dynamic_pointer_cast<JMARC::JStateInternal>(state);
        if (js) sRef = js->getRef();
        else {
            auto normal = std::dynamic_pointer_cast<JMARC::JState>(state);
            sRef = normal->getRef();
        }
        if (sRef == NULL || *sRef == NULL) throw "State in returned Solution is not a JState (missing JNI reference)";

        //if (env->ExceptionCheck() == JNI_TRUE) std::cout << "pending exceptions" << std::endl;

        jclass marcSol = env->FindClass("jmarc/modeling/MARCSolution");
	    jmethodID ctor = env->GetMethodID(marcSol, "<init>", "(Ljmarc/modeling/MARCState;)V");
        jobject result = env->NewObject(marcSol, ctor, *sRef);
        env->DeleteLocalRef(marcSol);
        return result;
    } catch (NoSolutionFoundException& e) {
        return NULL;
    } catch (NoApplicableActionException& e) {
        throw "Transition model incomplete: encountered a sink state";
    }         
}

