#include "lab_m1/homework2/entities/missile.h"

#include "explosion.h"
#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

Missile::Missile(glm::vec3 initalPosition, glm::vec3 direction) : Collidable(initalPosition, HW2_MISSILE_RADIUS) {
	this->position = initalPosition;
	this->direction = direction;

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1), position);
	const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1), glm::vec3(HW2_MISSILE_RADIUS));

	renderInfo.push_back(RenderInfo{HW2_BALL_MESH, HW2_BASIC_SHADER, 
		translationMatrix * scaleMatrix, RGB_BLACK});
}

Missile::~Missile() = default;

bool Missile::travel(float deltaTime) {
	distanceLeft -= deltaTime * speed;
	position += glm::normalize(direction) * deltaTime * speed;
	hitBoxCenter = position;

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1), glm::normalize(direction) * deltaTime * speed);
	renderInfo[0].model_matrix = translationMatrix * renderInfo[0].model_matrix;
	if (distanceLeft <= 0)
		return true;
	return false;
}

Explosion Missile::explode() const {
	return {position, 8 * HW2_MISSILE_RADIUS};
}
