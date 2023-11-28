#pragma once

#include "utils/glm_utils.h"

class HW2_Camera {
public:
	HW2_Camera() {
		position = glm::vec3(0, 2, -5);
		forward = glm::vec3(0, 0, 1);
		up = glm::vec3(0, 1, 0);
		right = glm::vec3(1, 0, 0);
		distanceToTarget = 5;
	}

	~HW2_Camera() = default;

	void Move(float distance, glm::vec3 direction) {
		glm::vec3 dir = glm::normalize(glm::vec3(direction.x, 0, direction.z));
		position += dir * distance;
	}

	void TranslateForward(float distance) {
		position = position + glm::normalize(forward) * distance;
	}

	void TranslateUpward(float distance) {
		position = position + glm::normalize(up) * distance;
	}

	void TranslateRight(float distance) {
		position = position + glm::normalize(glm::cross(forward, up)) * distance;
	}

	void RotateThirdPerson_OX(float angle) {
		TranslateForward(distanceToTarget);
		glm::mat4 mat = glm::rotate(glm::mat4(1), angle, glm::normalize(right));
		forward = glm::normalize(glm::vec3(mat * glm::vec4(forward, 1)));
		up = glm::normalize(glm::vec3(mat * glm::vec4(up, 1)));
		TranslateForward(-distanceToTarget);
	}

	void RotateThirdPerson_OY(float angle) {
		TranslateForward(distanceToTarget);
		glm::mat4 mat = glm::rotate(glm::mat4(1), angle, glm::vec3(0, 1, 0));
		forward = glm::normalize(glm::vec3(mat * glm::vec4(forward, 1)));
		right = glm::normalize(glm::vec3(mat * glm::vec4(right, 1)));
		up = glm::normalize(glm::vec3(mat * glm::vec4(up, 1)));
		TranslateForward(-distanceToTarget);
	}

	void RotateThirdPerson_OZ(float angle) {
		TranslateForward(distanceToTarget);
		glm::mat4 mat = glm::rotate(glm::mat4(1), angle, forward);
		up = glm::normalize(glm::vec3(mat * glm::vec4(up, 1)));
		right = glm::normalize(glm::vec3(mat * glm::vec4(right, 1)));
		TranslateForward(-distanceToTarget);
	}

	void Zoom(float distance) {
		const float newDistanceToTarget = distanceToTarget - distance;
		if (3 < newDistanceToTarget && newDistanceToTarget < 10) {
			distanceToTarget = newDistanceToTarget;
			position = position + glm::normalize(forward) * distance;
		}
	}

	glm::mat4 GetViewMatrix() const {
		return glm::lookAt(position, position + forward, up);
	}

	glm::vec3 GetTargetPosition() const {
		return position + forward * distanceToTarget;
	}

public:
	float distanceToTarget;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};
