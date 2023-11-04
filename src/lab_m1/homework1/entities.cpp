#include <lab_m1/homework1/entities.h>
#include <lab_m1/homework1/hw_object2D.h>
#include <lab_m1/homework1/hw_transform2D.h>

using namespace std;

HomeBase::HomeBase() {
	this->center = glm::vec2(75, 350);
	Mesh* mesh = hw_object2D::CreateRectangle("homeBase", 100, 600, glm::vec3(1, 0, 0), true, 0);
	glm::mat3 modelMatrix = transform2D::Translate(this->center.x, this->center.y);
	this->objectData.emplace_back(mesh, modelMatrix);
};

HomeBase::~HomeBase() = default;

Background::Background(float logicSpaceWidth, float logicSpaceHeigth) {
	this->center = glm::vec2(logicSpaceWidth / 2, logicSpaceHeigth / 2);
	Mesh* mesh = hw_object2D::CreateRectangle("backGround", logicSpaceWidth, logicSpaceHeigth, glm::vec3(0.2, 0.2, 0.2), true, -1);
	glm::mat3 modelMatrix = transform2D::Translate(this->center.x, this->center.y);
	this->objectData.emplace_back(mesh, modelMatrix);
}

Background::~Background() = default;

Cell::Cell(int i, int j) {
	if (i == 0) {
		this->center.y = 575;
	} else if (i == 1) {
		this->center.y = 350;
	} else if (i == 2) {
		this->center.y = 125;
	}

	if (j == 0) {
		this->center.x = 225;
	} else if (j == 1) {
		this->center.x = 450;
	} else if (j == 2) {
		this->center.x = 675;
	}

	Mesh* mesh = hw_object2D::CreateSquare("Cell", 150, glm::vec3(0, 1, 0.2), true, 0);
	glm::mat3 modelMatrix = transform2D::Translate(this->center.x, this->center.y);
	this->objectData.emplace_back(mesh, modelMatrix);
}

Cell::~Cell() = default;

RombPrice::RombPrice(unitType type) {
	this->type = type;

	Mesh* romb;

	switch (type) {
	case ORANGE:
		this->squareCenter.x = 200;
		this->firstStarCenter.x = 145;
		this->cost = 1;
		romb = hw_object2D::CreateRomb("PriceRomb", 60, glm::vec3(1, 0.5, 0.15), 0);
		break;
	case BLUE:
		this->squareCenter.x = 425;
		this->firstStarCenter.x = 370;
		this->cost = 2;
		romb = hw_object2D::CreateRomb("PriceRomb", 60, glm::vec3(0.2, 0.5, 0.95), 0);
		break;
	case YELLOW:
		this->squareCenter.x = 650;
		this->firstStarCenter.x = 595;
		this->cost = 2;
		romb = hw_object2D::CreateRomb("PriceRomb", 60, glm::vec3(1, 1, 0.35), 0);
		break;
	case PURPLE:
		this->squareCenter.x = 875;
		this->firstStarCenter.x = 820;
		this->cost = 3;
		romb = hw_object2D::CreateRomb("PriceRomb", 60, glm::vec3(0.45, 0.16, 0.95), 0);
		break;
	}

	this->firstStarCenter.y = 760;
	this->squareCenter.y = 875;

	Mesh* square = hw_object2D::CreateSquare("PriceSquare", 150, glm::vec3(0, 0, 0), false, 0);
	objectData.emplace_back(square, transform2D::Translate(this->squareCenter.x, this->squareCenter.y));

	Mesh* star = hw_object2D::CreateStar("PriceStar", 20, 10, glm::vec3(0.6, 0.6, 0.6), true, 0);
	for (int i = 0; i < this->cost; i++) {
		objectData.emplace_back(star, transform2D::Translate(static_cast<float>(i) * 55 + this->firstStarCenter.x, this->firstStarCenter.y));
	}

	objectData.emplace_back(romb, transform2D::Translate(this->squareCenter.x, this->squareCenter.y));
}


