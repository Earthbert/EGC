#pragma once
#include <vector>
#include <string>
#include "components/simple_scene.h"

struct RenderInfo {
	std::string mesh_name;
	std::string shader_name;
	glm::mat4 model_matrix;
	glm::vec3 color;
};

class Entity {
public:
	std::vector<RenderInfo>& getRenderInfo();

protected:
	std::vector<RenderInfo> renderInfo;
};
