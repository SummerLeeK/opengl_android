//
// Created by lhk12 on 2023-03-17.
//

#include "BaseRender.h"
#include <jni.h>
#include <GLES3/gl3.h>
#include <time.h>
#include "math.h"
#include "libyuv.h"
#include "android/log.h"
#include "iostream"
#include "ImageTextureRender.h"
#include "libyuv/rotate.h"
#include "VAO_VBO_EBO_TriangleSample.h"
#include "TriangleRender.h"

#define TAG "JNIHANDLE"
using namespace std;
using namespace std::chrono;
int width, height;

void getCurrentMillTimeStamp() {

    struct timeval tv;
    gettimeofday(&tv, NULL);
    __android_log_print(ANDROID_LOG_INFO, TAG, "Current time: %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_aisaka_opengldemo_MyRender_native_1OnCreate(JNIEnv
                                                    *env,
                                                    jobject thiz
) {

    BaseRender *cameraXRender = new VAO_VBO_EBO_TriangleSample();
    BaseRender::saveRender(env, thiz, cameraXRender);

    __android_log_print(ANDROID_LOG_INFO, TAG, "%s  %p", "native_OnCreate", cameraXRender);

    cameraXRender->onCreate();

}

extern "C"
JNIEXPORT void JNICALL
Java_cn_aisaka_opengldemo_MyRender_native_1OnDrawFrame(JNIEnv *env, jobject thiz
) {
    BaseRender *cameraXRender = BaseRender::GetRender(env, thiz);
    __android_log_print(ANDROID_LOG_INFO, TAG, "%s  %p", "native_OnDrawFrame", cameraXRender);
    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    cameraXRender->onDrawFrame(env, thiz);
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_aisaka_opengldemo_MyRender_native_1onSurfaceChanged(JNIEnv
                                                            *env,
                                                            jobject thiz, jint
                                                            jwidth,
                                                            jint jheight
) {
    width = jwidth;
    height = jheight;
    __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "native_onSurfaceChanged");

}

extern "C"
JNIEXPORT void JNICALL
Java_cn_aisaka_opengldemo_MyRender_native_1onSurfaceDestroyed(JNIEnv *env, jobject thiz) {
    BaseRender::freeRender(env, thiz);
    __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "onSurfaceDestroyed");
}
extern "C"
JNIEXPORT void JNICALL
Java_cn_aisaka_opengldemo_MyRender_native_1UpdateFrame(JNIEnv *env, jobject thiz, jbyteArray data,
                                                       jint width, jint height, jint format) {
//    __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "native_UpdateFrame");

    BaseRender *render = BaseRender::GetRender(env, thiz);

    ImageTextureRender *imageTextureRender = dynamic_cast<ImageTextureRender *>(render);
    if (imageTextureRender != nullptr) {
        if (format == IMAGE_FORMAT_RGBA_8888) {
            int length = width * height * 4;
            if (imageTextureRender->first != nullptr) {
                imageTextureRender->second = imageTextureRender->first;
                imageTextureRender->first = nullptr;
            }
            uint8_t *byte = reinterpret_cast<uint8_t *>(env->GetByteArrayElements(data, NULL));
            imageTextureRender->first = new ImageData(width, height, format, byte, length);
            env->ReleaseByteArrayElements(data, reinterpret_cast<jbyte *>(byte), NULL);
        }
    }

}