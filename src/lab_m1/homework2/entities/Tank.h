#pragma once
#include <optional>

#include "collidable.h"
#include "entity.h"
#include "missile.h"
#include "explosion.h"

class Tank : public Entity, public Collidable {
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

	void getPushed(const glm::vec3& direction);

	std::optional<Explosion> takeDamage();

	std::optional<Missile> shoot();

	glm::vec3 getCenter() const;

	glm::vec3 getTankDirection() const;

	int getHealth() const;
protected:
	glm::vec3 center;
	glm::vec3 tankDirection;
	glm::vec3 turretDirection;

	bool isAlive = true;

	int health = 3;

	float shotTimer  = 0;
};
