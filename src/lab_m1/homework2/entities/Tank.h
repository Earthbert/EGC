#pragma once
#include "Entity.h"

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
protected:
	glm::vec3 center;
	glm::vec3 tankDirection;
	glm::vec3 turretDirection;

	glm::mat4 rotationMatrix = glm::mat4(1);
	glm::mat4 rotationMatrixTurret = glm::mat4(1);
	glm::mat4 translationMatrix = glm::mat4(1);

	float tankSpeed = 10.0f;
	float tankAngularSpeed = 2.0f;
	float turretAngularSpeed = 2.0f;
};
