#ifndef JSTATE_H
#define JSTATE_H

#include <Modeling/State.h>
#include "JNIWrap.h"


namespace JMARC {

    class JState : public Modeling::State, public JNIWrap {

    private:
        mutable jmethodID equals = NULL;

    public:
        bool operator==(const Modeling::State& s);

        JState(JNIEnv* env, jobject* ref);

    };

}


#endif