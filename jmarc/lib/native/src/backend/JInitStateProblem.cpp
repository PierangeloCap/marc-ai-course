#include "../../header/backend/JInitStateProblem.h"
#include "../../header/backend/JDimensionType.h"


namespace JMARC {

    JInitStateProblem::JInitStateProblem(const JDimensionType& dim, JNIEnv* env, jobject* ref, Modeling::direction opt) :
        Modeling::InitialStateProblem(std::make_unique<JDimensionType>(dim.getDim())),
        Modeling::Problem(std::make_unique<JDimensionType>(dim.getDim())),
        JProblem(dim, env, ref, opt) {}

}