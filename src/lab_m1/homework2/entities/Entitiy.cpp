#pragma once

#include <vector>

#include "Entity.h"

std::vector<RenderInfo>& Entity::getRenderInfo() {
	return renderInfo;
}