#include "../../header/jni/jmarc_solving_MARCSolver.h"
#include <Solving/Solver.h>
#include <Solving/SolverMonitor.h>
#include <Solving/Algorithms/Algorithm.h>
#include "../../header/backend/JProblem.h"
#include "../../header/jni/Handle.h"


JNIEXPORT jobject JNICALL Java_jmarc_solving_MARCSolver_getSolverProblem(JNIEnv* env, jobject thiz) {
    auto solv = HandleManager<std::shared_ptr<Solving::Solver>>::getHandle(env, thiz);
    std::shared_ptr<Modeling::Problem> p = (*solv)->getSolverProblem().lock();
    auto prob = std::dynamic_pointer_cast<JMARC::JProblem>(p);
    return *(prob->getRef());    
}


JNIEXPORT void JNICALL Java_jmarc_solving_MARCSolver_setSolverProblem(JNIEnv* env, jobject thiz, jobject p) {
    auto solv = HandleManager<std::shared_ptr<Solving::Solver>>::getHandle(env, thiz);
    auto prob = HandleManager<std::shared_ptr<JMARC::JProblem>>::getHandle(env, p);
    jclass solver = env->GetObjectClass(thiz);
    jmethodID addDep = env->GetMethodID(solver, "addDependency", "(Ljmarc/MARCNativeWrapper;)V");
    env->CallVoidMethod(thiz, addDep, p);
    env->DeleteLocalRef(solver);
    (*solv)->setSolverProblem(*prob);
}


JNIEXPORT void JNICALL Java_jmarc_solving_MARCSolver_scheduleAlgorithm(JNIEnv* env, jobject thiz, jobject a, jint e, jboolean ri) {
    auto solv = HandleManager<std::shared_ptr<Solving::Solver>>::getHandle(env, thiz);
    auto alg = HandleManager<std::shared_ptr<Solving::Algorithms::Algorithm>>::getHandle(env, a);
    jclass solver = env->GetObjectClass(thiz);
    jmethodID addDep = env->GetMethodID(solver, "addDependency", "(Ljmarc/MARCNativeWrapper;)V");
    env->CallVoidMethod(thiz, addDep, a);
    int exec = (int)e;
    bool alwaysReInit = (bool)ri;
    env->DeleteLocalRef(solver);
    (*solv)->scheduleAlgorithm(*alg, exec, alwaysReInit);
}

JNIEXPORT void JNICALL Java_jmarc_solving_MARCSolver_setMonitor(JNIEnv* env, jobject thiz, jobject mon) {
    auto solv = HandleManager<std::shared_ptr<Solving::Solver>>::getHandle(env, thiz);
    auto monitor = HandleManager<std::shared_ptr<Solving::SolverMonitor>>::getHandle(env, mon);
    (*solv)->setMonitor(*monitor);
}

