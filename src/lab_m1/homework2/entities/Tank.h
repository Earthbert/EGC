#pragma once
#include <optional>

#include "entity.h"
#include "missile.h"

class Tank : public Entity {
public:
	Tank(glm::vec3 center);
	Tank();
	~Tank();

	void moveForward(float deltaTimeSeconds);
	void moveBackward(float deltaTimeSeconds);
	void rotateLeft(float deltaTimeSeconds);
	void rotateRight(float deltaTimeSeconds);

	void rotateTurretLeft(float deltaTimeSeconds);
	void rotateTurretRight(float deltaTimeSeconds);

	std::optional<Missile> shoot(float deltaTimeSeconds);

	glm::vec3 getCenter() const;

	float getTankSpeed() const;
	float getTankAngularSpeed() const;
	glm::vec3 getTankDirection() const;
protected:
	glm::vec3 center;
	glm::vec3 tankDirection;
	glm::vec3 turretDirection;

	float tankSpeed = 5.0f;
	float tankAngularSpeed = 2.0f;
	float turretAngularSpeed = 2.0f;
};
