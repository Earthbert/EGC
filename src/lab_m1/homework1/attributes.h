#pragma once

#include "components/simple_scene.h"

class Drawable {
public:
	Drawable();
	~Drawable();

	const std::vector<std::pair<Mesh*, glm::mat3>>& getDrawData();
protected:
	std::vector<std::pair<Mesh*, glm::mat3>> objectData;
};

class Clickable {
protected:
	glm::vec2 pressBoxCenter;
	int width, heigth;
public:
	bool checkClick(glm::vec2 pos) const;
};
