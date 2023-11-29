#pragma once

#include <optional>
#include <glm/vec3.hpp>

#include "lab_m1/Homework1/Homework1.h"

class Collidable {
public:
	enum CollisionType {
		SQUARE_COLLISION,
		CIRCLE_COLLISION
	};

	Collidable(glm::vec3 hitBoxCenter, float radius);
	Collidable(glm::vec3 hitBoxCenter, float length, float width);
	Collidable();
	~Collidable();

	std::optional<glm::vec3> checkCollision(Collidable& other) const;

protected:
	std::optional<glm::vec3> checkCicleSquareCollision(const Collidable& other) const;
	glm::vec3 checkCircleCicleCollision(const Collidable& other) const;

	CollisionType type;
	glm::vec3 hitBoxCenter;
	float radius;
	float length;
	float width;
};
