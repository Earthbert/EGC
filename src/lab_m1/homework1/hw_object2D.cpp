#include "hw_object2D.h"

#include <vector>

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
