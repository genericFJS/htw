#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>

GLuint loadShaders(const char* vertexFilePath, const char* fragmentFilePath, const char* geometryFilePath);
GLint height = 150, width = 150;
enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition, vColor };
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 50;
GLuint program;
float maxCoord = 42;
float border = 3;
float eCorrect = 0.5;

float centerHTWx(float c){
	float coordSize = (2 * border + maxCoord - eCorrect) /2;
	return (c + border) / coordSize - 1;
}

float centerHTWy(float c){
	float moveY = 42-30+border/2;
	float coordSize = (2 * border + maxCoord - eCorrect) / 2;
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
		{ centerHTWx(0), centerHTWy(0) },	// H balken 0
		{ centerHTWx(3), centerHTWy(0) },	// H balken 1 
		{ centerHTWx(0), centerHTWy(15) },  
		{ centerHTWx(3), centerHTWy(15) },
		{ centerHTWx(3), centerHTWy(7.5) },	// H Strich 4
		{ centerHTWx(10), centerHTWy(7.5) }, 
		{ centerHTWx(10), centerHTWy(0) },	// H Seite 6
		{ centerHTWx(10), centerHTWy(15) }, // T Strich1 7
		{ centerHTWx(15), centerHTWy(15) },
		{ centerHTWx(18), centerHTWy(0) }, // T Balken 9
		{ centerHTWx(15), centerHTWy(0) },	// T Balken 10
		{ centerHTWx(18), centerHTWy(15) },
		{ centerHTWx(15), centerHTWy(15) },
		{ centerHTWx(22), centerHTWy(0) }, // T-W Strich 13
		{ centerHTWx(22), centerHTWy(15) }, // T-W Strich 14
		{ centerHTWx(26), centerHTWy(15) },
		{ centerHTWx(25), centerHTWy(0) }, // W Balken 16
		{ centerHTWx(22), centerHTWy(0) },	// W Balken 17
		{ centerHTWx(34), centerHTWy(15) },
		{ centerHTWx(31), centerHTWy(15) },
		{ centerHTWx(33), centerHTWy(0) }, // W Balken2 20
		{ centerHTWx(30), centerHTWy(0) },	// W Balken2 21
		{ centerHTWx(42), centerHTWy(15) },
		{ centerHTWx(39), centerHTWy(15) },
		{ centerHTWx(30), centerHTWy(0) }, // W Balken2-Rand 24
		{ centerHTWx(33), centerHTWy(0) },	
		{ centerHTWx(42), centerHTWy(15) },
		{ centerHTWx(39), centerHTWy(15) }
		}; 
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
	glClearColor(0.9,0.9,0.9,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindVertexArray(VAOs[Triangles]);
	glVertexAttrib3f(vColor, 0, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 1, 3);
	glDrawArrays(GL_LINE_LOOP, 4, 2);
	glDrawArrays(GL_LINE_STRIP, 6, 3);
	//glDrawArrays(GL_LINES, 7, 2);
	glDrawArrays(GL_TRIANGLES, 9, 3);
	glDrawArrays(GL_TRIANGLES, 10, 3);
	glDrawArrays(GL_LINE_STRIP, 13, 3);
	//glDrawArrays(GL_LINES, 14, 2);
	glDrawArrays(GL_TRIANGLES, 16, 3);
	glDrawArrays(GL_TRIANGLES, 17, 3);
	glVertexAttrib3f(vColor, 249/255.0, 155/255.0, 28/255.0);
	glDrawArrays(GL_TRIANGLES, 20, 3);
	glDrawArrays(GL_TRIANGLES, 21, 3);
	glVertexAttrib3f(vColor, 0, 0, 0);
	glDrawArrays(GL_LINE_LOOP, 24, 4);
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
	glutInitWindowSize(500, 500);
	glutInitContextVersion(4, 2);  // (4,5) (3,3);
	glutInitContextProfile(GLUT_CORE_PROFILE);  //GLUT_COMPATIBILITY_PROFILE
	glutCreateWindow("HTW Logo");
	glewExperimental = GL_TRUE;
	if (glewInit()) printf("Error");
	init();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
