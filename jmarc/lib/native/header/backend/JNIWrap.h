#ifndef JNIWRAP_H
#define JNIWRAP_H

#include <jni.h>
#include <memory>

namespace JMARC {

    class JNIWrap {

    private:
        JavaVM *jvm;

        jobject ref;

    public:
        const JavaVM* getJVM() const;

        const jobject* getRef() const;

        JNIEnv* getEnv() const;

        void detachEnv() const;

        long getHandleField() const;

        static long getHandleField(JNIEnv* env, jobject* obj);

        jclass getClass() const;

        JNIWrap(JNIEnv* env, jobject* ref);

        ~JNIWrap();

    }; 

}

#endif