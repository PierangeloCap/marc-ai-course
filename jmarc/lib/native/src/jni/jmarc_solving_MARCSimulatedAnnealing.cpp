#include "../../header/jni/jmarc_solving_MARCSimulatedAnnealing.h"
#include <Solving/Algorithms/SimulatedAnnealing.h>
#include "../../header/backend/JTemperature.h"
#include "../../header/jni/Handle.h"


JNIEXPORT jlong JNICALL Java_jmarc_solving_MARCSimulatedAnnealing_createNativeObject(JNIEnv* env, jobject thiz, jint maxIdle) {
    auto iter = (int)maxIdle;
    if (iter < 0) throw "Value " + std::to_string(iter) + " illegal for argument \'maxIdleIterations\' (negative value)";
    auto sim = new std::shared_ptr<Solving::Algorithms::SimulatedAnnealing>(new Solving::Algorithms::SimulatedAnnealing(iter));
    return (jlong)sim;    
}


JNIEXPORT void JNICALL Java_jmarc_solving_MARCSimulatedAnnealing_setTemperature(JNIEnv* env, jobject thiz, jobject t) {
    auto sim = HandleManager<std::shared_ptr<Solving::Algorithms::SimulatedAnnealing>>::getHandle(env, thiz);
    auto temp = HandleManager<std::shared_ptr<JMARC::JTemperature>>::getHandle(env, t);
	jclass simAnn = env->GetObjectClass(thiz);
    jmethodID addDep = env->GetMethodID(simAnn, "addDependency", "(Ljmarc/MARCNativeWrapper;)V");
    env->CallVoidMethod(thiz, addDep, t);
    env->DeleteLocalRef(simAnn);
    (*sim)->setTemperature(*temp);
}

