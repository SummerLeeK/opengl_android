//
// Created by lhk12 on 2023-03-21.
//

#ifndef OPENGLDEMO_IMAGETEXTURERENDER_H
#define OPENGLDEMO_IMAGETEXTURERENDER_H

#include "BaseRender.h"
#include "jni.h"
#include "ImageData.h"

#define TAG "ImageTextureRender"

class ImageTextureRender : public BaseRender {
public:
    GLuint texture;
    GLint s_TextureMap;
    ImageData *first;
    ImageData *second;

    ImageTextureRender() {
        first = nullptr;
        second = nullptr;
    }

    ~ImageTextureRender() {
        if (first == nullptr)
            delete first;
        if (second == nullptr)
            delete second;
    }

    void initGLProgram();

    void onCreate() override;

    void onDrawFrame(JNIEnv *env, jobject jniHandleObj) override;

    void onSurfaceChanged(JNIEnv *env, jobject jniHandleObj, int width, int height) override;

};


#endif //OPENGLDEMO_IMAGETEXTURERENDER_H
