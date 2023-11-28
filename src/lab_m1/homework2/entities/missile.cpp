#include "lab_m1/homework2/entities/missile.h"

Missile::Missile(glm::vec3 direction) {
	this->direction = direction;
}

Missile::~Missile() = default;

bool Missile::move(float deltaTime) {
	return false;
}
