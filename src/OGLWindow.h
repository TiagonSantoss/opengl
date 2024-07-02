#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class OGLWindow
{
public:
	OGLWindow();

	OGLWindow(GLint windowWidth, GLint windowHeight);

	int initialise();

	GLfloat GetBufferWidth()
	{
		return bufferWidth;
	}
	GLfloat GetBufferHeight()
	{
		return bufferHeight;
	}

	bool GetShouldClose()
	{
		return glfwWindowShouldClose(mainWindow);
	}

	void swapBuffers()
	{
		glfwSwapBuffers(mainWindow);
	}

	~OGLWindow();
private:
	GLFWwindow* mainWindow;

	GLint width, heigth;
	GLint bufferWidth, bufferHeight;

};

