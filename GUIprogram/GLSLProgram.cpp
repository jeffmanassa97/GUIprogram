#include "GLSLProgram.h"
#include "Errors.h"

#include <vector>

#include <fstream>

//initialization list works only for constructors
GLSLProgram::GLSLProgram() : _numAttributes(0), _programID(0), _vertexShaderID(0), _fragmentShaderID(0) //order matters of declared matters
{
}


GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
	//Vertex and fragment shaders are successfully compiled.
	//Now time to link them together into a program.
	//Get a program object.
	_programID = glCreateProgram();
	
	//create the vertex shader object, and store its id
	_vertexShaderID = glCreateShader(GL_VERTEX_SHADER); //returns a GLuint; OpenGL calls always returns 0 if there is an error
	if (_vertexShaderID == 0) {
		fatalError("Vertex shader failed to be created!");
	}

	_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); //created a fragment shader
	if (_fragmentShaderID == 0) {
		fatalError("Fragment shader failed to be created!");
	}

	compileShader(vertexShaderFilePath, _vertexShaderID);
	compileShader(fragmentShaderFilePath, _fragmentShaderID);
}
 

void GLSLProgram::linkShaders() { //combine the files into one program

	//Attach our shaders to our program
	glAttachShader(_programID, _vertexShaderID);
	glAttachShader(_programID, _fragmentShaderID);

	//Link our program
	glLinkProgram(_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked); //all this is is error checking
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(_programID);
		//Don't leak shaders either.
		glDeleteShader(_vertexShaderID);
		glDeleteShader(_fragmentShaderID);

		std::printf("%s\n", &(errorLog[0])); //the address of the first element of errorlog is the same thing as it being interpreted as a string
		fatalError("Shaders failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(_programID, _vertexShaderID);
	glDetachShader(_programID, _fragmentShaderID);
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string& attributeName) {
	//0 indexed array(_numAttributes) depending on the number of attributes, only have one right now; after the line it will +1 for next time the function is called there will be another attribute
	glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str()); //binds an attribute to a location to be used in use()

}

GLint GLSLProgram::getUniformLocation(const std::string uniformName) { //to find the location/ID of the uniform variable for time
	//returns a GLint, not GLuint which is unsigned int
	GLint location = glGetUniformLocation(_programID, uniformName.c_str()); //_prograID to associate it with a specific program
	if (location == GL_INVALID_INDEX) {
		fatalError("Uniform " + uniformName + " not found in shader!");
	}
	return location;
}

void GLSLProgram::use() {
	glUseProgram(_programID);
	for (int i = 0; i < _numAttributes; i++) {//enable the index of vertexPosition
		glEnableVertexAttribArray(i); //the index of atributes
	}
}

void GLSLProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < _numAttributes; i++) {//enable the index of vertexPosition
		glDisableVertexAttribArray(i); //the index of atributes
	}
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail()) {
		perror(filePath.c_str()); //will be specific to the problem, after custom message is ": "
		fatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line)) { //if it successfuly read a line, it will return a positve number true
		fileContents += line + '\n'; //will read the entire file into fileContents when skipping lines
	}

	vertexFile.close(); //close file
	//c-string is an array of characters. .c_str() pulls the c-string from string. This line just passes an array that is one c-string
	const char* contentsPtr = fileContents.c_str();
	//tell GL where to get the source for compilation; number of strings where all the text is, count: 1; a pointer to the c-string of fileContents; length of each c-string, but since there's only one string it's nullptr
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	//From wiki on "OpenGL shader compilation"
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength); //will get maxlength

		// The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]); //will take the log that OpenGL created and put it into errorLog

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(id); // Don't leak the shader.
		//printf will print, "%s" is c-string of what's after the comma
		std::printf("%s\n", &(errorLog[0])); //the address of the first element of errorlog is the same thing as it being interpreted as a string
		fatalError("Shader " + filePath + " failed to compile!");
	}

}