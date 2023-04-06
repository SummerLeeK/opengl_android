//
// Created by lhk12 on 2023-03-20.
//

#include "BaseRender.h"

jfieldID BaseRender::s_ContextHandle = nullptr;

jfieldID
BaseRender::getField(JNIEnv *env, jobject jniHandleObj, const char *fieldName, const char *sig) {
    __android_log_print(ANDROID_LOG_INFO, TAG, "%s\t%s\t%s \t%p", "GetObjectClass",fieldName,sig,&env);


    jclass cls = env->GetObjectClass(jniHandleObj);

    if (cls == nullptr) {
        __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "GetObjectClass is NULL");
        return nullptr;
    }
    return env->GetFieldID(cls, fieldName, sig);
}

BaseRender *BaseRender::GetRender(JNIEnv *env, jobject jniHandleObj) {

    if (s_ContextHandle == nullptr) {
        s_ContextHandle = getField(env, jniHandleObj, "mNativeContextHandle", "J");
    }

    return reinterpret_cast<BaseRender *>(env->GetLongField(jniHandleObj, s_ContextHandle));
}

void
BaseRender::saveRender(JNIEnv *env, jobject jniHandleObj, BaseRender *cameraXRender) {
    if (s_ContextHandle == nullptr) {
        s_ContextHandle = getField(env, jniHandleObj, "mNativeContextHandle", "J");
    }
    env->SetLongField(jniHandleObj, s_ContextHandle, reinterpret_cast<jlong>(cameraXRender));

}

void BaseRender::freeRender(JNIEnv *env, jobject jniHandleObj) {
    BaseRender *cc = GetRender(env, jniHandleObj);

    if (cc != NULL) {
        delete cc;
    }
    env->SetLongField(jniHandleObj, s_ContextHandle, 0L);
}
