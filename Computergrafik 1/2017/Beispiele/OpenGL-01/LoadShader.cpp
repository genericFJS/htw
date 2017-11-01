#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include <glew.h>

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath,
	const char* geometryFilePath, const char* tesscontrolFilePath,
	const char* tessevaluationFilePath, const char* computeFilePath){

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
	GLuint tesscontrolShaderID = glCreateShader(GL_TESS_CONTROL_SHADER);
	GLuint tessevaluationShaderID = glCreateShader(GL_TESS_EVALUATION_SHADER);
	GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);

	GLint result = GL_FALSE;
	int infoLogLength;

	int vsavailable = 0;
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if (vertexShaderStream.is_open()){
		vsavailable = 1;
		std::string line = "";
		while (std::getline(vertexShaderStream, line))
			vertexShaderCode += "\n" + line;
		vertexShaderStream.close();	}
	else{ printf("Failed to open vertex shader source!\n"); }
	if (vsavailable){
		printf("compiling vertex shader: %s\n", vertexFilePath);
		char const* vertexShaderPointer = vertexShaderCode.c_str();
		const GLint vertexSourceLength = vertexShaderCode.size();
		glShaderSource(vertexShaderID, 1, &vertexShaderPointer, &vertexSourceLength);
		glCompileShader(vertexShaderID);
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE){
			printf("shader putt\n");
		}
		glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0){
			std::vector<char> vertexShaderErrorMsg(infoLogLength);
			glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMsg[0]);
			printf("%s\n", &vertexShaderErrorMsg[0]);
		}
	}

	int fsavailable = 0;
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if (fragmentShaderStream.is_open()){
		fsavailable = 1;
		std::string line = "";
		while (std::getline(fragmentShaderStream, line))
			fragmentShaderCode += "\n" + line;
		fragmentShaderStream.close(); }
	else{ printf("Failed to open fragment shader source!\n"); }
	if (fsavailable){
		printf("compiling fragment shader: %s\n", fragmentFilePath);
		char const* fragmentShaderPointer = fragmentShaderCode.c_str();
		glShaderSource(fragmentShaderID, 1, &fragmentShaderPointer, NULL);
		glCompileShader(fragmentShaderID);
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE){
			printf("shader putt\n");
		}
		glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0){
			std::vector<char> fragmentShaderErrorMsg(infoLogLength);
			glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMsg[0]);
			printf("%s\n", &fragmentShaderErrorMsg[0]);
		}
	}

	int gsavailable = 0;
	std::string geometryShaderCode;
	std::ifstream geometryShaderStream(geometryFilePath, std::ios::in);
	if (geometryShaderStream.is_open()){
		gsavailable = 1;
		std::string line = "";
		while (std::getline(geometryShaderStream, line))
			geometryShaderCode += "\n" + line;
		geometryShaderStream.close(); }
	else{ printf("Failed to open geometry shader source!\n"); }
	if (gsavailable){
		printf("compiling geometry shader: %s\n", geometryFilePath);
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
	}

	int tcsavailable = 0;
	std::string tesscontrolShaderCode;
	std::ifstream tesscontrolShaderStream(tesscontrolFilePath, std::ios::in);
	if (tesscontrolShaderStream.is_open()){
		tcsavailable = 1;
		std::string line = "";
		while (std::getline(tesscontrolShaderStream, line))
			tesscontrolShaderCode += "\n" + line;
		tesscontrolShaderStream.close(); }
	else{ printf("Failed to open tesscontrol shader source!\n"); }
	if (tcsavailable){
		printf("compiling tesscontrol shader: %s\n", tesscontrolFilePath);
		char const* tesscontrolShaderPointer = tesscontrolShaderCode.c_str();
		const GLint tesscontrolSourceLength = tesscontrolShaderCode.size();
		glShaderSource(tesscontrolShaderID, 1, &tesscontrolShaderPointer, &tesscontrolSourceLength);
		glCompileShader(tesscontrolShaderID);
		glGetShaderiv(tesscontrolShaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE){
			printf("shader putt\n");
		}
		glGetShaderiv(tesscontrolShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0){
			std::vector<char> tesscontrolShaderErrorMsg(infoLogLength);
			glGetShaderInfoLog(tesscontrolShaderID, infoLogLength, NULL, &tesscontrolShaderErrorMsg[0]);
			printf("%s\n", &tesscontrolShaderErrorMsg[0]);
		}
	}

	int tesavailable = 0;
	std::string tessevaluationShaderCode;
	std::ifstream tessevaluationShaderStream(tessevaluationFilePath, std::ios::in);
	if (tessevaluationShaderStream.is_open()){
		tesavailable = 1;
		std::string line = "";
		while (std::getline(tessevaluationShaderStream, line))
			tessevaluationShaderCode += "\n" + line;
		tessevaluationShaderStream.close();	}
	else{ printf("Failed to open tessevaluation shader source!\n"); }
	if (tesavailable){
		printf("compiling tessevaluation shader: %s\n", tessevaluationFilePath);
		char const* tessevaluationShaderPointer = tessevaluationShaderCode.c_str();
		const GLint tessevaluationSourceLength = tessevaluationShaderCode.size();
		glShaderSource(tessevaluationShaderID, 1, &tessevaluationShaderPointer, &tessevaluationSourceLength);
		glCompileShader(tessevaluationShaderID);
		glGetShaderiv(tessevaluationShaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE){
			printf("shader putt\n");
		}
		glGetShaderiv(tessevaluationShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0){
			std::vector<char> tessevaluationShaderErrorMsg(infoLogLength);
			glGetShaderInfoLog(tessevaluationShaderID, infoLogLength, NULL, &tessevaluationShaderErrorMsg[0]);
			printf("%s\n", &tessevaluationShaderErrorMsg[0]);
		}
	}

	int cosavailable = 0;
	std::string computeShaderCode;
	std::ifstream computeShaderStream(computeFilePath, std::ios::in);
	if (computeShaderStream.is_open()){
		cosavailable = 1;
		std::string line = "";
		while (std::getline(computeShaderStream, line))
			computeShaderCode += "\n" + line;
		computeShaderStream.close(); }
	else{ printf("Failed to open compute shader source!\n"); }
	if (cosavailable){
		printf("compiling compute shader: %s\n", computeFilePath);
		char const* computeShaderPointer = computeShaderCode.c_str();
		const GLint computeSourceLength = computeShaderCode.size();
		glShaderSource(computeShaderID, 1, &computeShaderPointer, &computeSourceLength);
		glCompileShader(computeShaderID);
		glGetShaderiv(computeShaderID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE){
			printf("shader putt\n");
		}
		glGetShaderiv(computeShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0){
			std::vector<char> computeShaderErrorMsg(infoLogLength);
			glGetShaderInfoLog(computeShaderID, infoLogLength, NULL, &computeShaderErrorMsg[0]);
			printf("%s\n", &computeShaderErrorMsg[0]);
		}
	}

	printf("linking program\n");
	GLuint programID = glCreateProgram();
	if (vsavailable)glAttachShader(programID, vertexShaderID);
	if (fsavailable)glAttachShader(programID, fragmentShaderID);
	if (gsavailable)glAttachShader(programID, geometryShaderID);
	if (tcsavailable)glAttachShader(programID, tesscontrolShaderID);
	if (tesavailable)glAttachShader(programID, tessevaluationShaderID);
	if (cosavailable)glAttachShader(programID, computeShaderID);
	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if(infoLogLength > 0){
		std::vector<char> progErrorMsg(infoLogLength);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &progErrorMsg[0]);
		printf("%s\n", &progErrorMsg[0]); }

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteShader(geometryShaderID);
	glDeleteShader(tesscontrolShaderID);
	glDeleteShader(tessevaluationShaderID);
	glDeleteShader(computeShaderID);

	return programID;
}
