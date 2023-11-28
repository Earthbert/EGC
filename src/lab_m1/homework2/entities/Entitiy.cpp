#pragma once

#include <vector>

#include "entity.h"

std::vector<RenderInfo>& Entity::getRenderInfo() {
	return renderInfo;
}