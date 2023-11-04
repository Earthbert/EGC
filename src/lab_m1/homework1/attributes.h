#pragma once

#include "components/simple_scene.h"

class Drawable {
public:
	Drawable(glm::vec2 initialPos);
	~Drawable();

	const std::vector<std::pair<Mesh*, glm::mat3>>& getDrawData();
protected:
	glm::vec2 initialPos;
	std::vector<std::pair<Mesh*, glm::mat3>> objectData;
};

