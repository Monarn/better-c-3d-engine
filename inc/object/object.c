#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>
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

Object* createObject(float vertices[], int sizeVert, int numVert, float color[], int sizeCol, GLuint indices[], int sizeInd, Shader* shader)
{
	Object* object = (Object*)malloc(sizeof(Object));

	object->x = 0; object->y = 0; object->z = 0; 

	object->numVert = numVert;

	object->shader = shader;

	glGenVertexArrays(1, &object->VAO);

	glGenBuffers(1, &object->VBOPos);
	glGenBuffers(1, &object->VBOColor);
	glGenBuffers(1, &object->VBOTexCoords);
	glGenBuffers(1, &object->EBO);

	glBindVertexArray(object->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, object->VBOPos);
	glBufferData(GL_ARRAY_BUFFER, sizeVert, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInd, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, object->VBOColor);
	glBufferData(GL_ARRAY_BUFFER, sizeCol, color, GL_STATIC_DRAW);

	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	return object;
}

void drawObject(Object* object)
{
	glBindVertexArray(object->VAO);
	glDrawArrays(GL_TRIANGLES, 0, object->numVert);
}

void translateObject(Object* object, float t1, float t2, float t3)
{
	object->x += t1; object->y += t2; object->z += t3;
	setVec3Uniform(object->shader, "oPos", object->x, object->y, object->z);
}

