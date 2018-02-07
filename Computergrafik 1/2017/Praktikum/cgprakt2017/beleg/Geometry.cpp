#include "Geometry.h"

Geometry::Geometry() {}
Geometry::Geometry(std::vector<vertex> vertices, std::vector<GLuint> indices, GLuint texture) {
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;
}

/// <summary>
/// Erstellt einen Würfel mit der Seitenlänge 1 am Punkt (0,0,0).
/// Dieser kann mit Transformierungen später vielseitig eingesetzt werden.
/// </summary>
void Geometry::createCube() {
	vertex vrtx;

	// Vorderseite
	vrtx.position = glm::vec3(-0.5, -0.5, 0.5); vrtx.tex_coord = glm::vec2(0, 0); vrtx.normal = glm::vec3(0, 0, 1); vertices.push_back(vrtx);	// Ecke 0
	vrtx.position = glm::vec3(0.5, -0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 0); vrtx.normal = glm::vec3(0, 0, 1); vertices.push_back(vrtx);	// Ecke 1
	vrtx.position = glm::vec3(-0.5, 0.5, 0.5); vrtx.tex_coord = glm::vec2(0, 1); vrtx.normal = glm::vec3(0, 0, 1); vertices.push_back(vrtx);	// Ecke 2
	vrtx.position = glm::vec3(0.5, 0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 1); vrtx.normal = glm::vec3(0, 0, 1); vertices.push_back(vrtx);		// Ecke 3

	// Seite rechts
	vrtx.position = glm::vec3(0.5, -0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 0); vrtx.normal = glm::vec3(1, 0, 0); vertices.push_back(vrtx);	// Ecke 4
	vrtx.position = glm::vec3(0.5, -0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 0); vrtx.normal = glm::vec3(1, 0, 0); vertices.push_back(vrtx);	// Ecke 5
	vrtx.position = glm::vec3(0.5, 0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 1); vrtx.normal = glm::vec3(1, 0, 0); vertices.push_back(vrtx);	// Ecke 6
	vrtx.position = glm::vec3(0.5, 0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 1); vrtx.normal = glm::vec3(1, 0, 0); vertices.push_back(vrtx);		// Ecke 7

	// Seite links
	vrtx.position = glm::vec3(-0.5, -0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 0); vrtx.normal = glm::vec3(-1, 0, 0); vertices.push_back(vrtx);	// Ecke 8
	vrtx.position = glm::vec3(-0.5, -0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 0); vrtx.normal = glm::vec3(-1, 0, 0); vertices.push_back(vrtx);	// Ecke 9
	vrtx.position = glm::vec3(-0.5, 0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 1); vrtx.normal = glm::vec3(-1, 0, 0); vertices.push_back(vrtx);	// Ecke 10
	vrtx.position = glm::vec3(-0.5, 0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 1); vrtx.normal = glm::vec3(-1, 0, 0); vertices.push_back(vrtx);	// Ecke 11

	// Oberseite
	vrtx.position = glm::vec3(-0.5, -0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 0); vrtx.normal = glm::vec3(0, -1, 0); vertices.push_back(vrtx);	// Ecke 12
	vrtx.position = glm::vec3(0.5, -0.5, -0.5); vrtx.tex_coord = glm::vec2(1, 0); vrtx.normal = glm::vec3(0, -1, 0); vertices.push_back(vrtx);	// Ecke 13
	vrtx.position = glm::vec3(-0.5, -0.5, 0.5); vrtx.tex_coord = glm::vec2(0, 1); vrtx.normal = glm::vec3(0, -1, 0); vertices.push_back(vrtx);	// Ecke 14
	vrtx.position = glm::vec3(0.5, -0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 1); vrtx.normal = glm::vec3(0, -1, 0); vertices.push_back(vrtx);	// Ecke 15

	// Unterseite
	vrtx.position = glm::vec3(-0.5, 0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 0); vrtx.normal = glm::vec3(0, 1, 0); vertices.push_back(vrtx);	// Ecke 16
	vrtx.position = glm::vec3(0.5, 0.5, -0.5); vrtx.tex_coord = glm::vec2(1, 0); vrtx.normal = glm::vec3(0, 1, 0); vertices.push_back(vrtx);	// Ecke 17
	vrtx.position = glm::vec3(-0.5, 0.5, 0.5); vrtx.tex_coord = glm::vec2(0, 1); vrtx.normal = glm::vec3(0, 1, 0); vertices.push_back(vrtx);	// Ecke 18
	vrtx.position = glm::vec3(0.5, 0.5, 0.5); vrtx.tex_coord = glm::vec2(1, 1); vrtx.normal = glm::vec3(0, 1, 0); vertices.push_back(vrtx);		// Ecke 19

	// Hinterseite
	vrtx.position = glm::vec3(-0.5, -0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 0); vrtx.normal = glm::vec3(0, 0, -1); vertices.push_back(vrtx);	// Ecke 20
	vrtx.position = glm::vec3(0.5, -0.5, -0.5); vrtx.tex_coord = glm::vec2(1, 0); vrtx.normal = glm::vec3(0, 0, -1); vertices.push_back(vrtx);	// Ecke 21
	vrtx.position = glm::vec3(-0.5, 0.5, -0.5); vrtx.tex_coord = glm::vec2(0, 1); vrtx.normal = glm::vec3(0, 0, -1); vertices.push_back(vrtx);	// Ecke 22
	vrtx.position = glm::vec3(0.5, 0.5, -0.5); vrtx.tex_coord = glm::vec2(1, 1); vrtx.normal = glm::vec3(0, 0, -1); vertices.push_back(vrtx);	// Ecke 23

	indices = {
		0, 1, 2, 1, 2, 3,		// Vorderseite
		4, 5, 6, 5, 6, 7,		// Seite rechts
		8, 9, 10, 9, 10, 11,	// Seite links
		12, 13, 14, 13, 14, 15,	// Oberseite
		16, 17, 18, 17, 18, 19,	// Unterseite
		20, 21, 22, 21, 22, 23	// Hinterseite
	};

	this->vertices = vertices;
	this->indices = indices;
}

