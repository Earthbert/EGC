#include "Tank.h"

#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/const_strings.h"

Tank::Tank(type m_type, glm::vec3 center) {
	this->m_type = m_type;
	this->center = center;
	// Create render info for the tank
	// 0 - track 1 - body 2 - turret 3 - cannon
	{
		renderInfo.push_back(RenderInfo{ HW2_TRACK_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_LIGHT_GREY });
		renderInfo.push_back(RenderInfo{ HW2_BODY_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_MILITARY_BLUE });
		renderInfo.push_back(RenderInfo{ HW2_TURRET_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_MILITARY_GREY });
		renderInfo.push_back(RenderInfo{ HW2_CANNON_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_LIGHT_GREY });
	}
}

Tank::Tank() = default;

Tank::~Tank() = default;
