#include "../../header/jni/jmarc_solving_MARCTemperature.h"
#include "../../header/backend/JTemperature.h"
#include <memory>


JNIEXPORT jlong JNICALL Java_jmarc_solving_MARCTemperature_createNativeObject(JNIEnv* env, jobject thiz) {    
    auto temp = new std::shared_ptr<JMARC::JTemperature>(new JMARC::JTemperature(env, &thiz));
    return (jlong)temp;
}
