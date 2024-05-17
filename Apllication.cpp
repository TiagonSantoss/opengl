#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Iostream>
#include <stdio.h>

/*static int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)_malloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
};*/


/*static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
};*/

// window size
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

// vs
static const char* vS = "                                         \n\
#version 330                                                      \n\
                                                                  \n\
layout (location = 0) in vec3 pos;                                \n\
                                                                  \n\
void main()                                                       \n\
{                                                                 \n\
   gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);      \n\
}";


// fs
static const char* fS = "                                         \n\
#version 330                                                      \n\
                                                                  \n\
out vec4 colour;                                                  \n\
                                                                  \n\
void main()                                                       \n\
{                                                                 \n\
   colour = vec4(1.0, 0.0, 1.0, 0.5);                             \n\
}";


void CreateTriangle()
{
    GLfloat vertices[]{
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f
    };

    glCreateVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

       glGenBuffers(1, &VBO);
       glBindBuffer(GL_ARRAY_BUFFER, VBO);
          glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
          
          glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
          glEnableVertexAttribArray(0);
       
       glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLenght[1];
    codeLenght[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLenght);
    glCompileShader(theShader);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) 
    {
        glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error compiling %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}



void ShaderCompiler()
{
    shader = glCreateProgram();

    if (!shader) 
    {
        printf("Error creating ShaderProgram!!\n");
        return;
    }

    addShader(shader, vS, GL_VERTEX_SHADER);
    addShader(shader, fS, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }
}



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "HELLO WORLD", NULL, NULL);
    if (!window)
    {
        printf("GLFW Window failed to create!\n");
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // allow modern things
    glewExperimental = GL_TRUE;

    // Extracts OpenGL current version
    std::cout <<glGetString(GL_VERSION) << std::endl;

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        printf("Error: '%s'", glewGetErrorString(error));
    }
    
    // Get buffers size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    // Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateTriangle();
    ShaderCompiler();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // poll + events
        glfwPollEvents();
        
        /* Render here */
        glClearColor(0.0f, 0.2f, 1.0f, 0.2f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);


        /* Swap front and back buffers */
         glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}