#include "explosion.h"

#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

Explosion::Explosion(glm::vec3 position, float size) {
	this->position = position;
	this->size = size;

	renderInfo.push_back(RenderInfo{ HW2_BALL_MESH, HW2_BASIC_SHADER,
		glm::scale(glm::translate(glm::mat4(0), position), glm::vec3(size)), RGB_ORANGE });
}

Explosion::Explosion() = default;

Explosion::~Explosion() = default;

bool Explosion::update(float deltaTimeSeconds) {
	size -= deltaTimeSeconds * implosionSpeed;

	renderInfo[0].model_matrix = glm::scale(glm::translate(glm::mat4(1), position), glm::vec3(size));

	if (size < 0.1f) {
		return true;
	}
	return false;
}
