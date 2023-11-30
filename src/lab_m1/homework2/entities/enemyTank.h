#pragma once

#include "playerTank.h"
#include "tank.h"
#include "lab_m1/homework2/consts.h"
#include "lab_m1/homework2/random_num.h"

class EnemyTank : public Tank {
	enum class MovementState {
		Idle,
		MovingForward,
		MovingBackward,
		RotatingLeft,
		RotatingRight,
	};

public:
	EnemyTank(PlayerTank& playerTank, glm::vec3 center);
	~EnemyTank() override;

	EnemyTank& EnemyTank::operator=(const EnemyTank& other);

	std::optional<Missile> updateEnemyTank(float deltaTimeSeconds);

private:
	PlayerTank& playerTank;
	RandomNum generator;
	float currentStateTimer = HW2_IDLE_MAX_TIME;
	MovementState currentState = MovementState::Idle;

	std::optional<Missile> targetPlayerTank(float deltaTimeSeconds);
	void updateState(float deltaTimeSeconds);
};
