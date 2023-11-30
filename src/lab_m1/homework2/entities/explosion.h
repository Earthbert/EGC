#pragma once
#include "Entity.h"

class Explosion : public Entity {
public:
	Explosion(glm::vec3 position, float size);
	Explosion();
	~Explosion();

	bool update(float deltaTimeSeconds);

	glm::vec3 position;
	float size;

	float implosionSpeed = 3.0f;
};
