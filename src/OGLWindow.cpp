#include "OGLWindow.h"
#include <iostream>

OGLWindow::OGLWindow()
{
	width = 800;
	heigth = 600;
}

OGLWindow::OGLWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	heigth = windowHeight;
}

int OGLWindow::initialise()
{
    /* Initialize the library */
    if (!glfwInit())
        return 1;

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow Forward Compatbility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    mainWindow = glfwCreateWindow(width, heigth, "HELLO WORLD", NULL, NULL);
    if (!mainWindow)
    {
        printf("GLFW Window failed to create!\n");
        glfwTerminate();
        return 1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(mainWindow);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extensions
    glewExperimental = GL_TRUE;

    // Extracts OpenGL current version
    std::cout << glGetString(GL_VERSION) << std::endl;

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        printf("Error: '%s'", glewGetErrorString(error));
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // Get buffers size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
}


OGLWindow::~OGLWindow()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}