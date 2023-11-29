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

	void update(float deltaTimeSeconds);

	std::optional<Missile> shoot();

	glm::vec3 getCenter() const;

	glm::vec3 getTankDirection() const;
protected:
	glm::vec3 center;
	glm::vec3 tankDirection;
	glm::vec3 turretDirection;

	float shotTimer  = 0;
};
