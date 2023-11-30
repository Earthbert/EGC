#include "enemyTank.h"

#include "playerTank.h"
#include "lab_m1/homework2/colors.h"

EnemyTank::EnemyTank(PlayerTank& playerTank, glm::vec3 center) : Tank(center), playerTank(playerTank) {
	renderInfo[1].color = RGB_DARK_RED;
}

EnemyTank::~EnemyTank() = default;

EnemyTank& EnemyTank::operator=(const EnemyTank& other) = default;
