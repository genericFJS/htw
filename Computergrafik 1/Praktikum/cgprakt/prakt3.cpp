#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>
#include <math.h>

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
GLint height = 150, width = 150;
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition, vColor };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint program;
// meins:
const GLuint triangleX = 10;
const GLuint triangleY = 10;
GLfloat vertices[triangleX*triangleY*3][2];

int windowX = 800;

void calcTriangle() {
	GLuint pos = 0;
	for (int i = 0; i < triangleX; i++) {
		for (int j = 0; j < triangleY ; j++) {
			GLfloat transFactorX = 1 / float(triangleX) * 2;
			GLfloat transFactorY = 1 / float(triangleY) * 2;
			GLfloat transSumX = -1 + transFactorX * i;
			GLfloat transSumY = -1 + transFactorY * j;
			vertices[pos][0] = 0.5 * transFactorX + transSumX ;
			vertices[pos][1] = 1 * transFactorY + transSumY;
			vertices[pos + 1][0] = 0.067 * transFactorX + transSumX;
			vertices[pos + 1][1] = 0.25* transFactorY + transSumY;
			vertices[pos + 2][0] = 0.933 * transFactorX + transSumX;
			vertices[pos + 2][1] = 0.25 * transFactorY + transSumY;
			pos += 3;
		}
	}
}

void drawTriangle() {
	glVertexAttrib3f(vColor, 0, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, triangleX*triangleY * 3);
//	for (int i = 0; i < triangleX*triangleY * 3; i+=3) {
//		glDrawArrays(GL_TRIANGLES, i, 3);
//	}
}

void init(void){
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("OpenGL-01/Dreiecke_prakt3.vs", "OpenGL-01/Dreiecke_prakt3.fs", "");
	glUseProgram(program);
}

void display(void){
	//calcWheelVert();
	calcTriangle();

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.9, 0.9, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawTriangle();
	glBindVertexArray(VAOs[Triangles]);
	glutSwapBuffers();
}

// timer besser.
void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(50, timer, 10);
}

void reshape(int w, int h) {
	width = w;
	height = h;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(windowX, windowX);
	glutInitContextVersion(4, 2);  // (4,5) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);  //GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow("Dreieck Matrix");
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();

	//glutTimerFunc(moveWait, timer, 10);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
