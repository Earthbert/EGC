#include "collidable.h"

#include <optional>

#include "lab_m1/homework2/consts.h"

Collidable::Collidable(glm::vec3 hitBoxCenter, float radius) {
	this->type = CIRCLE_COLLISION;
	this->hitBoxCenter = hitBoxCenter;
	this->radius = radius;
}

Collidable::Collidable(glm::vec3 hitBoxCenter, float length, float width) {
	this->type = SQUARE_COLLISION;
	this->hitBoxCenter = hitBoxCenter;
	this->length = length;
	this->width = width;
}

Collidable::Collidable() = default;

Collidable::~Collidable() = default;

std::optional<glm::vec3> Collidable::checkCollision(Collidable& other) const {
	if (this->type == CIRCLE_COLLISION && other.type == SQUARE_COLLISION) {
		return checkCicleSquareCollision(other);
	}
	if (this->type == SQUARE_COLLISION && other.type == CIRCLE_COLLISION) {
		return other.checkCicleSquareCollision(*this);
	}
	if (this->type == CIRCLE_COLLISION && other.type == CIRCLE_COLLISION) {
		return checkCircleCicleCollision(other);
	}
	return {};
}

std::optional<glm::vec3> Collidable::checkCicleSquareCollision(const Collidable& other) const {
	glm::vec3 closestPoint;
	closestPoint.x = glm::clamp(hitBoxCenter.x, other.hitBoxCenter.x - other.length / 2, other.hitBoxCenter.x + other.length / 2);
	closestPoint.y = 0;
	closestPoint.z = glm::clamp(hitBoxCenter.z, other.hitBoxCenter.z - other.width / 2, other.hitBoxCenter.z + other.width / 2);

	const glm::vec3 collisionVector = closestPoint - glm::vec3(hitBoxCenter.x, 0, hitBoxCenter.z);

	const float distance = glm::length(collisionVector);

	if (distance < radius) {
		if (distance == 0.0f) {
			return glm::vec3(radius, 0, 0);
		}

		const float moveDistance = radius - distance;
		glm::vec3 moveVector = glm::normalize(collisionVector) * moveDistance;
		return moveVector;
	}
	return {};
}

glm::vec3 Collidable::checkCircleCicleCollision(const Collidable& other) const {
	const float distance = glm::length(this->hitBoxCenter - other.hitBoxCenter);
	const glm::vec3 difference = this->hitBoxCenter - other.hitBoxCenter;

	if (distance < this->radius + other.radius) {
		return (this->radius + other.radius - distance) * glm::normalize(difference);
	}
	return {};
}
