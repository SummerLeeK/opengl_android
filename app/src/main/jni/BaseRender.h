//
// Created by lhk12 on 2023-03-20.
//

#ifndef OPENGLDEMO_BASERENDER_H
#define OPENGLDEMO_BASERENDER_H
#include "jni.h"
#include "android/log.h"
#include "GLES3/gl3.h"
#define TAG "BaseRender"
#define IMAGE_FORMAT_RGBA_8888 0x2A

class BaseRender {
public:
    GLint vShader;
    GLint fShader;
    GLint program;
    int width;
    int height;

    virtual void onCreate()=0;
    virtual void onDrawFrame(JNIEnv *env,jobject jniHandleObj)=0;
    virtual void onSurfaceChanged(JNIEnv *env,jobject jniHandleObj,int width,int height)=0;
    static jfieldID getField(JNIEnv *env, jobject jniHandleObj, const char *fieldName, const char *sig);
    static BaseRender *GetRender(JNIEnv *env,jobject jniHandleObj);
    static void saveRender(JNIEnv *env,jobject jniHandleObj,BaseRender *cameraXRender);
    static void freeRender(JNIEnv *env,jobject jniHandleObj);

private:
    static jfieldID s_ContextHandle;
};


#endif //OPENGLDEMO_BASERENDER_H
