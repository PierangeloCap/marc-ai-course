#include "../../header/backend/JState.h"
#include <Utils/Exceptions/IncompatibleStateTypeException.h>

namespace JMARC {

    bool JState::operator==(const Modeling::State& s) {
        auto ref = this->getRef();
        auto env = this->getEnv();

        auto js = dynamic_cast<const JState*>(&s);
        if (!js) throw IncompatibleStateTypeException();
        auto sRef = js->getRef();

        if (this->equals == NULL) {
            jclass thisClass = this->getClass();
            this->equals = env->GetMethodID(thisClass, "equals", "(Ljmarc/modeling/MARCState;)Z");
            env->DeleteLocalRef(thisClass);
        }

        jboolean res = env->CallBooleanMethod(*ref, this->equals, *sRef);
        return (bool)res;
    }

    JState::JState(JNIEnv* env, jobject* ref) :
        JNIWrap(env, ref) {}

}