#include <lab_m1/homework1/entities.h>
#include <lab_m1/homework1/hw_object2D.h>
#include <lab_m1/homework1/hw_transform2D.h>

using namespace std;

HomeBase::HomeBase() : Drawable(glm::vec2(75, 350))
{
	Mesh* mesh = hw_object2D::CreateRectangle("homeBase", 100, 600, glm::vec3(1, 0, 0), true, 0);
	glm::mat3 modelMatrix = transform2D::Translate(this->initialPos.x, this->initialPos.y);
	this->objectData.push_back(make_pair(mesh, modelMatrix));
};

HomeBase::~HomeBase()
{
}

Background::Background(int logicSpaceWidth, int logicSpaceHeigth) : Drawable(glm::vec2(logicSpaceWidth / 2, logicSpaceHeigth / 2))
{
	Mesh* mesh = hw_object2D::CreateRectangle("backGround", logicSpaceWidth, logicSpaceHeigth, glm::vec3(0.2, 0.2, 0.2), true, -1);
	glm::mat3 modelMatrix = transform2D::Translate(this->initialPos.x, this->initialPos.y);
	this->objectData.push_back(make_pair(mesh, modelMatrix));
}

Background::~Background()
{
}

Cell::Cell(int i, int j) : Drawable(calcCenter(i, j))
{
	Mesh* mesh = hw_object2D::CreateSquare("Cell", 150, glm::vec3(0, 1, 0.2), true, 0);
	glm::mat3 modelMatrix = transform2D::Translate(this->initialPos.x, this->initialPos.y);
	this->objectData.push_back(make_pair(mesh, modelMatrix));
}

Cell::~Cell()
{
}

glm::vec2 Cell::calcCenter(int i, int j)
{
	glm::vec2 pos;
	if (i == 0) {
		pos.y = 575;
	}
	else if (i == 1) {
		pos.y = 350;
	}
	else if (i == 2) {
		pos.y = 125;
	}

	if (j == 0) {
		pos.x = 225;
	}
	else if (j == 1) {
		pos.x = 450;
	}
	else if (j == 2) {
		pos.x = 675;
	}
	return pos;
}