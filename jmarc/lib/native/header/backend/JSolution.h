#ifndef JSOLUTION_H
#define JSOLUTION_H

#include <Modeling/Solution.h>

#include "JNIWrap.h"

namespace JMARC {

    class JSolution : public Modeling::Solution, public JNIWrap {

    friend class JProblem;

    public:
        JSolution(JNIEnv* env, jobject* ref);
        
    };

}


#endif