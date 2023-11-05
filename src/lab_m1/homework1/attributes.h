#pragma once

#include "components/simple_scene.h"

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

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

class HasHitbox {
public:
	bool checkCollision(HasHitbox other) const;
protected:
	glm::vec2 hitboxCenter;
	int hitBoxRadius;
};

class Moveable {
public:
	virtual bool move(float deltaTime);
protected:
	glm::vec2 currentPos;
	glm::vec2 finalPos;
	glm::vec2 speed;
};

class HasAnimation {
public:
	virtual void startAnimation();
	virtual bool animate();
};
