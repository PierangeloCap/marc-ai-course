#include "../../header/jni/jmarc_modeling_MARCSolution.h"
#include "../../header/backend/JSolution.h"
#include "../../header/backend/JState.h"
#include "../../header/backend/JStateInternal.h"
#include "../../header/backend/JNIWrap.h"
#include "../../header/jni/Handle.h"


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCSolution_createNativeObject(JNIEnv* env, jobject thiz, jobject s) {
   
    auto sol = new std::shared_ptr<JMARC::JSolution>(new JMARC::JSolution(env, &thiz));

    std::shared_ptr<Modeling::State>* statePass = 
        reinterpret_cast<std::shared_ptr<Modeling::State>*>(JMARC::JNIWrap::getHandleField(env, &s));

    (*sol)->setStateSolution(*statePass);

    return (jlong)sol;
}


JNIEXPORT jobject JNICALL Java_jmarc_modeling_MARCSolution_getStateSolution(JNIEnv* env, jobject thiz) {
    auto sol = HandleManager<std::shared_ptr<JMARC::JSolution>>::getHandle(env, thiz);
    std::shared_ptr<Modeling::State> s = (*sol)->getStateSolution().lock();
    auto state = std::dynamic_pointer_cast<JMARC::JState>(s);
    return *(state->getRef());
}

/*
JNIEXPORT void JNICALL Java_JMARC_Modeling_MARCSolution_setStateSolution(JNIEnv* env, jobject thiz, jobject s)  {
    auto sol = HandleManager<std::shared_ptr<JSolution>>::getHandle(env, thiz);
    auto state = HandleManager<std::shared_ptr<JState>>::getHandle(env, s);
    (*sol)->setStateSolution(*state);
}
*/
