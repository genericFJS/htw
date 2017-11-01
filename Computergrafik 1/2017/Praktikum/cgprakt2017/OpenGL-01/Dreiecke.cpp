/*
  Dreiecke
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
GLint height = 100, width = 100;
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition, vColor };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;
GLuint program;

void init(void) {
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("../OpenGL-01/Dreiecke.vs", "../OpenGL-01/Dreiecke.fs", "");
	glUseProgram(program);
	GLfloat vertices[NumVertices][2] = {
	{-0.90,-0.90},{0.85,-0.90},{-0.90,0.85},{0.90,-0.85},{0.90,0.90},{-0.85,0.90} };
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 1, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices / 2);
	glVertexAttrib3f(vColor, 0, 1, 0);
	glDrawArrays(GL_LINE_LOOP, 3, NumVertices / 2);
	glFlush();
}

void reshape(int w, int h) {
	width = w;
	height = h;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(4, 2);  // (4,5) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);  //GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow(argv[0]);
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
