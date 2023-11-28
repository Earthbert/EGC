#include "Tank.h"

#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

Tank::Tank(const glm::vec3 center) {
	this->center = center;
	this->tankDirection = glm::vec3(0, 0, 1);
	this->turretDirection = glm::vec3(0, 0, 1);
	// Create render info for the tank
	// 0 - track 1 - body 2 - turret 3 - cannon
	{
		renderInfo.push_back(RenderInfo{ HW2_TRACK_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_LIGHT_GREY });
		renderInfo.push_back(RenderInfo{ HW2_BODY_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_MILITARY_BLUE });
		renderInfo.push_back(RenderInfo{ HW2_TURRET_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_MILITARY_GREY });
		renderInfo.push_back(RenderInfo{ HW2_CANNON_MESH, HW2_BASIC_SHADER, glm::mat4(1), RGB_LIGHT_GREY });
	}
}

Tank::Tank() = default;

Tank::~Tank() = default;

void Tank::moveForward(const float deltaTimeSeconds) {
	const glm::vec3 forward = glm::normalize(tankDirection);
	center += forward * tankSpeed * deltaTimeSeconds;

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1), forward * tankSpeed * deltaTimeSeconds);
	for (auto& info : renderInfo) {
		info.model_matrix = translationMatrix * info.model_matrix;
	}
}

void Tank::moveBackward(const float deltaTimeSeconds) {
	const glm::vec3 forward = glm::normalize(tankDirection);
	center -= forward * tankSpeed * deltaTimeSeconds;

	const glm::mat4 translationMatrix = glm::translate(glm::mat4(1), -forward * tankSpeed * deltaTimeSeconds);
	for (auto& info : renderInfo) {
		info.model_matrix = translationMatrix * info.model_matrix;
	}
}

void Tank::rotateLeft(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), tankAngularSpeed * deltaTimeSeconds, glm::vec3(0, 1, 0));

	tankDirection = glm::vec3(rotationMatrix * glm::vec4(tankDirection, 1));
	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (auto& info : renderInfo) {
		info.model_matrix = info.model_matrix * rotationMatrix;
	}
}

void Tank::rotateRight(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), -(tankAngularSpeed * deltaTimeSeconds), glm::vec3(0, 1, 0));

	tankDirection = glm::vec3(rotationMatrix * glm::vec4(tankDirection, 1));
	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (auto& info : renderInfo) {
		info.model_matrix = info.model_matrix * rotationMatrix;
	}
}
void Tank::rotateTurretLeft(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), turretAngularSpeed * deltaTimeSeconds, glm::vec3(0, 1, 0));

	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (int i = 2; i < 3; i++) {
		renderInfo[i].model_matrix = renderInfo[i].model_matrix * rotationMatrix;
	}
}
void Tank::rotateTurretRight(const float deltaTimeSeconds) {
	const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1), -(turretAngularSpeed * deltaTimeSeconds), glm::vec3(0, 1, 0));

	turretDirection = glm::vec3(rotationMatrix * glm::vec4(turretDirection, 1));

	for (int i = 2; i < 3; i++) {
		renderInfo[i].model_matrix = renderInfo[i].model_matrix * rotationMatrix;
	}
}