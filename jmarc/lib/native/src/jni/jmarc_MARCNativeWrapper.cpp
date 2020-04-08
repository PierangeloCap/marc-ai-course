#include "../../header/jni/jmarc_MARCNativeWrapper.h"
#include "../../header/jni/Handle.h"
#include "../../header/backend/JNIWrap.h"
#include <memory>
#include <iostream>


JNIEXPORT void JNICALL Java_jmarc_MARCNativeWrapper_cleanUp(JNIEnv *, jclass clazz, jlong ptr) {
    auto ref = reinterpret_cast<std::shared_ptr<JMARC::JNIWrap> *>(ptr);
    //std::cout << ref->use_count() << std::endl;
    delete ref;
}