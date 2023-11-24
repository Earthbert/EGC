#include "resources.h"
#include "components/simple_scene.h"

ResourceManager& ResourceManager::getInstance() {
	static ResourceManager instance;
	return instance;
}

ResourceManager::ResourceManager() {
	{
		Shader* shader = new Shader("HW2_Shader");
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "homework2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
		shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "homework2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Mesh* mesh = new Mesh("ground");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "ground.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
	{
		Mesh* mesh = new Mesh("wheels");
		mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "homework2"), "wheels.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}
}
