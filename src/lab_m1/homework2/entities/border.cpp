#include "border.h"


Border::Border(glm::vec3 center, float length, float width) : Collidable(center, length, width) {}

Border::Border() = default;

Border::~Border() = default;
