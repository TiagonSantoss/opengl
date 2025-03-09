#include "OGLWindow.h"
#include <iostream>

OGLWindow::OGLWindow()
{
	width = 800;
	heigth = 600;

    for (size_t i = 0; i < 1020; i++) 
    {
        keys[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
}

OGLWindow::OGLWindow(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	heigth = windowHeight;

    for (size_t i = 0; i < 1020; i++) {
        keys[i] = 0;
    }

    xChange = 0.0f;
    yChange = 0.0f;
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

    // Handle keyboard + mouse inputs
    createCallbacks();
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(mainWindow, this);
}

void OGLWindow::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat OGLWindow::getXChange()
{
    GLfloat theChange = xChange;
    xChange = 0.0f;
    return theChange;
}

GLfloat OGLWindow::getYChange()
{
    GLfloat theChange = yChange;
    yChange = 0.0f;
    return theChange;
}

void OGLWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    OGLWindow* theWindow = static_cast<OGLWindow*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            theWindow->keys[key] = true;
        }

        if (action == GLFW_RELEASE) 
        {
            theWindow->keys[key] = false;
        }
    }
}

void OGLWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    OGLWindow* theWindow = static_cast<OGLWindow*>(glfwGetWindowUserPointer(window));

    if (theWindow->mouseFirstMoved)
    {
        theWindow->lastX = xPos;
        theWindow->lastY = yPos;
        theWindow->mouseFirstMoved = false;
    }

    theWindow->xChange = xPos - theWindow->lastX;
    theWindow->yChange = theWindow->lastY - yPos;

    theWindow->lastX = xPos;
    theWindow->lastY = yPos;
}

OGLWindow::~OGLWindow()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}
