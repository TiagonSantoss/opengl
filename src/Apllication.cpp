#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Iostream>
#include <stdio.h>
#include <cmath>
#include <bitset>
#include <vector>

#include "OGLWindow.h"
#include "Mesh.h"
#include "Shader.h"

const float toRadians = 3.14159265f / 180.0f;

OGLWindow mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

// Vertex Shader
static const char* vS = "src/Shaders/shader.vert";

// Fragment Shader
static const char* fS = "src/Shaders/shader.frag";

void CreateObjects()
{
    unsigned int indices[]{
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };
    
    GLfloat vertices[]{
        -1.0f, -1.0f, 0.0f,
         0.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj2);
}

void CreateShaders()
{
    Shader* Shader1 = new Shader();
    Shader1->CreateFromFiles(vS, fS);
    shaderList.push_back(*Shader1);
}

int main(void)
{
    mainWindow = OGLWindow(800, 600);
    mainWindow.initialise();

    CreateObjects();
    CreateShaders();

    GLuint uniformProjection = 0, uniformModel = 0;
    glm::mat4 projection = glm::perspective(45.0f, mainWindow.GetBufferWidth() / mainWindow.GetBufferHeight(), 0.1f, 100.0f);

    /* Loop until the user closes the window */
    while (!mainWindow.GetShouldClose())
    {
        // poll + events
        glfwPollEvents();

        // render here
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0].UseShader();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformModel = shaderList[0].GetModelLocation();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        meshList[1]->RenderMesh();

        glUseProgram(0);

        mainWindow.swapBuffers();
    }
    glfwTerminate();
    return 0;
}