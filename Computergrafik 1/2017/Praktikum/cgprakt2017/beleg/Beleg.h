#pragma once

#include "Geometry.h"

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
GLuint loadTextures(const char* filename, GLenum minification_filter, GLenum magnification_filter);

void DisplayFunc();
void ReshapeFunc(int w, int h);
void MotionFunc(int mouseX, int mouseY);
void UpdateAnimation(int value);
void SpecialFunc(int specKey, int mouseX, int mouseY);
void KeyboardFunc(unsigned char theKey, int mouseX, int mouseY);
void DrawViewport(GLuint posx, GLuint posy, GLuint WIDTHz, GLuint HEIGHTz, glm::vec3 Sichtpunkt, glm::vec3 Oben);