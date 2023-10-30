#pragma once

#include "components/simple_scene.h"


namespace m1
{
	class Lab1 : public gfxc::SimpleScene
	{
	public:
		Lab1();
		~Lab1();

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

		// TODO(student): Class variables go here

		const std::string shapes[3] = { "box", "sphere", "quad" };

		glm::vec3 shape_coord = glm::vec3(1, 0.5f, 0);

		glm::vec3 initial_coord = glm::vec3(3, 0.5f, 10);
		glm::vec3 peak_coord = glm::vec3(3, 5, 10);

		glm::vec3 jumper_coord = glm::vec3(3, 0.5f, 10);

		float acc = 1.0f;

		bool jumping = false;
		bool falling = false;

		char shape_index = 0;
		bool change_color = false;

	};
}   // namespace m1
