#include "../../header/jni/jmarc_solving_MARCSolverMonitor.h"
#include <Solving/SolverMonitor.h>
#include <memory>

JNIEXPORT jlong JNICALL Java_jmarc_solving_MARCSolverMonitor_createNativeObject(JNIEnv* env, jobject thiz, jstring jname) {
    const char* cName = env->GetStringUTFChars(jname, 0);
    std::string name(cName);

    auto mon = new std::shared_ptr<Solving::SolverMonitor>(new Solving::SolverMonitor(name));
    env->ReleaseStringUTFChars(jname, cName);
    return (jlong)mon;
}