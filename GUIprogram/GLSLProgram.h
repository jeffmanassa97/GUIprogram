#pragma once

#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();
	
	//read the GLSL from their files. Const bc/ they are never going to change. Make them by reference to use the origanl copy in parameters
	void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath); //read the GLSL from their files

	void linkShaders();

	void addAttribute(const std::string& attributeName); //for vec variables in the files

	GLint getUniformLocation(const std::string uniformName); //to find the location/ID of the uniform variable for time

	void use();
	void unuse(); //unbind it
private:
	
	int _numAttributes; //an attribute is a color, texture, vertexPosition, etc.

	void compileShader(const std::string& filePath, GLuint id); //quick function to compile both shaders
	
	//just like the vertex buffer object, you need an ID to hold on to the shader program & individual programs
	GLuint _programID; // the idea that refers to the entire program finished product

	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
	//every object in OpenGL needs a GLuint ID: VBO, textures, programs, etc.
};

