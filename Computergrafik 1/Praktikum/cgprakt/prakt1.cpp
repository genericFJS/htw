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
const GLuint NumVertices = 50;
GLuint program;

float centerHTWx(float c){
	float border = 3;
	float maxCoord = 30;
	float coordSize = (2 * border + maxCoord) /2;
	printf("%f ",(c + border) / coordSize - 1);
	return (c + border) / coordSize - 1;
}

float centerHTWy(float c){
	float border = 3;
	float moveY = 15/2;
	float maxCoord = 30;
	float coordSize = (2 * border + maxCoord) / 2;
	printf("%f ", (c + border) / coordSize - 1);
	return (c + border + moveY) / coordSize - 1;
}

void init(void)
{
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("OpenGL-01/Dreiecke.vs", "OpenGL-01/Dreiecke.fs", "");
	glUseProgram(program);
	GLfloat vertices[NumVertices][2] = {
		{ centerHTWx(0), centerHTWy(0) },	// 1
		{ centerHTWx(3), centerHTWy(0) },	// 2
		{ centerHTWx(0), centerHTWy(15) }, // 3
		{ centerHTWx(3), centerHTWy(15) },
		{ centerHTWx(3), centerHTWy(7.5) },
		{ centerHTWx(10), centerHTWy(7.5) }, // 4
		{ centerHTWx(10), centerHTWy(0) },
		{ centerHTWx(10), centerHTWy(15) },
		{ centerHTWx(15), centerHTWy(15) },
		{ centerHTWx(15), centerHTWy(0) }, // 5
		{ centerHTWx(18), centerHTWy(0) },
		{ centerHTWx(18), centerHTWy(15) },
		{ centerHTWx(15), centerHTWy(15) },
		{ centerHTWx(22), centerHTWy(0) }, // 6
		{ centerHTWx(25), centerHTWy(0) }, // 7
		{ centerHTWx(31), centerHTWy(15) }, // 8
		{ centerHTWx(26), centerHTWy(15) }, // 9
		{ centerHTWx(30), centerHTWy(0) } }; // 10
	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);
}

void display(void)
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 1, 3);
	glDrawArrays(GL_LINE_LOOP, 4, 2);
	glDrawArrays(GL_LINES, 6, 2);
	glDrawArrays(GL_LINES, 7, 2);
	glDrawArrays(GL_TRIANGLES, 9, 3);
	glDrawArrays(GL_TRIANGLES, 10, 3);
	//glVertexAttrib3f(vColor, 0, 1, 0);
	//glDrawArrays(GL_LINE_LOOP, 3, NumVertices / 2);
	glFlush();
}

void reshape(int w, int h) {
	width = w;
	height = h;
}

int main(int argc, char** argv)
{
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
