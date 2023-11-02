#pragma once

#include "lab_m1/homework1/homework1.h"

namespace m1 {
	class Drawable
	{
	public:
		Drawable(Homework1* world, glm::vec2 initialPos, Mesh* mesh);
		~Drawable();
		void draw(glm::mat3 visMatrix);

	private:
		Homework1* world;
		glm::vec2 initialPos;
		Mesh* mesh;
		glm::mat3 modelMatrix;
	};
}

