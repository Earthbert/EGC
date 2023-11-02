#include <lab_m1/homework1/attributes.h>
#include <lab_m1/homework1/hw_transform2D.h>
#include <lab_m1/homework1/homework1.h>

using namespace m1;

Drawable::Drawable(Homework1* world, glm::vec2 initialPos, Mesh* mesh)
{
	this->world = world;
	this->initialPos = initialPos;
	this->mesh = mesh;
}

Drawable::~Drawable()
{
}

void Drawable::draw(glm::mat3 visMatrix) {
	modelMatrix = visMatrix * transform2D::Translate(100, 300);
	world->RenderMesh(mesh, modelMatrix);
}