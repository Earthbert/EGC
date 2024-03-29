#include "tank.h"

#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

Tank::Tank(const glm::vec3 center) : Collidable(center, HW2_TANK_RADIUS) {
	this->center = center;
	this->tankDirection = glm::vec3(0, 0, 1);
	this->turretDirection = glm::vec3(0, 0, 1);
	// Create render info for the tank
	// 0 - track 1 - body 2 - turret 3 - cannon
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1), center);

		renderInfo.push_back(RenderInfo{ HW2_TRACK_MESH, HW2_BASIC_SHADER, modelMatrix, RGB_LIGHT_GREY });
		renderInfo.push_back(RenderInfo{ HW2_BODY_MESH, HW2_BASIC_SHADER, modelMatrix, RGB_MILITARY_BLUE });
		renderInfo.push_back(RenderInfo{ HW2_TURRET_MESH, HW2_BASIC_SHADER, modelMatrix, RGB_MILITARY_GREY });
		renderInfo.push_back(RenderInfo{ HW2_CANNON_MESH, HW2_BASIC_SHADER, modelMatrix, RGB_LIGHT_GREY });
	}
}

Tank::Tank() = default;

Tank::~Tank() = default;

void Tank::moveForward(const float deltaTimeSeconds) {
	const glm::vec3 forward = glm::normalize(tankDirection);
	center += forward * HW2_TANK_SPEED * deltaTimeSeconds;
	hitBoxCenter = center;

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1), forward * HW2_TANK_SPEED * deltaTimeSeconds);
	for (auto& info : renderInfo) {
		info.model_matrix = translationMatrix * info.model_matrix;
	}
}

void Tank::moveBackward(const float deltaTimeSeconds) {
	const glm::vec3 forward = glm::normalize(tankDirection);
	center -= forward * HW2_TANK_SPEED * deltaTimeSeconds;
	hitBoxCenter = center;

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1), -forward * HW2_TANK_SPEED * deltaTimeSeconds);
	for (auto& info : renderInfo) {
		info.model_matrix = translationMatrix * info.model_matrix;
	}
}

void Tank::rotateLeft(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), HW2_TANK_ANGULAR_SPEED * deltaTimeSeconds, glm::vec3(0, 1, 0));

	tankDirection = glm::vec3(rotationMatrix * glm::vec4(tankDirection, 1));
	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (auto& info : renderInfo) {
		info.model_matrix = info.model_matrix * rotationMatrix;
	}
}

void Tank::rotateRight(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), -(HW2_TANK_ANGULAR_SPEED * deltaTimeSeconds), glm::vec3(0, 1, 0));

	tankDirection = glm::vec3(rotationMatrix * glm::vec4(tankDirection, 1));
	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (auto& info : renderInfo) {
		info.model_matrix = info.model_matrix * rotationMatrix;
	}
}
void Tank::rotateTurretLeft(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), HW2_TURRET_ANGULAR_SPEED * deltaTimeSeconds, glm::vec3(0, 1, 0));

	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (int i = 2; i <= 3; i++) {
		renderInfo[i].model_matrix = renderInfo[i].model_matrix * rotationMatrix;
	}
}
void Tank::rotateTurretRight(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), -(HW2_TURRET_ANGULAR_SPEED * deltaTimeSeconds), glm::vec3(0, 1, 0));

	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (int i = 2; i <= 3; i++) {
		renderInfo[i].model_matrix = renderInfo[i].model_matrix * rotationMatrix;
	}
}

void Tank::update(float deltaTimeSeconds) {
	if (isAlive == false) {
				return;
	}

	if (shotTimer < HW2_SHOT_COOLDOWN) {
		shotTimer += deltaTimeSeconds;
	}
}

void Tank::getPushed(const glm::vec3& direction) {
	center -= direction;
	hitBoxCenter = center;

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1), -direction);

	for (auto& info : renderInfo) {
		info.model_matrix = translationMatrix * info.model_matrix;
	}
}

std::optional<Explosion> Tank::takeDamage() {
	if (isAlive == false) {
		return {};
	}
	
	health--;
	if (health <= 0) {
		isAlive = false;
		return Explosion(this->center, 4 * HW2_TANK_RADIUS);
	}
	return {};
}

std::optional<Missile> Tank::shoot() {
	if (isAlive == false) {
		return {};
	}

	if (shotTimer >= HW2_SHOT_COOLDOWN) {
		shotTimer = 0;
		glm::vec3 missilePosition = center + glm::normalize(turretDirection) * HW2_CANNON_LENGTH;
		missilePosition.y = HW2_CANNON_HEIGHT;
		return Missile(missilePosition, turretDirection);
	}
	return {};
}

glm::vec3 Tank::getCenter() const {
	return center;
}

glm::vec3 Tank::getTankDirection() const {
	return tankDirection;
}

int Tank::getHealth() const {
	return health;
}
