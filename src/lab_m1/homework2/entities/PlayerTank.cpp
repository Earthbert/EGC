#include "playerTank.h"

#include "lab_m1/homework2/consts.h"

PlayerTank::PlayerTank(const glm::vec3 center) : Tank(center) {
	std::for_each(renderInfo.begin(), renderInfo.end(), [this](RenderInfo& info) {
		info.shader_name = HW2_TANK_SHADER;
		});
}

PlayerTank::PlayerTank() = default;
PlayerTank::~PlayerTank() = default;
