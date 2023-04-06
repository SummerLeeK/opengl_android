//
// Created by lhk12 on 2023-03-22.
//

#include "VAO_VBO_EBO_TriangleSample.h"


VAO_VBO_EBO_TriangleSample::VAO_VBO_EBO_TriangleSample() {

    vertexArrayObj = 0;
    vertexBufferObj = nullptr;
    elementBufferObj = 0;

}

VAO_VBO_EBO_TriangleSample::~VAO_VBO_EBO_TriangleSample() {
    vertexArrayObj = 0;
    vertexBufferObj = nullptr;
    elementBufferObj = 0;
}

void VAO_VBO_EBO_TriangleSample::createProgram() {


    program = glCreateProgram();

    char *vShaderStr = "#version 300 es\n"
                       "layout(location = 0) in vec4 a_position;\n"
                       "layout(location = 1) in vec3 inColor;\n"
                       "out vec3 vColor;\n"
                       "void main(){\n"
                       "vColor=inColor;\n"
                       "gl_Position=a_position;\n"
                       "}\n";

    char *fShaderStr = "#version 300 es\n"
                       "precision mediump float;\n"//precision 表示精度
                       "in vec3 vColor;\n"
                       "out vec4 o_fragColor;\n"
                       "void main(){\n"
                       "o_fragColor=vec4(vColor,1.0f);\n"
                       "}\n";


    createShader(&vShader, GL_VERTEX_SHADER, vShaderStr);

    glAttachShader(program, vShader);

    createShader(&fShader, GL_FRAGMENT_SHADER, fShaderStr);

    glAttachShader(program, fShader);
    glLinkProgram(program);

    onCreateVAO();
    onCreateVBOEBO();

    glBindVertexArray(GL_NONE);
}

void VAO_VBO_EBO_TriangleSample::onCreateVBOEBO() {

//    glGenBuffers(2,vertexBufferObj);

    // 4 vertices, with(x,y,z) ,(r, g, b, a) per-vertex
    GLfloat vertices[] =
            {
                    -0.5f, 0.5f, 0.0f,       // v0
                    1.0f, 0.0f, 0.0f,        // c0
                    -0.5f, -0.5f, 0.0f,       // v1
                    0.0f, 1.0f, 0.0f,        // c1
                    0.5f, -0.5f, 0.0f,        // v2
                    0.0f, 0.0f, 1.0f,        // c2
                    0.5f, 0.5f, 0.0f,        // v3
                    0.5f, 1.0f, 1.0f,        // c3
            };
// Index buffer data
    GLushort indices[6] = {0, 1, 2, 0, 2, 3};
    vertexBufferObj = (GLuint *) malloc(2 * sizeof(GLuint));
    glGenBuffers(2, vertexBufferObj);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObj[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), NULL);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                          (const void *) (3 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexBufferObj[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

}

void VAO_VBO_EBO_TriangleSample::onCreateVAO() {
    glGenVertexArrays(1, &vertexArrayObj);
    glBindVertexArray(vertexArrayObj);
}

void VAO_VBO_EBO_TriangleSample::onCreate() {
    createProgram();
}

void VAO_VBO_EBO_TriangleSample::onDraFramePure(JNIEnv *env, jobject jniHandleObj) {
    // 4 vertices, with(x,y,z) ,(r, g, b, a) per-vertex
    GLfloat vertices[] =
            {
                    -0.5f, 0.5f, 0.0f,       // v0
                    1.0f, 0.0f, 0.0f,        // c0
                    -0.5f, -0.5f, 0.0f,       // v1
                    0.0f, 1.0f, 0.0f,        // c1
                    0.5f, -0.5f, 0.0f,        // v2
                    0.0f, 0.0f, 1.0f,        // c2
                    0.5f, 0.5f, 0.0f,        // v3
                    0.5f, 1.0f, 1.0f,        // c3
            };
// Index buffer data
    GLushort indices[6] = {0, 1, 2, 0, 2, 3};

    glUseProgram(program);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), vertices);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), vertices + 3);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void VAO_VBO_EBO_TriangleSample::onDrawFrameWithVBO_EBO(JNIEnv *env, jobject jniHandleObj) {
    glUseProgram(program);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

void VAO_VBO_EBO_TriangleSample::onDrawFrameWithVAO_VBO_EBO(JNIEnv *env, jobject jniHandleObj) {
    glUseProgram(program);
    glBindVertexArray(vertexArrayObj);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);
}

void VAO_VBO_EBO_TriangleSample::onDrawFrame(JNIEnv *env, jobject jniHandleObj) {
    onDrawFrameWithVAO_VBO_EBO(env, jniHandleObj);
}

void VAO_VBO_EBO_TriangleSample::onSurfaceChanged(JNIEnv *env, jobject jniHandleObj, int width,
                                                  int height) {

}
