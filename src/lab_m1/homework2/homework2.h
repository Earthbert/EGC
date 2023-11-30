#pragma once
#include "hw2_camera.h"
#include "entities/entity.h"
#include "random_num.h"
#include "components/simple_scene.h"
#include "entities/border.h"
#include "entities/enemyTank.h"
#include "entities/ground.h"
#include "entities/house.h"
#include "entities/minimapBg.h"
#include "entities/playerTank.h"
#include "entities/tank.h"
#include "lab_m1/homework1/entities.h"

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

		void RenderEntities();
		void UpdateEntities(float deltaTimeSeconds);
		void CheckCollisions(float deltaTimeSeconds);

		void CreateEnemies(float deltaTimeSeconds);
		void RenderObject(Entity &entity);
		void RenderUsingBasicShader(Mesh* mesh, const glm::mat4& modelMatrix, const glm::vec3& color);
		void CreateShaders();
		void CreateMeshes();
		void CreateEntities();
		void RenderMinimap();

		// Camera
		glm::mat4 projectionMatrix;
		HW2_Camera camera;

		// Static Entities
		Ground ground;
		std::vector<House> houses;
		std::vector<Border> borders;
		// Dynamic Entities
		PlayerTank playerTank;
		std::vector<EnemyTank> enemyTanks;
		std::vector<Missile> missiles;
		std::vector<Explosion> explosions;

		// Game logic
		bool gameOver = false;
		float gameOverTimer = 600.0f;
		float enemyTimer = 0.0f;

		// Minimap
		MinimapBg minimapBg;
		bool renderMinimap;
		glm::mat4 minimapViewMatrix;
		glm::mat4 minimapProjectionMatrix;
	protected:
		RandomNum generator;
	};
}   // namespace m1