#ifndef JSTATEINTERNAL_H
#define JSTATEINTERNAL_H

#include <Modeling/State.h>
#include <jni.h>


namespace JMARC {

    class JStateInternal : public Modeling::State {

    private:
        JavaVM *jvm;

        jobject ref;

        mutable jmethodID equals = NULL;

    public:
        const jobject* getRef() const;

        bool operator==(const Modeling::State& s);

        JStateInternal(JNIEnv* env, jobject ref);

        ~JStateInternal();

    };

}


#endif