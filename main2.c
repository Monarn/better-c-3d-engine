#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "inc/shader/shader.h"
#include "inc/object/object.h"

#include "inc/stb/stb_image.h"

#define WIDTH 800
#define HEIGTH 600

void framebufferSizeCallback(GLFWwindow* window, int width, int heigth)
{	
	glViewport(0,0,width, heigth);
}

int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DEPTH_BITS, 24); 
		
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGTH, "3D renderer", NULL, NULL);
	if (window == NULL)
	{
	  fprintf(stderr, "CANNOT CREATE WINDOW\n");
	  return 1;
	}

	glfwMakeContextCurrent(window);   

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "CANNOT CREATE GLAD CONTEXT\n");
    	return -1;
	}
	
	Shader* shader = createShader("shaders/shader.vs", NULL, "shaders/shader.fs");

	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwSwapInterval(1);

	float color[] = 
	{
    // Face avant
    1.0f, 0.0f, 0.0f,  // Coin inférieur gauche (rouge)
    0.0f, 1.0f, 0.0f,  // Coin inférieur droit (rouge)
    1.0f, 0.0f, 1.0f,  // Coin supérieur droit (rouge)
	};

   float vertices[] = {
    -0.5f, -0.5f, 1.0f,
     0.5f, -0.5f, 2.0f,
     0.0f,  0.5f, 1.0f
	};
	

	GLuint indices[] = {
		0, 1, 2
	};
	 
	Object* obj = createObject(vertices, sizeof(vertices), sizeof(vertices)/sizeof(float), color, sizeof(color), indices, sizeof(indices), shader);

	while (!glfwWindowShouldClose(window))
	{


		glEnable(GL_DEPTH_TEST);

		int width, heigth;

		glfwGetWindowSize(window, &width, &heigth);

		setVec2Uniform(shader, "screenDim", (float)width, (float)heigth);

		glClearColor(0.2f,0.1f,0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		useShader(shader);

		drawObject(obj);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
