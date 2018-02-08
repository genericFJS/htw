#pragma once

#include "Geometry.h"

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
GLuint loadTextures(const char* filename, GLenum minification_filter, GLenum magnification_filter);

void DisplayFunc();
void ReshapeFunc(int width, int height);
void UpdateAnimation(int value);
void KeyboardFunc(unsigned char theKey, int mouseX, int mouseY);
void SpecialFunc(int specKey, int mouseX, int mouseY);
void MotionFunc(int mouseX, int mouseY);
void DrawViewport(GLuint viewportPositionX, GLuint viewportPositionY, GLuint viewportWidth, GLuint viewportHeight, glm::vec3 viewpointInput, glm::vec3 viewpointDirection, int perspective);