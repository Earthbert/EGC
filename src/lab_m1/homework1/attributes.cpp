#include <lab_m1/homework1/attributes.h>
#include <lab_m1/homework1/hw_transform2D.h>
#include <lab_m1/homework1/homework1.h>

Drawable::Drawable() = default;

Drawable::~Drawable() = default;

const std::vector<std::pair<Mesh*, glm::mat3>>& Drawable::getDrawData() {
	return this->objectData;
}
