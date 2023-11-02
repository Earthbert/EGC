#include "hw_object2D.h"

#include <vector>
#include <math.h>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* hw_object2D::CreateSquare(
	const std::string& name,
	float length,
	glm::vec3 color,
	bool fill, float depth)
{
	float lengthH = length / 2.0f;
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-lengthH, -lengthH, depth), color),
		VertexFormat(glm::vec3(lengthH, -lengthH, depth), color),
		VertexFormat(glm::vec3(lengthH, lengthH, depth), color),
		VertexFormat(glm::vec3(-lengthH, lengthH, depth), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* hw_object2D::CreateRectangle(
	const std::string& name,
	float width,
	float heigth,
	glm::vec3 color,
	bool fill, float depth)
{
	float widthH = width / 2.0f;
	float heigthH = heigth / 2.0f;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(-widthH, -heigthH, depth), color),
		VertexFormat(glm::vec3(widthH, -heigthH, depth), color),
		VertexFormat(glm::vec3(widthH, heigthH, depth), color),
		VertexFormat(glm::vec3(-widthH, heigthH, depth), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// Draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* hw_object2D::CreateHexagon(
	const std::string& name,
	float radius,
	glm::vec3 color,
	bool fill, float depth)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < 6.0f; i++)
	{
		float theta = 2.0f * M_PI * float(i) / 6.0f + M_PI / 4;

		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		vertices.push_back(VertexFormat(glm::vec3(x, y, depth), color));
		indices.push_back(i);
	}

	Mesh* hexagon = new Mesh(name);

	if (!fill) {
		hexagon->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		vertices.push_back(VertexFormat(glm::vec3(0, 0, depth), color));
		indices.insert(indices.begin(), 6);
		indices.push_back(0);
		hexagon->SetDrawMode(GL_TRIANGLE_FAN);
	}

	hexagon->InitFromData(vertices, indices);
	return hexagon;
}

Mesh* hw_object2D::CreateStar(
	const std::string& name,
	float radius,
	float innerRadius,
	glm::vec3 color,
	bool fill, float depth)
{
	std::vector<VertexFormat> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < 5.0f; i++)
	{
		float theta = 2.0f * M_PI * float(i) / 5.0f + M_PI / 2.0;
		float innerTheta = 2.0f * M_PI * float(i) / 5.0f + M_PI / 2.0 + M_PI / 5.0f;

		float x = radius * cosf(theta);
		float y = radius * sinf(theta);

		float innerX = innerRadius * cosf(innerTheta);
		float innerY = innerRadius * sinf(innerTheta);

		vertices.push_back(VertexFormat(glm::vec3(x, y, depth), color));
		indices.push_back(2 * i);

		vertices.push_back(VertexFormat(glm::vec3(innerX, innerY, depth), color));
		indices.push_back(2 * i + 1);
	}

	Mesh* star = new Mesh(name);

	if (!fill) {
		star->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		vertices.push_back(VertexFormat(glm::vec3(0, 0, depth), color));
		indices.insert(indices.begin(), 10);
		indices.push_back(0);
		star->SetDrawMode(GL_TRIANGLE_FAN);
	}

	star->InitFromData(vertices, indices);
	return star;
}

Mesh* hw_object2D::CreateRomb(
	const std::string& name,
	float radius,
	glm::vec3 color,
	float depth)
{
	std::vector<VertexFormat> vertices =
	{
		VertexFormat(glm::vec3(0, radius, depth), color),
		VertexFormat(glm::vec3(radius / 2, 0, depth), color),
		VertexFormat(glm::vec3(0, -radius, depth), color),
		VertexFormat(glm::vec3(-radius / 2, 0, depth), color),

		VertexFormat(glm::vec3(0, radius / 4, depth), color),
		VertexFormat(glm::vec3(radius, radius / 4, depth), color),
		VertexFormat(glm::vec3(0, -radius / 4, depth), color),
		VertexFormat(glm::vec3(radius, -radius / 4, depth), color)
	};

	Mesh* romb = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 3, 1, 2, 3, 4, 5, 7, 4, 6, 7};

	romb->SetDrawMode(GL_TRIANGLES);

	romb->InitFromData(vertices, indices);
	return romb;
}

