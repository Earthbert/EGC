#pragma once
#include "Tank.h"

class PlayerTank : public Tank {
public:
	PlayerTank(glm::vec3 center);
	PlayerTank();
	~PlayerTank();
};
