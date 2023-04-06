//
// Created by lhk12 on 2023-03-22.
//

#include <cstdlib>
#include "ShaderCreator.h"

int createShader(GLint *shader, GLenum shaderType, const char *shaderStr) {
    int result = 0;
    *shader = glCreateShader(shaderType);

    if (!*shader) {
        LOGE(TAG, "glCreateShader failure");
        return -1;
    }

    glShaderSource(*shader, 1, &shaderStr, NULL);

    glCompileShader(*shader);


    GLint compiled;

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);

    if (!compiled) {
        //编译shader失败
        GLint lenInfoLog;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &lenInfoLog);

        if (lenInfoLog) {
            char *buf = static_cast<char *>(malloc(lenInfoLog));

            if (buf){
                glGetShaderInfoLog(*shader,lenInfoLog,NULL,buf);
                LOGE(TAG,"reason %s",buf);
                free(buf);
            }
            glDeleteShader(*shader);
            *shader=0;
        }
        result=-1;
    }

    return result;
}