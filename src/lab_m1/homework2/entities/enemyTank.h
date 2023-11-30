#pragma once

#include "playerTank.h"
#include "tank.h"

class EnemyTank : public Tank {
public:
	EnemyTank(PlayerTank& playerTank, glm::vec3 center);
	~EnemyTank() override;

	EnemyTank &EnemyTank::operator=(const EnemyTank &other);

	PlayerTank& playerTank;
};
