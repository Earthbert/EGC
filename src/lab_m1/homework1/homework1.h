#pragma once

#include <random>

#include "components/simple_scene.h"
#include "lab_m1/homework1/entities.h"

namespace m1
{
	class Homework1 : public gfxc::SimpleScene {
	public:
		struct ViewportSpace {
			ViewportSpace() : x(0), y(0), width(1), height(1) {}
			ViewportSpace(int x, int y, int width, int height)
				: x(x), y(y), width(width), height(height) {}
			int x;
			int y;
			int width;
			int height;
		};

		struct LogicSpace {
			LogicSpace() : x(0), y(0), width(1), height(1) {}
			LogicSpace(float x, float y, float width, float height)
				: x(x), y(y), width(width), height(height) {}
			float x;
			float y;
			float width;
			float height;
		};

	public:
		Homework1();
		~Homework1() override;

		void Init() override;

	private:
		void FrameStart() override;
		void CheckCollisions();
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

		void CreatePermanentObjects();
		void MoveObjects(float deltaTime);

		void DrawObject(Drawable& object);
		void DrawScene();
		inline void DrawUI();
		inline void DrawLiveElements();
		inline void CreateRandomEntities(float deltaTime);


		glm::mat3 VisualizationTransf2D() const;

		void SetViewportArea(glm::vec3 colorColor = glm::vec3(0), bool clear = true) const;

		inline void DrawBackground();
		glm::vec2 calcLogicSpaceCoord(int x, int y);

		std::mt19937 rng;
		std::uniform_int_distribution<int> uniTime;
		std::uniform_int_distribution<int> uniX;
		std::uniform_int_distribution<int> uniY;
		std::uniform_int_distribution<int> uniThree;
		std::uniform_int_distribution<int> uniUnit;

		LogicSpace logicSpace;
		ViewportSpace viewSpace;
		glm::mat3 modelMatrix, visMatrix;

		static constexpr int maxLives = 3;
		static constexpr int maxStars = 12;

		// Game State
		struct GameState {
			int numLives = maxLives;
			int numStars = maxStars / 2;
		} gameState;

		bool dragingRomb = false;

		// UI Elements
		HomeBase* homeBase;
		Background* background;
		Cell* cells[3][3];
		Price* rombPrices[4];
		Resource* resources[maxStars];
		Life* lives[maxLives];
		DragRomb* dragRomb;

		// Live Elements
		// Collectables
		float collectableDelta = 2000;
		float collectableTimer = 0;
		std::vector<Collectable> collectables;

		// Enemies
		float enemyDelta = 1000;
		float enemyTimer = 0;
		std::vector<Enemy> enemies;

		// Projectiles
		std::vector<Projectile> projectiles;
	};
}   // namespace m1
