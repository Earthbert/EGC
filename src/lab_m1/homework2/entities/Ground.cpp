#pragma once

#include "ground.h"

#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

Ground::Ground() {
	renderInfo.push_back(RenderInfo{HW2_GROUND_MESH, HW2_BASIC_SHADER, glm::scale(glm::mat4(1), glm::vec3(3, 1, 3)), RGB_GRASS_GREEN});
}

Ground::~Ground() = default;
