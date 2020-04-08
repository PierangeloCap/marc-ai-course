#include "../../header/backend/JSolution.h"

namespace JMARC {

    JSolution::JSolution(JNIEnv* env, jobject* ref) :
        JNIWrap(env, ref), Modeling::Solution() {}

}