#pragma once
#include "Entity.h"

class House : public Entity {
public:
	House(glm::vec2 position, glm::vec3 scaleValues);
	House();
	~House();
};
