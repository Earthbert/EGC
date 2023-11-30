#pragma once

#include "tank.h"

class EnemyTank final : public Tank {
public:
	EnemyTank(glm::vec3 center);

	EnemyTank();
	~EnemyTank();

};
