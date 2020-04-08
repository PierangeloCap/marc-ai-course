#include "../../header/jni/jmarc_modeling_MARCProblem.h"
#include "../../header/backend/JAction.h"
#include "../../header/backend/JProblem.h"
#include "../../header/backend/JState.h"
#include "../../header/backend/JDimensionType.h"
#include "../../header/jni/Handle.h"
//#include <unordered_set>


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCProblem_createNativeObject__Ljava_lang_Object_2(JNIEnv* env, jobject thiz, jobject dim) {
    Modeling::direction dir = Modeling::direction::MIN;
	JMARC::JDimensionType jDim(dim);

	auto prob = new std::shared_ptr<JMARC::JProblem>(new JMARC::JProblem(jDim, env, &thiz, dir));
	return (jlong)prob;  
}


JNIEXPORT jlong JNICALL Java_jmarc_modeling_MARCProblem_createNativeObject__Ljava_lang_Object_2Ljava_lang_String_2(JNIEnv* env, jobject thiz, jobject dim, jstring dir) {
	const char* cDir = env->GetStringUTFChars(dir, 0);
    std::string strDir(cDir);
	env->ReleaseStringUTFChars(dir, cDir);
	Modeling::direction natDir;
	if (strDir == "MIN") natDir = Modeling::direction::MIN;
	else if (strDir == "MAX") natDir = Modeling::direction::MAX;
	else throw "Direction type " + strDir + " is undefined";

	JMARC::JDimensionType jDim(dim);
	auto prob = new std::shared_ptr<JMARC::JProblem>(new JMARC::JProblem(jDim, env, &thiz, natDir));
	return (jlong)prob;
}


/*JNIEXPORT jobject JNICALL Java_jmarc_modeling_MARCProblem_getPossibleActions(JNIEnv* env, jobject thiz, jobject s) {
    auto prob = HandleManager<std::shared_ptr<JMARC::JProblem>>::getHandle(env, thiz);
	auto state = HandleManager<std::shared_ptr<JMARC::JState>>::getHandle(env, s);
	std::unordered_set<std::shared_ptr<Modeling::Action>> possible = (*prob)->getPossibleActions(*state);

	jclass hashSet = env->FindClass("java/util/HashSet");
	jmethodID hsCtor = env->GetMethodID(hashSet, "<init>", "()V");
	jmethodID add = env->GetMethodID(hashSet, "add", "(Ljmarc/modeling/MARCAction;)Z");
	jobject result = env->NewObject(hashSet, hsCtor);

	for (auto itr = possible.begin(); itr != possible.end(); itr++) {
		auto a = *(itr);
		auto curr = std::dynamic_pointer_cast<JMARC::JAction>(a);
		jobject jcurr = *(curr->getRef());
		env->CallBooleanMethod(result, add, jcurr);
		env->DeleteLocalRef(jcurr);
	}
	env->DeleteLocalRef(hashSet);
	return result;
}*/

