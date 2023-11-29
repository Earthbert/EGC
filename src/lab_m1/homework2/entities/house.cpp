#include "house.h"

#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

House::House(glm::vec2 position, glm::vec3 scaleValues) {
	const glm::vec3 center = glm::vec3(position.x, 0.5 * scaleValues.y, position.y);

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), center);
	const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scaleValues);
	this->renderInfo.push_back(RenderInfo{ HW2_HOUSE_MESH, HW2_BASIC_SHADER,
		translationMatrix * scaleMatrix, RGB_BRICK });
}

House::House() = default;

House::~House() = default;
