#pragma once
#include "collidable.h"
#include "entity.h"
#include "explosion.h"

class Missile : public Entity, public Collidable {
public:
	Missile(glm::vec3 initalPosition, glm::vec3 direction);
	~Missile();

	bool travel(float deltaTime);
	Explosion explode() const;

private:
	glm::vec3 position;
	glm::vec3 direction;
	float speed = 10.0f;
	float distanceLeft = 100.0f;

};
