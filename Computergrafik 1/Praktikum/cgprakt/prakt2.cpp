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
const GLuint wheelVert = 40;
const GLuint wheelRadiusMult = 5;
const GLuint allWheelVert = wheelVert * wheelRadiusMult;
GLfloat vertices[allWheelVert+1+wheelVert][2];
float wheelRadius = 0.8;
float pi = 3.1415;
int moveWait = 15;	// 
float move = 0.0;	// Position x-Richtung
float vel = 0.01;	// Geschwindigkeit
float velSp = 0.0;	// Geschwindigkeit der Speichen

int windowX = 800;

void calcWheelVert() {
	// Radius zeichnen:
	for (int i = 0; i < allWheelVert;i++) {
		vertices[i][0] = wheelRadius * cos(i * 2 * pi / allWheelVert) + move;
		vertices[i][1] = wheelRadius * sin(i * 2 * pi / allWheelVert);
	}
	// Mittelpunkt:
	vertices[allWheelVert][0] = 0 + move;
	// Speichen:
	vertices[allWheelVert][1] = 0;
	for (int i = allWheelVert+1; i < allWheelVert+1 + wheelVert; i++) {
		vertices[i][0] = wheelRadius * cos((i-velSp) * 2 * pi / wheelVert) + move;
		vertices[i][1] = wheelRadius * sin((i-velSp) * 2 * pi / wheelVert);
	}

	// Kommt von links wieder:
	if (move > 1+wheelRadius) {
		move = -1-0.1-wheelRadius;
	}

}

void init(void){
	printf("\n%s", (char*)glGetString(GL_RENDERER));
	printf("\n%s", (char*)glGetString(GL_VERSION));
	printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	program = loadShaders("OpenGL-01/Dreiecke.vs", "OpenGL-01/Dreiecke.fs", "");
	glUseProgram(program);
}

void display(void){
	calcWheelVert();

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.9, 0.9, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 0, 0, 0);
	glDrawArrays(GL_LINE_LOOP, 0, allWheelVert);
	glDrawArrays(GL_TRIANGLE_FAN, allWheelVert, wheelVert+1);
	// glFlush() für einfachen Buffer
	//glFlush();
	/// glut... für GLUT_DOUBLE
	glutSwapBuffers();
}

// idle: Schlechte angewohnheit, da display() Fehleranfällig. Besser mit timer().
void idle(void){
	move += vel;
	velSp = move * 10;
	display();
	Sleep(25);
}

// timer besser.
void timer(int value) {
	move += vel;
	velSp = move * 10;
	glutPostRedisplay();
	glutTimerFunc(moveWait, timer, 10);
}

void reshape(int w, int h) {
	width = w;
	height = h;
	move = 0.0;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	// |GLUT_DOUBLE : doppelter Buffer für geschmeidigere Animation
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(windowX, windowX);
	glutInitContextVersion(4, 2);  // (4,5) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);  //GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow("Drehendes Rad");
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();

	glutTimerFunc(10, timer, 10);
	//glutIdleFunc(idle);
	//timer(0);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
