#pragma once
#include "entity.h"

class Missile : public Entity {
public:
	Missile(glm::vec3 initalPosition, glm::vec3 direction);
	~Missile();

	bool travel(float deltaTime);
private:
	glm::vec3 position;
	glm::vec3 direction;
	float speed = 10.0f;
	float distanceLeft = 100.0f;

};