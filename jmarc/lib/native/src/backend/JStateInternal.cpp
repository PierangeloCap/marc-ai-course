#include "../../header/backend/JStateInternal.h"
#include <cassert>


namespace JMARC {

    const jobject* JStateInternal::getRef() const {
        return &(this->ref);
    }

    bool JStateInternal::operator==(const Modeling::State& s) {
        JNIEnv* env;
        //jint rs = (this->jvm)->AttachCurrentThread((void**)&env, NULL);
        jint rs = (this->jvm)->GetEnv((void**)&env, JNI_VERSION_1_6);
        assert (rs == JNI_OK);

        auto js = dynamic_cast<const JStateInternal*>(&s);
        auto sRef = js->getRef();

        if (this->equals == NULL) {
            jclass thisClass = env->GetObjectClass(this->ref);
            this->equals = env->GetMethodID(thisClass, "equals", "(Ljmarc/modeling/MARCState;)Z");
            env->DeleteLocalRef(thisClass);
        }

        jboolean res = env->CallBooleanMethod(this->ref, this->equals, *sRef);
        
        //(this->jvm)->DetachCurrentThread();
        return (bool)res;
    }

    JStateInternal::JStateInternal(JNIEnv* env, jobject ref) : Modeling::State() {
        this->ref = env->NewGlobalRef(ref);
        jint rs = env->GetJavaVM(&(this->jvm));
        assert (rs == JNI_OK);
    }

    JStateInternal::~JStateInternal() {
        //std::cout << "I am being eliminated" << /*eliminated++ <<*/ std::endl;
        JNIEnv* env;
        //jint rs = (this->jvm)->AttachCurrentThread((void**)&env, NULL);
        jint rs = (this->jvm)->GetEnv((void**)&env, JNI_VERSION_1_6);
        assert (rs == JNI_OK);
        env->DeleteGlobalRef(this->ref);
        //(this->jvm)->DetachCurrentThread();
    }

}