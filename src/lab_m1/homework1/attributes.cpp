#include <lab_m1/homework1/attributes.h>
#include <lab_m1/homework1/hw_transform2D.h>
#include <lab_m1/homework1/homework1.h>

Drawable::Drawable() = default;

Drawable::~Drawable() = default;

const std::vector<std::pair<Mesh*, glm::mat3>>& Drawable::getDrawData() {
	return this->objectData;
}

bool Clickable::checkClick(glm::vec2 pos) const {
	if (pos.x > pressBoxCenter.x + this->width || pos.x < pressBoxCenter.x - this->width)
		return false;
	if (pos.y > pressBoxCenter.y + this->heigth || pos.y < pressBoxCenter.y - this->heigth)
		return false;
	return true;
}

bool HasHitbox::checkCollision(HasHitbox other) const {
	float deltaX = this->hitboxCenter.x - other.hitboxCenter.x;
	float deltaY = this->hitboxCenter.y - other.hitboxCenter.y;
	float dist = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (dist < (this->hitBoxRadius + other.hitBoxRadius))
		return true;
	return false;
}

bool Moveable::move(float deltaTime) {
	this->currentPos.x += speed.x * deltaTime;
	this->currentPos.y += speed.y * deltaTime;

	if (speed.x > 0 && currentPos.x > finalPos.x)
		return true;

	if (speed.x < 0 && currentPos.x < finalPos.x)
		return true;

	if (speed.y > 0 && currentPos.y > finalPos.y)
		return true;

	if (speed.y < 0 && currentPos.y < finalPos.y)
		return true;

	return false;
}
