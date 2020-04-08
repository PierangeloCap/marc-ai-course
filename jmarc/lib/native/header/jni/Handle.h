#ifndef HANDLE_H
#define HANDLE_H

#include <jni.h>


template <typename T>
class HandleManager {

public:
	static jfieldID getHandleField(JNIEnv *env, jobject obj);

	static T* getHandle(JNIEnv *env, jobject obj);

	static void setHandle(JNIEnv *env, jobject obj, T *t);

};


template <typename T>
jfieldID HandleManager<T>::getHandleField(JNIEnv *env, jobject obj) {
    jclass c = env->GetObjectClass(obj);
    // J is the type signature for long:
    auto res = env->GetFieldID(c, "handle", "J");
    env->DeleteLocalRef(c);
    return res;
}

template <typename T>
T* HandleManager<T>::getHandle(JNIEnv *env, jobject obj) {
    jlong handle = env->GetLongField(obj, HandleManager<T>::getHandleField(env, obj));
    return reinterpret_cast<T *>(handle);
}

template <typename T>
void HandleManager<T>::setHandle(JNIEnv *env, jobject obj, T *t) {
    jlong handle = reinterpret_cast<jlong>(t);
    env->SetLongField(obj, HandleManager<T>::getHandleField(env, obj), handle);
}


#endif // HANDLE_H