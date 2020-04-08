#include "../../header/backend/JAction.h"
#include "../../header/backend/JState.h"
#include "../../header/backend/JStateInternal.h"
#include <iostream>


namespace JMARC {

    bool JAction::satisfiesPreconditions(const std::shared_ptr<Modeling::State>& s) const {
        auto ref = this->getRef();
        auto env = this->getEnv();

        const jobject* sRef;
        auto js = std::dynamic_pointer_cast<JStateInternal>(s);
        if (js) sRef = js->getRef();
        else {
            auto normal = std::dynamic_pointer_cast<JState>(s);
            sRef = normal->getRef();
        }

        if (this->prec == NULL) {
            jclass thisClass = this->getClass();
            this->prec = env->GetMethodID(thisClass, "satisfiesPreconditions", "(Ljmarc/modeling/MARCState;)Z");
            env->DeleteLocalRef(thisClass);
        }

        jboolean res = env->CallBooleanMethod(*ref, this->prec, *sRef);
        
        return (bool)res;          
    }

    std::shared_ptr<Modeling::State> JAction::evaluateEffects(const std::shared_ptr<Modeling::State>& s) const {
        auto ref = this->getRef();
        auto env = this->getEnv();

        const jobject* sRef;
        auto js = std::dynamic_pointer_cast<JStateInternal>(s);
        if (js) sRef = js->getRef();
        else {
            auto normal = std::dynamic_pointer_cast<JState>(s);
            sRef = normal->getRef();
        }

        if (this->effects == NULL) {
            jclass thisClass = this->getClass();
            this->effects = env->GetMethodID(thisClass, "evaluateEffects", "(Ljmarc/modeling/MARCState;)Ljmarc/modeling/MARCState;");
            env->DeleteLocalRef(thisClass);
        }

        jobject res = env->CallObjectMethod(*ref, this->effects, *sRef);

        std::shared_ptr<JStateInternal> nativeRes = std::make_shared<JStateInternal>(env, res);

        env->DeleteLocalRef(res);

        return nativeRes;
    }

    double JAction::cost(const std::shared_ptr<Modeling::State>& s) const {
        auto ref = this->getRef();
        auto env = this->getEnv();

        const jobject* sRef;
        auto js = std::dynamic_pointer_cast<JStateInternal>(s);
        if (js) sRef = js->getRef();
        else {
            auto normal = std::dynamic_pointer_cast<JState>(s);
            sRef = normal->getRef();
        }

        if (this->cst == NULL) {
            jclass thisClass = this->getClass();
            this->cst = env->GetMethodID(thisClass, "cost", "(Ljmarc/modeling/MARCState;)D");
            env->DeleteLocalRef(thisClass);
        }

        jdouble res = env->CallDoubleMethod(*ref, this->cst, *sRef);

        return (double)res;          
    }

    JAction::JAction(JNIEnv* env, jobject* ref, std::string description) :
        JNIWrap(env, ref), Modeling::Action(description) {}

}