/// <summary>
/// Erstellt eine Kugel mit dem Radius 0.5.
/// </summary>
void Geometry::createSphere() {
	double lati_bands = 30;
	double longi_bands = 30;
	double radius = 0.5;

	for (double lati_num = 0; lati_num <= lati_bands; lati_num++) {
		double theta = lati_num * PI / lati_bands;
		double sin_theta = sin(theta);
		double cos_theta = cos(theta);

		for (double longi_num = 0; longi_num <= longi_bands; longi_num++) {
			double phi = longi_num * 2 * PI / longi_bands;
			double sin_phi = sin(phi);
			double cos_phi = cos(phi);

			vertex va;
			va.normal = glm::vec3(cos_phi * sin_theta, cos_theta, sin_phi * sin_theta);
			va.tex_coord = glm::vec2(1 - (longi_num / longi_bands), 1 - (lati_num / lati_bands));
			va.position = glm::vec3(radius * va.normal.x, radius * va.normal.y, radius * va.normal.z);
			vertices.push_back(va);
		}

		for (int lati_num = 0; lati_num < lati_bands; lati_num++) {
			for (int longi_num = 0; longi_num < longi_bands; longi_num++) {
				int first = (lati_num * (longi_bands + 1)) + longi_num;
				int second = first + longi_bands + 1;

				indices.push_back(first);
				indices.push_back(second);
				indices.push_back(first + 1);

				indices.push_back(second);
				indices.push_back(second + 1);
				indices.push_back(first + 1);
			}
		}
		this->vertices = vertices;
		this->indices = indices;
	}
}

/// <summary>
/// Zeichnet das Objekt (ggf. texturiert).
/// </summary>
void Geometry::draw() {
	if (this->texture != 0)
		glBindTexture(GL_TEXTURE_2D, this->texture);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

/// <summary>
/// Bereitet die geladenen Vertices zur Benutzung vor.
/// </summary>
void Geometry::setup() {
	// Buffer erstellen
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	// In Vertex Buffer laden
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)* this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* this->indices.size(), &this->indices[0], GL_STATIC_DRAW);

	// Setzen der Vertex Attribut Pointer
	// Vertex Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
	// Vertex Normalen
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, normal));
	// Vertex Texture Koordinaten
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, tex_coord));

	glBindVertexArray(0);
}