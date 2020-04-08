#include "../../header/backend/JNIWrap.h"
#include <cassert>

#include <iostream>

namespace JMARC {

    JNIWrap::JNIWrap(JNIEnv* env, jobject* ref) {
        jint rs = env->GetJavaVM(&(this->jvm));
        assert (rs == JNI_OK);
        this->ref = env->NewWeakGlobalRef(*ref);
    } 

    const JavaVM* JNIWrap::getJVM() const {
        return this->jvm;
    }

    const jobject* JNIWrap::getRef() const {
        return &(this->ref);
    }

    JNIEnv* JNIWrap::getEnv() const {
        JNIEnv* env;
        //jint rs = (this->jvm)->AttachCurrentThread((void**)&env, NULL);
        jint rs = (this->jvm)->GetEnv((void**)&env, JNI_VERSION_1_6);
        assert (rs == JNI_OK);
        return env;
    }

    void JNIWrap::detachEnv() const {
        (this->jvm)->DetachCurrentThread();
    }

    long JNIWrap::getHandleField() const {
        auto env = this->getEnv();
        jclass c = this->getClass();
        jfieldID h = env->GetFieldID(c, "handle", "J");
        env->DeleteLocalRef(c);
        return (long)env->GetLongField(this->ref, h);
    }

    long JNIWrap::getHandleField(JNIEnv* env, jobject* obj) {
        jclass c = env->GetObjectClass(*obj);
        jfieldID h = env->GetFieldID(c, "handle", "J");
        env->DeleteLocalRef(c);
        return (long)env->GetLongField(*obj, h);
    }

    jclass JNIWrap::getClass() const {
        /*if (this->cls == NULL) {
            auto env = this->getEnv();
            jclass c = env->GetObjectClass(this->ref);
            this->cls = env->NewGlobalRef(c);
            env->DeleteLocalRef(c);
        }
        return this->cls;*/
        auto env = this->getEnv();
        return env->GetObjectClass(this->ref);
    }

    JNIWrap::~JNIWrap() {
        auto env = this->getEnv();
        env->DeleteWeakGlobalRef(this->ref);
    }

}