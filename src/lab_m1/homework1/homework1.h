#pragma once

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
		void RenderMesh(Mesh* mesh, const glm::mat3& modelMatrix);

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

		void CreatePermanentObjects();

		void DrawObject(Drawable& object);

		void DrawScene();
		void DrawUI();


		glm::mat3 VisualizationTransf2D() const;
		glm::mat3 VisualizationTransf2DUnif() const;

		void SetViewportArea(glm::vec3 colorColor = glm::vec3(0), bool clear = true) const;

		inline void drawBackground();

	private:
		LogicSpace logicSpace;
		ViewportSpace viewSpace;
		glm::mat3 modelMatrix, visMatrix;

		const float logicSpaceWidth = 1800;
		const float logicSpaceHeigth = 1000;

		struct GameState {
			const int maxLives = 3;
			const int maxStars = 10;

			int numLives = maxLives;
			int numStars = 0;
		} gameState;

		HomeBase* homeBase;
		Background* background;
		Cell* cells[3][3];
		RombPrice* rombPrices[4];

	};
}   // namespace m1
