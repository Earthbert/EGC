#include "enemyTank.h"

#include "playerTank.h"
EnemyTank::EnemyTank(PlayerTank& playerTank, glm::vec3 center) : Tank(center), playerTank(playerTank) {}

EnemyTank::~EnemyTank() = default;

EnemyTank& EnemyTank::operator=(const EnemyTank& other) = default;
