#include "../../header/jni/jmarc_modeling_MARCAction.h"
#include "../../header/jni/Handle.h"
#include "../../header/backend/JAction.h"
#include "../../header/backend/JProblem.h"

#include <memory>


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCAction_createNativeObject(JNIEnv* env, jobject thiz, jobject p, jstring label) {
    const char* cLabel = env->GetStringUTFChars(label, 0);
    std::string strLabel(cLabel);

    auto prob = HandleManager<std::shared_ptr<JMARC::JProblem>>::getHandle(env, p);
    auto act = new std::shared_ptr<JMARC::JAction>(new JMARC::JAction(env, &thiz, strLabel));
    env->ReleaseStringUTFChars(label, cLabel);
    (*act)->setProblem(*prob);
    return (jlong)act;
}


JNIEXPORT jobject JNICALL Java_jmarc_modeling_MARCAction_getActionProblem(JNIEnv* env, jobject thiz) {
    auto act = HandleManager<std::shared_ptr<JMARC::JAction>>::getHandle(env, thiz);
    std::shared_ptr<Modeling::Problem> prob = (*act)->getProblem().lock();
    auto jprob = std::dynamic_pointer_cast<JMARC::JProblem>(prob);
    return *(jprob->getRef());
}

/*
JNIEXPORT void JNICALL Java_JMARC_Modeling_MARCAction_setActionProblem(JNIEnv* env, jobject thiz, jobject prob) {
    auto act = HandleManager<std::shared_ptr<JAction>>::getHandle(env, thiz);
    auto prob = HandleManager<std::shared_ptr<JProblem>>::getHandle(env, prob);
    (*act)->setProblem(*prob);
}
*/