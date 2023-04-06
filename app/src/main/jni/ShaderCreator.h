//
// Created by lhk12 on 2023-03-22.
//

#ifndef OPENGLDEMO_SHADERCREATOR_H
#define OPENGLDEMO_SHADERCREATOR_H
#define TAG "SHADERCREATOR"
#include <GLES3/gl3.h>
#include "Log.h"

int createShader(GLint *shader,GLenum shaderType,const char *shaderStr);


#endif //OPENGLDEMO_SHADERCREATOR_H
