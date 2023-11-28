#pragma once
#include "hw2_camera.h"
#include "entities/Entity.h"
#include "random_num.h"
#include "components/simple_scene.h"
#include "entities/Ground.h"
#include "entities/PlayerTank.h"
#include "entities/Tank.h"

namespace m1
{
	class Homework2 : public gfxc::SimpleScene {
	public:
		Homework2();
		~Homework2();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void RenderObject(Entity &entity);
		void RenderUsingBasicShader(Mesh* mesh, const glm::mat4& modelMatrix, const glm::vec3& color);
		void CreateShaders();
		void CreateMeshes();
		void CreateEntities();

		// Camera
		glm::mat4 projectionMatrix;
		HW2_Camera camera;

		// Static Entities
		Ground ground;
		// Dynamic Entities
		PlayerTank playerTank;
	protected:
		RandomNum generator;
	};
}   // namespace m1