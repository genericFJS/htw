#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <glew.h>

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath){

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if(vertexShaderStream.is_open()){
		std::string line = "";
		while( std::getline( vertexShaderStream, line))
			vertexShaderCode += "\n"+line;
		vertexShaderStream.close();
	}else{
		printf("Failed to open vertexShader source!\n");
	}

	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if(fragmentShaderStream.is_open()){
		std::string line = "";
		while( std::getline( fragmentShaderStream, line))
			fragmentShaderCode += "\n" + line;
		fragmentShaderStream.close();
	}else{
		printf("Failed to open fragmentShader source!\n");
	}
	int gsavailable = 0;
	std::string geometryShaderCode;
	std::ifstream geometryShaderStream(geometryFilePath, std::ios::in);
	if (geometryShaderStream.is_open()){
		gsavailable = 1;
		std::string line = "";
		while (std::getline(geometryShaderStream, line))
			geometryShaderCode += "\n" + line;
		geometryShaderStream.close();
	}
	else{
		printf("Failed to open geometryShader source!\n");
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	printf("compiling vertex shader:\n   %s\n", vertexFilePath);
	char const* vertexShaderPointer = vertexShaderCode.c_str();
	const GLint vertexSourceLength = vertexShaderCode.size();
	glShaderSource(vertexShaderID, 1, & vertexShaderPointer, &vertexSourceLength);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE){
		printf("shader putt\n");
	}
	glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> vertexShaderErrorMsg(infoLogLength);
		glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
		printf("%s\n", &vertexShaderErrorMsg[0]);
	}

	printf("compiling fragment shader:\n  %s\n", fragmentFilePath);
	char const* fragmentShaderPointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, NULL);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE){
		printf("shader putt\n");
	}
	glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> fragmentShaderErrorMsg(infoLogLength);
		glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMsg[0]);
		printf("%s\n", &fragmentShaderErrorMsg[0]);
	}

	printf("compiling geometry shader:\n   %s\n", geometryFilePath);
	char const* geometryShaderPointer = geometryShaderCode.c_str();
	const GLint geometrySourceLength = geometryShaderCode.size();
	glShaderSource(geometryShaderID, 1, &geometryShaderPointer, &geometrySourceLength);
	glCompileShader(geometryShaderID);

	glGetShaderiv(geometryShaderID, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE){
		printf("shader putt\n");
	}
	glGetShaderiv(geometryShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0){
		std::vector<char> geometryShaderErrorMsg(infoLogLength);
		glGetShaderInfoLog(geometryShaderID, infoLogLength, NULL, &geometryShaderErrorMsg[0]);
		printf("%s\n", &geometryShaderErrorMsg[0]);
	}

	printf("linking program\n");
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	if(gsavailable)glAttachShader(programID, geometryShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> progErrorMsg(infoLogLength);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &progErrorMsg[0]);
		printf("%s\n", &progErrorMsg[0]);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteShader(geometryShaderID);

	return programID;
}
