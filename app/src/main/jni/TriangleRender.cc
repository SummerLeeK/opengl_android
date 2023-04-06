//
// Created by lhk12 on 2023-03-17.
//

#include "TriangleRender.h"
#include "math.h"

void TriangleRender::onDrawFrame(JNIEnv *env, jobject jniHandleObj) {
    float sinx = sinf(drawcount / 90.0);
    GLfloat vVertices[] = {
            0.0f, 0.5f, 0.0f,
            -0.5f * (sinx), -0.5f, 0.0f,
            0.5f * (sinx), -0.5f, 0.0f,
    };


    glUseProgram(program);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);

    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    drawcount++;
}

void TriangleRender::onSurfaceChanged(JNIEnv *env, jobject jniHandleObj, int width, int height) {

}

void TriangleRender::onCreate() {

    createProgram();
}

void TriangleRender::createProgram() {

    program=glCreateProgram();

    vShader= glCreateShader(GL_VERTEX_SHADER);

    char* vShaderStr =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "}                                        \n";

    char* fShaderStr =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 ( 1.0, 0.0, 0.0, 1.0 );  \n"
            "}                                            \n";
    glShaderSource(vShader,1,&vShaderStr,NULL);
    glCompileShader(vShader);


    fShader= glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader,1,&fShaderStr,NULL);
    glCompileShader(fShader);

    glAttachShader(program,vShader);

    glAttachShader(program,fShader);

    glLinkProgram(program);

}