#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace hw_object2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(const std::string& name,
		float length,
		glm::vec3 color,
		bool fill, float depth = 0);

	Mesh* CreateRectangle(
		const std::string& name,
		float length,
		float width,
		glm::vec3 color,
		bool fill, float depth = 0);
}