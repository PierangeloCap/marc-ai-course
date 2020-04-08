#include "../../header/jni/jmarc_solving_MARCORBSolver.h"
#include <Solving/ORBSolver.h>
#include "../../header/backend/JStateInternal.h"
#include "../../header/backend/JState.h"
#include "../../header/backend/JSolution.h"
#include <Modeling/Solution.h>
#include <Modeling/State.h>
#include <Utils/Exceptions/NoSolutionFoundException.h>
#include <Utils/Exceptions/NoApplicableActionException.h>
#include "../../header/jni/Handle.h"

#include <vector>


JNIEXPORT jlong JNICALL Java_jmarc_solving_MARCORBSolver_createNativeObject(JNIEnv* env, jobject thiz, jint samples) {
    auto solver = new std::shared_ptr<Solving::ORBSolver>(new Solving::ORBSolver((unsigned int)samples));
    return (jlong)solver;    
}

JNIEXPORT jobject JNICALL Java_jmarc_solving_MARCORBSolver_solve(JNIEnv* env, jobject thiz) {
    auto solv = HandleManager<std::shared_ptr<Solving::ORBSolver>>::getHandle(env, thiz);
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

JNIEXPORT void JNICALL Java_jmarc_solving_MARCORBSolver_addBootstrapState(JNIEnv* env, jobject thiz, jobject s) {
    auto solv = HandleManager<std::shared_ptr<Solving::ORBSolver>>::getHandle(env, thiz);
	auto state = HandleManager<std::shared_ptr<JMARC::JState>>::getHandle(env, s);
    (*solv)->addBootstrapState(*state);
}

JNIEXPORT void JNICALL Java_jmarc_solving_MARCORBSolver_bootstrap(JNIEnv* env, jobject thiz) {
    auto solv = HandleManager<std::shared_ptr<Solving::ORBSolver>>::getHandle(env, thiz);
    (*solv)->bootstrap();
}

JNIEXPORT jobject JNICALL Java_jmarc_solving_MARCORBSolver_getBootstrap(JNIEnv* env, jobject thiz) {
    auto solv = HandleManager<std::shared_ptr<Solving::ORBSolver>>::getHandle(env, thiz);
    std::vector<std::shared_ptr<Modeling::State>> boot = (*solv)->getBootstrap();

	jclass vecClass = env->FindClass("java/util/Vector");
	jmethodID vecCtor = env->GetMethodID(vecClass, "<init>", "()V");
	jmethodID add = env->GetMethodID(vecClass, "add", "(Ljava/lang/Object;)Z");
	jobject result = env->NewObject(vecClass, vecCtor);

    // env->ExceptionDescribe();

    unsigned int i = 0;
    for (auto itr = boot.begin(); itr != boot.end(); itr++) {
        auto s = *itr;
		auto curr = std::dynamic_pointer_cast<JMARC::JStateInternal>(s);
        jobject jcurr = *(curr->getRef());
        env->CallBooleanMethod(result, add, jcurr);
		// env->DeleteLocalRef(jcurr);
    }
    env->DeleteLocalRef(vecClass);
	return result;
}
