#pragma once
#include <optional>

#include "entity.h"
#include "missile.h"

class Tank : public Entity {
public:
	Tank(glm::vec3 center);
	Tank();
	~Tank();

  /*  Tank(const Tank& other);

    Tank& operator=(const Tank& other);*/

	void moveForward(float deltaTimeSeconds);
	void moveBackward(float deltaTimeSeconds);
	void rotateLeft(float deltaTimeSeconds);
	void rotateRight(float deltaTimeSeconds);

	void rotateTurretLeft(float deltaTimeSeconds);
	void rotateTurretRight(float deltaTimeSeconds);

	std::optional<Missile> shoot();

	glm::vec3 getCenter() const;
protected:
	glm::vec3 center;
	glm::vec3 tankDirection;
	glm::vec3 turretDirection;

	float tankSpeed = 5.0f;
	float tankAngularSpeed = 2.0f;
	float turretAngularSpeed = 2.0f;
};
