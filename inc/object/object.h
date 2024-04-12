#ifndef OBJECT_H_
#define OBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include "../shader/shader.h"

typedef struct
{
    float x,y,z;
    GLuint VAO;
    GLuint EBO;
    GLuint VBOPos;
    GLuint VBOColor;
    GLuint VBOTexCoords;
    GLsizei numVert;
    GLsizei numTex;
    Shader* shader;
}Object;


Object* createObject(float vertices[], int sizeVert, int numVert, float color[], int sizeCol, GLuint indices[], int sizeInd, Shader* shader);

void drawObject(Object* object);

void translateObject(Object* obj, float t1, float t2, float t3);


#endif
