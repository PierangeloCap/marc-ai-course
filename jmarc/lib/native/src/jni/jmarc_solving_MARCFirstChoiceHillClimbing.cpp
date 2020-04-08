#include "../../header/jni/jmarc_solving_MARCFirstChoiceHillClimbing.h"
#include <Solving/Algorithms/FirstChoiceHillClimbing.h>
#include <string>


JNIEXPORT jlong JNICALL Java_jmarc_solving_MARCFirstChoiceHillClimbing_createNativeObject(JNIEnv* env, jobject thiz, jint maxIdle) {
    auto iter = (int)maxIdle;
    if (iter < 0) throw "Value " + std::to_string(iter) + " illegal for argument \'maxIdleIterations\' (negative value)";    
    
    auto temp = std::make_shared<Solving::Algorithms::FirstChoiceHillClimbing::ZeroTemperature>();

    auto fchc = new std::shared_ptr<Solving::Algorithms::FirstChoiceHillClimbing>(new Solving::Algorithms::FirstChoiceHillClimbing(iter));
    (*fchc)->setTemperature(std::move(temp));

    return (jlong)fchc;
}
