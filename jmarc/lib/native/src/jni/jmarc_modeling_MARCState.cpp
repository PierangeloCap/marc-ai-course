#include "../../header/jni/jmarc_modeling_MARCState.h"
#include "../../header/backend/JState.h"
#include "../../header/backend/JProblem.h"
#include "../../header/jni/Handle.h"


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCState_createNativeObject__Ljmarc_modeling_MARCProblem_2(JNIEnv* env, jobject thiz, jobject p) {   
    auto state = new std::shared_ptr<JMARC::JState>(new JMARC::JState(env, &thiz));
    auto prob = HandleManager<std::shared_ptr<JMARC::JProblem>>::getHandle(env, p);
    (*state)->setStateProblem(*prob);
    return (jlong)state;    
}


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCState_createNativeObject__(JNIEnv* env, jobject thiz) {
    auto state = new std::shared_ptr<JMARC::JState>(new JMARC::JState(env, &thiz));
    return (jlong)state;  
}


JNIEXPORT jobject JNICALL Java_jmarc_modeling_MARCState_getStateProblem(JNIEnv* env, jobject thiz) {
    auto state = HandleManager<std::shared_ptr<JMARC::JState>>::getHandle(env, thiz);
    std::shared_ptr<Modeling::Problem> p = (*state)->getStateProblem().lock();
    auto prob = std::dynamic_pointer_cast<JMARC::JProblem>(p);
    return *(prob->getRef());    
}


JNIEXPORT void JNICALL Java_jmarc_modeling_MARCState_setStateProblem(JNIEnv* env, jobject thiz, jobject p) {
    auto state = HandleManager<std::shared_ptr<JMARC::JState>>::getHandle(env, thiz);
    auto prob = HandleManager<std::shared_ptr<JMARC::JProblem>>::getHandle(env, p);
	jclass marcState = env->GetObjectClass(thiz);
    jmethodID addDep = env->GetMethodID(marcState, "addDependency", "(Ljmarc/MARCNativeWrapper;)V");
    env->CallVoidMethod(thiz, addDep, p);
    env->DeleteLocalRef(marcState);
    (*state)->setStateProblem(*prob);
}
