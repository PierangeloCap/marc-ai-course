#ifndef JINITSTATEPROBLEM_H
#define JINITSTATEPROBLEM_H

#include <Modeling/InitialStateProblem.h>

#include "JProblem.h"

namespace JMARC {

    class JInitStateProblem : public JProblem, public Modeling::InitialStateProblem {

    public:
        JInitStateProblem(const JDimensionType& dim, JNIEnv* env, jobject* ref, Modeling::direction opt);

    };


}


#endif 