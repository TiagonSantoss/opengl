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

	bool* getKeys()
	{
		return keys;
	}

	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers()
	{
		glfwSwapBuffers(mainWindow);
	}

	~OGLWindow();
private:
	GLFWwindow* mainWindow = 0;

	GLint width = 0, heigth = 0;
	GLint bufferWidth = 0, bufferHeight = 0;

	bool keys[1020];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};