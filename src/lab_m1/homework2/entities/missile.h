#pragma once
#include "entity.h"

class Missile : public Entity {
public:
	Missile(glm::vec3 direction);
	~Missile();

	bool move(float deltaTime);
private:
	float speed = 0.5f;
	glm::vec3 direction;
	float distanceLeft = 100.0f;

};