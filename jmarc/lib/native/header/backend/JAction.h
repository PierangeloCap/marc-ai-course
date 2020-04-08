#ifndef JACTION_H
#define JACTION_H

#include <Modeling/Action.h>

#include "JNIWrap.h"


namespace JMARC {

    class JAction : public Modeling::Action, public JNIWrap {

    private:
        mutable jmethodID prec = NULL;

        mutable jmethodID effects = NULL;

        mutable jmethodID cst = NULL;

    public:
        bool satisfiesPreconditions(const std::shared_ptr<Modeling::State>& s) const;

        std::shared_ptr<Modeling::State> evaluateEffects(const std::shared_ptr<Modeling::State>& s) const;

        double cost(const std::shared_ptr<Modeling::State>& s) const;

        JAction(JNIEnv* env, jobject* ref, std::string description);

    };

}

#endif