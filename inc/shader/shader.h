#ifndef SHADER_H_
#define SHADER_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define str const char*

typedef struct
{
    unsigned int vertShader;
    unsigned int geomShader;
    unsigned int fragShader;
    unsigned int shaderProgram;
    bool active;
}Shader;

str loadShader(str name);

Shader* createShader(str vertShader, str geomShader, str fragShader);

void useShader(Shader* shader);

void setFloatUniform(Shader* shader, const char* name, float value);

void setIntUniform(Shader* shader, const char* name, int value);

void setVec2Uniform(Shader* shader, const char* name, float v1, float v2);

void setVec3Uniform(Shader* shader, const char* name, float v1, float v2, float v3);


#endif
