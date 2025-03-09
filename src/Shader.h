#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

	std::string Readfile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();

	void UseShader();
	void ClearShader();

	~Shader();

private:
	GLuint shaderID, uniformProjection, uniformModel, uniformView;

	void CompileShader(const char* VertexCode, const char* FragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

