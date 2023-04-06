//
// Created by lhk12 on 2023-03-17.
//

#ifndef OPENGLDEMO_TRIANGLERENDER_H
#define OPENGLDEMO_TRIANGLERENDER_H
#include "android/log.h"
#include "jni.h"
#include "BaseRender.h"
#include <GLES3/gl3.h>
#define TAG "TriangleRender"
class TriangleRender: public BaseRender {

public:
    int drawcount = 0;

    TriangleRender(){
        __android_log_print(ANDROID_LOG_ERROR,TAG,"%s","onCreate");
    }

    ~TriangleRender(){
        __android_log_print(ANDROID_LOG_ERROR,TAG,"%s","onDestory");
    }

    virtual void createProgram();

    virtual void onCreate();
    virtual void onDrawFrame(JNIEnv *env,jobject jniHandleObj);
    virtual void onSurfaceChanged(JNIEnv *env,jobject jniHandleObj,int width,int height);

};


#endif //OPENGLDEMO_TRIANGLERENDER_H
