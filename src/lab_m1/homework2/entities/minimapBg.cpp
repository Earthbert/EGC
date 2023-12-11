#include "minimapBg.h"
#include "lab_m1/homework2/colors.h"
#include "lab_m1/homework2/consts.h"

MinimapBg::MinimapBg() {
	renderInfo.push_back({HW2_GROUND_MESH, HW2_BASIC_SHADER, glm::scale(glm::translate(glm::mat4(1), glm::vec3(0, -1, 0)), glm::vec3(3.5f, 0, 3.5f)), RGB_BLACK});
}

MinimapBg::~MinimapBg() = default;
