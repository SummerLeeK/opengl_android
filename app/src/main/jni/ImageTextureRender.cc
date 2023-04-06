//
// Created by lhk12 on 2023-03-21.
//

#include "ImageTextureRender.h"

void ImageTextureRender::initGLProgram() {
    program = glCreateProgram();

    vShader = glCreateShader(GL_VERTEX_SHADER);
    char *vShaderStr =
            "#version 300 es                            \n"
            "layout(location = 0) in vec4 a_position;   \n"
            "layout(location = 1) in vec2 a_texCoord;   \n"
            "out vec2 v_texCoord;                       \n"
            "void main()                                \n"
            "{                                          \n"
            "   gl_Position = a_position;               \n"
            "   v_texCoord = a_texCoord;                \n"
            "}                                          \n";

    glShaderSource(vShader, 1, &vShaderStr, NULL);

    glCompileShader(vShader);

    glAttachShader(program, vShader);


    char *fShaderStr =
            "#version 300 es                                     \n"
            "precision mediump float;                            \n"
            "in vec2 v_texCoord;                                 \n"
            "layout(location = 0) out vec4 outColor;             \n"
            "uniform sampler2D s_TextureMap;                     \n"
            "void main()                                         \n"
            "{                                                   \n"
            "  outColor = texture(s_TextureMap, v_texCoord);     \n"
            "}                                                   \n";


    fShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fShader, 1, &fShaderStr, NULL);

    glCompileShader(fShader);

    glAttachShader(program, fShader);

    glLinkProgram(program);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);


    s_TextureMap = glGetUniformLocation(program, "s_TextureMap");

}

void ImageTextureRender::onCreate() {
    initGLProgram();
}

void
ImageTextureRender::onSurfaceChanged(JNIEnv *env, jobject jniHandleObj, int width, int height) {

}

void ImageTextureRender::onDrawFrame(JNIEnv *env, jobject jniHandleObj) {

    if (second == nullptr)
        return;
    __android_log_print(ANDROID_LOG_INFO, TAG, "%s", "native_UpdateFrame");

    // 展示在opengl的纹理坐标 逆时针 且已经旋转90度后的坐标系
    GLfloat verticesCoords[] = {
            1.0f, 1.0f, 0.0f,
            -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
    };


    GLfloat textureCoords[] = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
    };

    GLushort indices[] = {
            0, 1, 2, 0, 2, 3
    };

    //生成纹理
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, second->width, second->height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 second->data);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);


    glUseProgram(program);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), verticesCoords);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), textureCoords);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(s_TextureMap, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

}