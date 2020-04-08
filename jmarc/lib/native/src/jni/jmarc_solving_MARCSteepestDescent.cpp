#include "../../header/jni/jmarc_solving_MARCSteepestDescent.h"
#include <Solving/Algorithms/SteepestDescent.h>


JNIEXPORT jlong JNICALL Java_jmarc_solving_MARCSteepestDescent_createNativeObject(JNIEnv* env, jobject thiz) {
    auto steep = new std::shared_ptr<Solving::Algorithms::SteepestDescent>(new Solving::Algorithms::SteepestDescent());
 
    return (jlong)steep;
}
