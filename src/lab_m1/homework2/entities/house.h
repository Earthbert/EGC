#pragma once
#include "collidable.h"
#include "Entity.h"

class House : public Entity, public Collidable {
public:
	House(glm::vec2 position, glm::vec3 scaleValues);
	House();
	~House();
};
