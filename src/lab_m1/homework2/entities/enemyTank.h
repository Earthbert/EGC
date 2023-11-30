#pragma once

#include "playerTank.h"
#include "tank.h"
#include "lab_m1/homework2/random_num.h"

class EnemyTank : public Tank {
public:
	EnemyTank(PlayerTank& playerTank, glm::vec3 center);
	~EnemyTank() override;

	EnemyTank &EnemyTank::operator=(const EnemyTank &other);

	std::optional<Missile> updateEnemyTank(float deltaTimeSeconds);

private:
	PlayerTank& playerTank;
	RandomNum generator;

	std::optional<Missile> targetPlayerTank(float deltaTimeSeconds);
};
