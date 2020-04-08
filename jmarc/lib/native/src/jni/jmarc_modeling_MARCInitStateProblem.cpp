#include "../../header/jni/jmarc_modeling_MARCInitStateProblem.h"
#include "../../header/backend/JInitStateProblem.h"
#include "../../header/backend/JDimensionType.h"
#include "../../header/backend/JState.h"
#include "../../header/jni/Handle.h"

#include <iostream>


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCInitStateProblem_createNativeObject__Ljava_lang_Object_2(JNIEnv* env, jobject thiz, jobject dim) {	
	Modeling::direction dir = Modeling::direction::MIN;
	JMARC::JDimensionType jDim(dim);

	auto prob = new std::shared_ptr<JMARC::JInitStateProblem>(new JMARC::JInitStateProblem(jDim, env, &thiz, dir));
	return (jlong)prob;
}


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCInitStateProblem_createNativeObject__Ljava_lang_Object_2Ljava_lang_String_2(JNIEnv* env, jobject thiz, jobject dim, jstring dir) {
	const char* cDir = env->GetStringUTFChars(dir, 0);
    std::string strDir(cDir);
	env->ReleaseStringUTFChars(dir, cDir);
	Modeling::direction natDir;
	if (strDir == "MIN") natDir = Modeling::direction::MIN;
	else if (strDir == "MAX") natDir = Modeling::direction::MAX;
	else throw "Direction type " + strDir + " is undefined";

	JMARC::JDimensionType jDim(dim);
	auto prob = new std::shared_ptr<JMARC::JInitStateProblem>(new JMARC::JInitStateProblem(jDim, env, &thiz, natDir));
	return (jlong)prob;
}


JNIEXPORT jobject JNICALL Java_jmarc_modeling_MARCInitStateProblem_getInitialState(JNIEnv* env, jobject thiz) {
	auto prob = HandleManager<std::shared_ptr<JMARC::JInitStateProblem>>::getHandle(env, thiz);
	std::shared_ptr<Modeling::State> s = (*prob)->getInitialState().lock();
	auto state = std::dynamic_pointer_cast<JMARC::JState>(s);
	return *(state->getRef());
}


JNIEXPORT void JNICALL Java_jmarc_modeling_MARCInitStateProblem_setInitialState(JNIEnv* env, jobject thiz, jobject s) {
	auto prob = HandleManager<std::shared_ptr<JMARC::JInitStateProblem>>::getHandle(env, thiz);
	auto state = HandleManager<std::shared_ptr<JMARC::JState>>::getHandle(env, s);
	jclass initStateProblem = env->GetObjectClass(thiz);
    jmethodID addDep = env->GetMethodID(initStateProblem, "addDependency", "(Ljmarc/MARCNativeWrapper;)V");
    env->CallVoidMethod(thiz, addDep, s);
	(*prob)->setInitialState(*state);
	env->DeleteLocalRef(initStateProblem);
}

