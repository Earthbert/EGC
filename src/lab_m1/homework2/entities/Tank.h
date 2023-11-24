#pragma once
#include "Entity.h"

class Tank final : public Entity {
public:
	enum class type {
		PLAYER,
		ENEMY
	};

	Tank(type type, glm::vec3 center);
	Tank();
	~Tank();
private:
	type m_type;
	glm::vec3 center;
};
