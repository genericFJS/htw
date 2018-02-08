#include "Beleg.h"

// Fenstergröße
GLuint windowWidth = 900, windowHeight = 600;

// Shader(-ID)
GLuint lightingColor;
GLuint lightingTexture;

// Animationsvariablen
GLfloat animationAngle = 0, animationStep = 0.015, animationSpeed = 1;
GLuint FPS = 30;

// Lichteigenschaften
glm::vec3 light1Position(1, 1, 1);
glm::vec3 light2Position(-1, 2, -1);
glm::vec3 light1Color(1, 1, 1);
glm::vec3 light2Color(1, 1, 1);
GLfloat lightRadius = 3;

// Buchstabenfarbe
glm::vec3 cubeColor(1, 1, 1);

// viewport Variablen
GLfloat viewportRotationZ = 0.2, viewportRotationY = 0.8, viewportDistance = 6, viewportRotationStep = 0.5;

// Vorgefertiges Objekt
Geometry cube, sphere, logocube;

// ==================================================
//                     main
// ==================================================
int main(int argc, char** argv) {
	// glut initialisieren und konfigurieren
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewExperimental = GL_TRUE;
	glutCreateWindow("Rotating RGB by FJS (s74053)");
	if (glewInit())
		printf("Error");
	// Aktiveren von: Tiefenpuffer, Schablonen und Transparenz
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Aktivieren von Texturen
	FreeImage_Initialise(TRUE);

	// Info zu GL ausgeben
	printf("GL renderer:                 %s\n", (char*)glGetString(GL_RENDERER));
	printf("GL version:                  %s\n", (char*)glGetString(GL_VERSION));
	printf("GL shading language version: %s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Shader laden
	lightingColor = loadShaders("ressources/shader.vs", "ressources/colorShader.fs", "");
	lightingTexture = loadShaders("ressources/shader.vs", "ressources/textureShader.fs", "");
	// Textur laden
	cube.texture = loadTextures("ressources/Schreibtisch.png", GL_LINEAR, GL_LINEAR);
	logocube.texture = loadTextures("ressources/FJS-logo_black.png", GL_LINEAR, GL_LINEAR);

	// Erstellen der vorgefertigen Objekte
	logocube.createPlain();
	logocube.setup();
	cube.createCube();
	cube.setup();
	sphere.createSphere(10);
	sphere.setup();

	// Zuweisen der glut Funktionen
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutMotionFunc(MotionFunc);
	glutReshapeFunc(ReshapeFunc);
	glutDisplayFunc(DisplayFunc);

	// Einstellen der Bildwiederholrate
	glutTimerFunc(1000 / FPS, UpdateAnimation, 0);

	glutMainLoop();
}


/// <summary>
/// Fülle das Fenster mit mehreren Viewports.
/// </summary>
void DisplayFunc() {
	glPolygonMode(GL_FRONT, GL_FILL);
	glClearColor(0.3, 0.3, 0.3, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Viewport oben (Kamera steuerbar)
	DrawViewport(
		0,
		0,
		windowWidth * 2 / 3,
		windowHeight,
		glm::vec3(-viewportDistance * sin(viewportRotationY) * sin(viewportRotationZ), viewportDistance * cos(viewportRotationY), -viewportDistance * sin(viewportRotationY) * cos(viewportRotationZ)),
		glm::vec3(0.0, cos(viewportRotationY - PI*0.5), 0.0),
		0);

	// Viewport rechts oben (Frontalansicht)
	//DrawViewport(
	//	windowWidth / 3 * 2,
	//	windowHeight / 2,
	//	windowWidth / 3,
	//	windowHeight / 2,
	//	glm::vec3(0, 0.2, 4),
	//	glm::vec3(0, 1, 0),
	//	1);
	DrawViewport(
		windowWidth / 3 * 2,
		windowHeight / 2,
		windowWidth / 3,
		windowHeight / 2,
		glm::vec3(0, 5, -0.0001),
		glm::vec3(0, 1, 0),
		1);

	// Viewport rechts unten (Vogelperspektive)
	DrawViewport(
		windowWidth / 3 * 2,
		0,
		windowWidth / 3,
		windowHeight / 2,
		glm::vec3(0, 5, -0.0001),
		glm::vec3(0, 1, 0),
		0);

	glFlush();

}

/// <summary>
/// Anpassen der Variablen des veränderten Fensters.
/// </summary>
/// <param name="width">Neue Breite</param>
/// <param name="height">Neue Höhe</param>
void ReshapeFunc(int width, int height) {
	windowWidth = width;
	windowHeight = height;
}

/// <summary>
/// Animationsschritt durchführen.
/// </summary>
/// <param name="value">Nicht genutzt</param>
void UpdateAnimation(int value) {
	animationAngle = animationAngle + animationStep * animationSpeed;
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, UpdateAnimation, 0);
}

/// <summary>
/// Reagiert auf Tastatureingabe.
/// </summary>
/// <param name="theKey">Gedrückte Taste</param>
/// <param name="mouseX">Nicht genutzt</param>
/// <param name="mouseY">Nicht genutzt</param>
void KeyboardFunc(unsigned char theKey, int mouseX, int mouseY) {
	switch (theKey) {
	case '+':
	case 'w':
		// reinzoomen
		viewportDistance -= viewportRotationStep;
		DisplayFunc;
		break;
	case '-':
	case 's':
		// rauszoomen
		viewportDistance += viewportRotationStep;
		DisplayFunc;
		break;
	case 'p':
		// Animation pausieren
		if (animationSpeed == 0) {
			animationSpeed = 1;
		} else {
			animationSpeed = 0;
		}
		break;
	case 'y':
		// Licht 1 Intensität umschalten
		// y   x   c   v   b
		// schwach --> stark
		light1Color = glm::vec3(0, 0, 0);
		break;
	case 'x':
		light1Color = glm::vec3(.25, .25, .25);
		break;
	case 'c':
		light1Color = glm::vec3(.5, .5, .5);
		break;
	case 'v':
		light1Color = glm::vec3(.75, .75, .75);
		break;
	case 'b':
		light1Color = glm::vec3(1, 1, 1);
		break;
	case '1':
		// Licht 2 Intensität umschalten
		// 1   2    3    4    5
		// rot grün blau weiß aus
		light2Color = glm::vec3(1, 0, 0);
		break;
	case '2':
		light2Color = glm::vec3(0, 1, 0);
		break;
	case '3':
		light2Color = glm::vec3(0, 0, 1);
		break;
	case '4':
		light2Color = glm::vec3(1, 1, 1);
		break;
	case '5':
		light2Color = glm::vec3(0, 0, 0);
		break;
	case 'q':
		// Anwendung beenden
		exit(-1);
	}
}

/// <summary>
/// Reagiert auf Tastatureingabe (Sondertasten bzw. Pfeiltasten).
/// </summary>
/// <param name="specKey">Gedrückte Taste</param>
/// <param name="mouseX">Nicht genutzt</param>
/// <param name="mouseY">Nicht genutzt</param>
void SpecialFunc(int specKey, int mouseX, int mouseY) {
	switch (specKey) {
	case GLUT_KEY_LEFT:
		viewportRotationZ -= viewportRotationStep;
		DisplayFunc();
		break;
	case GLUT_KEY_RIGHT:
		viewportRotationZ += viewportRotationStep;
		DisplayFunc();
		break;
	case GLUT_KEY_UP:
		viewportRotationY -= viewportRotationStep;
		DisplayFunc();
		break;
	case GLUT_KEY_DOWN:
		viewportRotationY += viewportRotationStep;
		DisplayFunc();
		break;
	}
}

/// <summary>
/// Reagiert auf Mausbewegung (bei gedrückter Maustaste).
/// </summary>
/// <param name="mouseX">X-Wert Mausposition</param>
/// <param name="mouseY">Y-Wert Mausposition</param>
void MotionFunc(int mouseX, int mouseY) {
	if (mouseX < (windowWidth / 2)) {
		viewportRotationZ -= (mouseX - (windowWidth / 2.0)) / 20000.0;
	} else {
		viewportRotationZ -= (mouseX - (windowWidth / 2.0)) / 20000.0;
	}

	if (mouseY < (windowHeight / 2)) {
		viewportRotationY -= (mouseY - (windowHeight / 2.0)) / 20000.0;
	} else {
		viewportRotationY -= (mouseY - (windowHeight / 2.0)) / 20000.0;
	}

	DisplayFunc();
}

/// <summary>
/// Füllt einen Viewport. Der Viewport setzt sich zusammen aus dem Licht, und den (zusammengesetzten) Objekten.
/// </summary>
/// <param name="viewportPositionX">X-Wert Position des Viewports im Fenster</param>
/// <param name="viewportPositionY">Y-Wert Position des Viewports im Fenster</param>
/// <param name="viewportWidth">Breite des Viewports</param>
/// <param name="viewportHeight">Höhe des Viewports</param>
/// <param name="viewpointInput"></param>
/// <param name="viewpointDirection"></param>
void DrawViewport(GLuint viewportPositionX, GLuint viewportPositionY, GLuint viewportWidth, GLuint viewportHeight, glm::vec3 viewpointInput, glm::vec3 viewpointDirection, int perspective) {
	// Viewport einrichten
	glViewport(viewportPositionX, viewportPositionY, viewportWidth, viewportHeight);

	glm::mat4 cameraProjection;
	if (perspective == 0) {
		cameraProjection = glm::perspective(45.0f, 1.0f, 0.1f, 100.f);
	} else {
		float orthoHeight = 3 * ((float)viewportWidth / viewportHeight);
		float orthoWidth = 3;

		cameraProjection = glm::ortho(-1 * orthoHeight, orthoHeight, -1 * orthoWidth, orthoWidth, 0.1f, 100.0f);
	}

	// Kameraausschnitt einrichten
	GLfloat viewpoint[3];
	viewpoint[0] = viewpointInput.x;
	viewpoint[1] = viewpointInput.y;
	viewpoint[2] = viewpointInput.z;

	glm::mat4 cameraView = glm::lookAt(glm::vec3(viewpoint[0], viewpoint[1], viewpoint[2]), glm::vec3(0, 0, 0), viewpointDirection);

	// Beleuchtung vorbereiten:
	// Beleuchtung für Farboberflächen
	glUseProgram(lightingColor);
	GLint object_color_loc = glGetUniformLocation(lightingColor, "object_color");
	GLint light_color_loc = glGetUniformLocation(lightingColor, "light_color");
	GLint light_color2_loc = glGetUniformLocation(lightingColor, "light_color2");
	GLint light_pos_loc = glGetUniformLocation(lightingColor, "light_pos");
	GLint light_pos2_loc = glGetUniformLocation(lightingColor, "light_pos2");
	GLint view_pos_loc = glGetUniformLocation(lightingColor, "view_pos");
	glUniform3f(object_color_loc, cubeColor.x, cubeColor.y, cubeColor.z);
	glUniform3f(light_color_loc, light1Color.x, light1Color.y, light1Color.z);
	glUniform3f(light_color2_loc, light2Color.x, light2Color.y, light2Color.z);
	glUniform3f(light_pos_loc, light1Position.x, light1Position.y, light1Position.z);
	glUniform3f(light_pos2_loc, light2Position.x, light2Position.y, light2Position.z);
	glUniform3f(view_pos_loc, viewpoint[0], viewpoint[1], viewpoint[2]);
	// Beleuchtung für Texturoberflächen
	glUseProgram(lightingTexture);
	object_color_loc = glGetUniformLocation(lightingTexture, "object_color");
	light_color_loc = glGetUniformLocation(lightingTexture, "light_color");
	light_color2_loc = glGetUniformLocation(lightingTexture, "light_color2");
	light_pos_loc = glGetUniformLocation(lightingTexture, "light_pos");
	light_pos2_loc = glGetUniformLocation(lightingTexture, "light_pos2");
	view_pos_loc = glGetUniformLocation(lightingTexture, "view_pos");
	glUniform3f(object_color_loc, cubeColor.x, cubeColor.y, cubeColor.z);
	glUniform3f(light_color_loc, light1Color.x, light1Color.y, light1Color.z);
	glUniform3f(light_color2_loc, light2Color.x, light2Color.y, light2Color.z);
	glUniform3f(light_pos_loc, light1Position.x, light1Position.y, light1Position.z);
	glUniform3f(light_pos2_loc, light2Position.x, light2Position.y, light2Position.z);
	glUniform3f(view_pos_loc, viewpoint[0], viewpoint[1], viewpoint[2]);

	// Darstellen von Objekten über Farbshader
	glUseProgram(lightingColor);
	// Einstellen der Kamera
	GLint view_loc = glGetUniformLocation(lightingColor, "view");
	GLint proj_loc = glGetUniformLocation(lightingColor, "projection");
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &cameraView[0][0]);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &cameraProjection[0][0]);
	// Vorbereiten der Oberflächen
	glm::mat4 model(1.0);
	glm::mat3 normal_mat(1.0);
	GLint normal_mat_loc = glGetUniformLocation(lightingColor, "normal_mat");
	GLint model_loc = glGetUniformLocation(lightingColor, "model");

	// Darstellen der Lichtpunkte
	glUniform3f(object_color_loc, light1Color.x, light1Color.y, light1Color.z);
	model = glm::mat4(1.0);
	model = glm::translate(model, light1Position);
	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	sphere.draw();

	glUniform3f(object_color_loc, light2Color.x, light2Color.y, light2Color.z);
	model = glm::mat4(1.0);
	model = glm::translate(model, light2Position);
	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	sphere.draw();

	// ROT
	// ======================================================================
	cubeColor = glm::vec3(1, 0.1, 0.1);
	glUniform3f(object_color_loc, cubeColor.x, cubeColor.y, cubeColor.z);

	// Teil a
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-1, .3, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.6, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil b
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-.75, .55, 0));
	model = glm::scale(model, glm::vec3(0.3, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil c
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-.6, .4, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil d
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-.75, .25, 0));
	model = glm::scale(model, glm::vec3(0.3, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil e
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-.75, .15, 0));
	model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil f
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-.6, .05, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// GRÜN
	// ======================================================================
	cubeColor = glm::vec3(0.1, 1, 0.1);
	glUniform3f(object_color_loc, cubeColor.x, cubeColor.y, cubeColor.z);

	// Teil a
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-0.2, .3, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.4, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil b
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(0, .55, 0));
	model = glm::scale(model, glm::vec3(0.4, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil c
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(.2, .45, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil d
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(-.05, .05, 0));
	model = glm::scale(model, glm::vec3(0.3, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil e
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(.2, .15, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.3, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil f
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(.05, .25, 0));
	model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// BLAU
	// ======================================================================
	cubeColor = glm::vec3(0.1, 0.1, 1);
	glUniform3f(object_color_loc, cubeColor.x, cubeColor.y, cubeColor.z);

	// Teil a
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(0.6, .3, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.6, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil b
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(.85, .55, 0));
	model = glm::scale(model, glm::vec3(0.3, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil c
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(1, .45, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil d
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(.85, .35, 0));
	model = glm::scale(model, glm::vec3(0.3, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil e
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(1, .2, 0));
	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Teil f
	model = glm::mat4(1.0);
	model = glm::rotate(model, animationAngle, glm::vec3(0.0, 1.0, 0.0));
	model = glm::translate(model, glm::vec3(.85, .05, 0));
	model = glm::scale(model, glm::vec3(0.3, 0.1, 0.1));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	// Texturierte Oberfläche
	// ======================================================================
	glUseProgram(lightingTexture);
	// Einstellen der Kamera
	view_loc = glGetUniformLocation(lightingTexture, "view");
	proj_loc = glGetUniformLocation(lightingTexture, "projection");
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &cameraView[0][0]);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &cameraProjection[0][0]);
	// Vorbereiten der Oberflächen
	normal_mat_loc = glGetUniformLocation(lightingTexture, "normal_mat");
	model_loc = glGetUniformLocation(lightingTexture, "model");

	// Texturierung nicht einfärben
	cubeColor = glm::vec3(1, 1, 1);
	glUniform3f(object_color_loc, cubeColor.x, cubeColor.y, cubeColor.z);

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0, -.4, 0));
	model = glm::scale(model, glm::vec3(5, 0.1, 5));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	cube.draw();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-1.5, -.84, 1.5));
	model = glm::rotate(model, -1.571f, glm::vec3(1.0, 0.0, 0.0));
	model = glm::rotate(model, 3.0f, glm::vec3(0.0, 0.0, 1.0));

	normal_mat = glm::mat3(glm::transpose(glm::inverse(model)));
	glUniformMatrix3fv(normal_mat_loc, 1, FALSE, &normal_mat[0][0]);
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	logocube.draw();
}