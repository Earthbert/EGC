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
