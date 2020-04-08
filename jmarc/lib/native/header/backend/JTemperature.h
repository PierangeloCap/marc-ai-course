#ifndef JTEMPERATURE_H
#define JTEMPERATURE_H

#include <Solving/Algorithms/Temperature.h>

#include "JNIWrap.h"


namespace JMARC {

    class JTemperature : public JNIWrap, public Solving::Algorithms::Temperature {

    private:
        mutable jmethodID temp = NULL;
        
    protected:
        [[nodiscard]] double temperature(const unsigned int step) const override;

    public:
        JTemperature(JNIEnv* env, jobject* ref);

    };

}

#endif