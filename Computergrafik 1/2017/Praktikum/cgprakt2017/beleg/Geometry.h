#pragma once
#include <string>
#include <vector>
#include <math.h>

#include <glm.hpp>
#include <gtx/transform.hpp>
#include <glew.h>
#include <freeglut.h>
#include <FreeImage.h>

#define PI 3.14159

struct vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 tex_coord;
};

class Geometry {
public:
	std::vector<vertex> vertices;
	std::vector<GLuint> indices;
	GLuint texture;

	Geometry();
	Geometry(std::vector<vertex> vertices, std::vector<GLuint> indices, GLuint texture = 0);

	void createCube();
	void createSphere();

	void draw();
	void setup();


private:
	GLuint VAO, VBO, EBO;
};