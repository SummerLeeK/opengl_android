//
// Created by lhk12 on 2023-03-22.
//

#ifndef OPENGLDEMO_VAO_VBO_EBO_TRIANGLESAMPLE_H
#define OPENGLDEMO_VAO_VBO_EBO_TRIANGLESAMPLE_H

#include "BaseRender.h"
#include "ShaderCreator.h"
#include "stdlib.h"
class VAO_VBO_EBO_TriangleSample : public BaseRender {

public:

    GLint program;
    GLint vShader;
    GLint fShader;
    GLuint vertexArrayObj;
    GLuint* vertexBufferObj;
    GLint elementBufferObj;

    VAO_VBO_EBO_TriangleSample();

    ~VAO_VBO_EBO_TriangleSample();

    void onCreate() override;

    void onCreateVBOEBO();

    void onCreateVAO();

    void onDrawFrame(JNIEnv *env, jobject jniHandleObj) override;

    void onDraFramePure(JNIEnv *env, jobject jniHandleObj);

    void onDrawFrameWithVBO_EBO(JNIEnv *env, jobject jniHandleObj);

    void onDrawFrameWithVAO_VBO_EBO(JNIEnv *env, jobject jniHandleObj);

    void onSurfaceChanged(JNIEnv *env, jobject jniHandleObj, int width, int height) override;

private:
    void createProgram();
};


#endif //OPENGLDEMO_VAO_VBO_EBO_TRIANGLESAMPLE_H
