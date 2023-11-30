#pragma once
#include "Entity.h"

class Explosion final : public Entity {
public:
	Explosion(glm::vec3 position, float size);
	Explosion();
	~Explosion() override;

	bool update(float deltaTimeSeconds);

	glm::vec3 position;
	float size;

	float implosionSpeed = 3.0f;
};
