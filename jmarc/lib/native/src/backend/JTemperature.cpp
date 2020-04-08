#include "../../header/backend/JTemperature.h"

namespace JMARC {

    double JTemperature::temperature(const unsigned int step) const {
        auto ref = this->getRef();
        auto env = this->getEnv();
        
        if (this->temp == NULL) {
            jclass thisClass = this->getClass();
            this->temp = env->GetMethodID(thisClass, "temperature", "(I)D");
            env->DeleteLocalRef(thisClass);
        }

        jdouble res = env->CallDoubleMethod(*ref, this->temp, (jint)step);
        return (double)res;     
    }

    JTemperature::JTemperature(JNIEnv* env, jobject* ref) :
        JNIWrap(env, ref) { }


}