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
// navi:
GLfloat pi = 3.14159;
GLfloat alpha = 0.2, beta = 0.8, dist = 5, DELTA = 0.5;
void display(void);
// meins:
GLuint cubeX = 0;
GLuint cubeY = 0;
GLuint cubeZ = 0;
GLuint cubeD = 1;
GLuint coneX = 0;
GLuint coneY = 0;
GLuint coneZ = 0;
GLuint coneD = 1;
const GLuint coneF = 42;
GLfloat vertices[6*4+1+coneF][3];
GLfloat norm = 0.5;

int windowX = 800;

void calcBodys() {
	GLuint i = 0;
	// hinten
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY - 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ - 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX + 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY - 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ - 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX + 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY + 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ - 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY + 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ - 0.5*cubeD)*norm;
	i++;
	// vorne
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY - 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ + 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX + 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY - 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ + 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX + 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY + 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ + 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY + 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ + 0.5*cubeD)*norm;
	i++;
	// links
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY - 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ - 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY + 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ - 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY - 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ + 0.5*cubeD)*norm;
	i++;
	vertices[i][0] = (cubeX - 0.5*cubeD)*norm;
	vertices[i][1] = (cubeY + 0.5*cubeD)*norm;
	vertices[i][2] = (cubeZ + 0.5*cubeD)*norm;
	i++;
}

void drawBodys() {
	glVertexAttrib3f(vColor, 0.5, 0.5, 0.2);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glVertexAttrib3f(vColor, 0.5, 0.5, 0.3);
	glDrawArrays(GL_TRIANGLE_FAN, 3, 4);
	glVertexAttrib3f(vColor, 0.5, 0.5, 0.4);
	glDrawArrays(GL_TRIANGLE_FAN, 7, 4);
	glVertexAttrib3f(vColor, 0.5, 0.5, 0.5);
	glDrawArrays(GL_TRIANGLE_FAN, 11, 4);
	glVertexAttrib3f(vColor, 1, 0.5, 0.5);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void keyboard(unsigned char theKey, int mouseX, int mouseY) {
	GLint x = mouseX;
	GLint y = height - mouseY;
	switch (theKey) {
	case 'v': dist -= DELTA; display(); break;
	case 'z': dist += DELTA; display(); break;
	case 'e': exit(-1);
	}
}

void special(int specKey, int mouseX, int mouseY) {
	GLint x = mouseX;
	GLint y = height - mouseY;
	switch (specKey) {
	case GLUT_KEY_LEFT: alpha -= DELTA; display(); break;
	case GLUT_KEY_RIGHT: alpha += DELTA; display(); break;
	case GLUT_KEY_UP: beta -= DELTA; display(); break;
	case GLUT_KEY_DOWN: display(); beta += DELTA; break;
	}
}

void mouse(int theButton, int State, int mouseX, int mouseY) {
	GLint x = mouseX; GLint y = height - mouseY;
}

void motion(int mouseX, int mouseY) {
	if (mouseX<(width / 2)) { alpha -= (mouseX - (width / 2)) / 10000.0; }
	else { alpha -= (mouseX - (width / 2)) / 10000.0; }
	if (mouseY<(height / 2)) { beta -= (mouseY - (height / 2)) / 10000.0; }
	else { beta -= (mouseY - (height / 2)) / 10000.0; }
	display();
}

void init(void){
	//printf("\n%s", (char*)glGetString(GL_RENDERER));
	//printf("\n%s", (char*)glGetString(GL_VERSION));
	//printf("\n%s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	//program = loadShaders("OpenGL-04/VertexSh4.vs", "OpenGL-04/FragmentSh4.fs", "");
	program = loadShaders("OpenGL-04/VertexSh4.vs", "OpenGL-04/FragmentSh4.fs", "");
	glUseProgram(program);
}

void display(void){
	// Steuerung:
	GLfloat viewpoint[3];
	viewpoint[0] = dist*sin(beta)*sin(alpha);
	viewpoint[1] = dist*cos(beta);
	viewpoint[2] = dist*sin(beta)*cos(alpha);
	glViewport(0, 0, width, height);
	glm::mat4 Projection = glm::perspective(45.0f, 1.0f, 0.1f, 100.f);
	glm::mat4 View = glm::lookAt(glm::vec3(viewpoint[0], viewpoint[1], viewpoint[2]),
		glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.0, cos(beta - 3.141593*0.5), 0.0));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 ModelViewProjection = glm::mat4(1.0f);
	//glm::mat4 ModelViewProjection=Projection*View*Model;
	GLuint Location = glGetUniformLocation(program, "ModelViewProjection");
	glUniformMatrix4fv(Location, 1, GL_FALSE, &ModelViewProjection[0][0]);

	//calcWheelVert();
	calcBodys();

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(vPosition);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glClearColor(0.9, 0.9, 0.9, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	drawBodys();
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

	// Steuerung: 
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	//glutTimerFunc(moveWait, timer, 10);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
