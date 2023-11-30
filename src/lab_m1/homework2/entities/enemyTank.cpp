#include "enemyTank.h"

#include "playerTank.h"
#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

EnemyTank::EnemyTank(PlayerTank& playerTank, glm::vec3 center) : Tank(center), playerTank(playerTank) {
	renderInfo[1].color = RGB_DARK_RED;

	std::for_each(renderInfo.begin(), renderInfo.end(), [](RenderInfo& info) {
		info.shader_name = HW2_TANK_SHADER;
		});
}

EnemyTank::~EnemyTank() = default;

EnemyTank& EnemyTank::operator=(const EnemyTank& other) = default;

std::optional<Missile> EnemyTank::updateEnemyTank(float deltaTimeSeconds) {
	update(deltaTimeSeconds);
	updateState(deltaTimeSeconds);
	return targetPlayerTank(deltaTimeSeconds);
}

std::optional<Missile> EnemyTank::targetPlayerTank(float deltaTimeSeconds) {
	if (glm::length(this->center - playerTank.getCenter()) < HW2_ENEMY_DETECTION_RADIUS) {
		const glm::vec3 direction = glm::normalize(playerTank.getCenter() - this->center);

		float angle = glm::acos(glm::dot(direction, glm::normalize(this->turretDirection)));

		const glm::vec3 crossProduct = glm::cross(this->turretDirection, direction);
		const float rotationDirection = glm::sign(glm::dot(crossProduct, glm::vec3(0.0f, 1.0f, 0.0f)));

		angle *= glm::degrees(angle) * rotationDirection;

		if (abs(angle) < glm::pi<float>() / 90.0f) {
			return shoot();
		}

		if (angle > 0.0f) {
			rotateTurretLeft(deltaTimeSeconds);
		} else {
			rotateTurretRight(deltaTimeSeconds);
		}
	}

	return {};
}

void EnemyTank::updateState(float deltaTimeSeconds) {
	currentStateTimer -= deltaTimeSeconds;

	if (currentStateTimer <= 0) {
		currentStateTimer = generator.getRandomFloat(1, 5);
		currentState = static_cast<MovementState>(generator.getRandomInt(0, 4));
	}

	switch (currentState) {
	case MovementState::Idle:
		break;
	case MovementState::MovingForward:
		moveForward(deltaTimeSeconds);
		break;
	case MovementState::MovingBackward:
		moveBackward(deltaTimeSeconds);
		break;
	case MovementState::RotatingLeft:
		rotateLeft(deltaTimeSeconds);
		break;
	case MovementState::RotatingRight:
		rotateRight(deltaTimeSeconds);
		break;
	}
}




