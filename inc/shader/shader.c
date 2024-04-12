#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#define str const char*

typedef struct
{
	GLuint vertShader;
	GLuint geomShader;
	GLuint fragShader;
	GLuint shaderProgram;
	bool active;
}Shader;



str loadShader(str name)
{
    FILE* file;
    char* content;
    long len;

    file = fopen(name, "r");
    if (file == NULL)
    {
        fprintf(stderr, "COULD NOT FIND FILE %s\n", name);
        return NULL;
    }

    fseek(file,0,SEEK_END);
    len = ftell(file);
    fseek(file,0,SEEK_SET);

    content = (char*)malloc(len+1);

    if (content == NULL)
    {
        fprintf(stderr, "COULD NOT LOAD CONTENT OF FILE %s\n", name);
        return NULL;
    }
    fread((void*)content,1,len, file);

	content[len] = '\0';

    fclose(file);
    return (str)content;
}

Shader* createShader(str vertShader, str geomShader, str fragShader)
{
	Shader* shader = malloc(sizeof(Shader));

	if (shader == NULL)
	{
		fprintf(stderr, "SHADER ALLOCATION FAILED\n");
		exit(-1);
	}

	shader->shaderProgram = glCreateProgram();
	
	shader->active = true;

	if (vertShader != NULL)
	{
		int success;	
		char infoLog[512];

		str content = loadShader(vertShader);
		shader->vertShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(shader->vertShader, 1, &content, NULL);
		glCompileShader(shader->vertShader);
		glGetShaderiv(shader->vertShader, GL_COMPILE_STATUS, &success);
		glGetShaderInfoLog(shader->vertShader, 512, NULL, infoLog);
		if (!success)
		{
			fprintf(stderr, "VERTEX SHADER FAILED TO COMPILE : %s\n", infoLog);		
		}
		
		printf("VERTEX SHADER LOADED SUCCESSFULLY\n");

		glAttachShader(shader->shaderProgram, shader->vertShader);
	}

	if (geomShader != NULL)
	{
		int success;	
		char infoLog[512];

		str content = loadShader(geomShader);
		shader->geomShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(shader->geomShader, 1, &content, NULL);
		glCompileShader(shader->geomShader);
		glGetShaderiv(shader->geomShader, GL_COMPILE_STATUS, &success);
		glGetShaderInfoLog(shader->geomShader, 512, NULL, infoLog);
		if (!success)
		{
			fprintf(stderr, "GEOMETRY SHADER FAILED TO COMPILE : %s\n", infoLog);		
		}

		printf("GEOMETRY SHADER LOADED SUCCESSFULLY\n");

		glAttachShader(shader->shaderProgram, shader->geomShader);

	}

	if (fragShader != NULL)
	{
		int success;	
		char infoLog[512];

		str content = loadShader(fragShader);
		shader->fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(shader->fragShader, 1, &content, NULL);
		glCompileShader(shader->fragShader);
		glGetShaderiv(shader->fragShader, GL_COMPILE_STATUS, &success);
		glGetShaderInfoLog(shader->fragShader, 512, NULL, infoLog);
		if (!success)
		{
			fprintf(stderr, "FRAGMENT SHADER FAILED TO COMPILE : %s\n", infoLog);		 }

		printf("FRAGMENT SHADER LOADED SUCCESSFULLY\n");
		glAttachShader(shader->shaderProgram, shader->fragShader);

	}


	return shader;

}

void useShader(Shader* shader)
{
	if (shader->active)
	{
		glLinkProgram(shader->shaderProgram);
		glUseProgram(shader->shaderProgram);
	} 
}

void setFloatUniform(Shader* shader, const char* name, float value)
{
	GLuint uniLoc = glGetUniformLocation(shader->shaderProgram, name);
	glUniform1f(uniLoc, value);
}

void setIntUniform(Shader* shader, const char* name, int value)
{
	GLuint uniLoc = glGetUniformLocation(shader->shaderProgram, name);
	glUniform1i(uniLoc, value);
}

void setVec2Uniform(Shader* shader, const char* name, float v1, float v2)
{
	GLuint uniLoc = glGetUniformLocation(shader->shaderProgram, name);
	glUniform2f(uniLoc, v1, v2);
}

void setVec3Uniform(Shader* shader, const char* name, float v1, float v2, float v3)
{
	GLuint uniLoc = glGetUniformLocation(shader->shaderProgram, name);

	glUniform3f(uniLoc, v1, v2, v3);
}
